package kr.ac.kw.jack_sphero_vr;

import android.graphics.Bitmap;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.CvException;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfPoint2f;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Size;
import org.ros.android.BitmapFromCompressedImage;
import org.ros.android.RosActivity;
import org.ros.android.view.RosImageView;
import org.ros.concurrent.CancellableLoop;
import org.ros.message.MessageListener;
import org.ros.namespace.GraphName;
import org.ros.node.ConnectedNode;
import org.ros.node.Node;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMain;
import org.ros.node.NodeMainExecutor;
import org.ros.node.topic.Publisher;
import org.ros.node.topic.Subscriber;

import java.io.IOException;

import static org.opencv.imgproc.Imgproc.getRotationMatrix2D;
import static org.opencv.imgproc.Imgproc.warpAffine;

public class JackSpheroVr extends RosActivity implements NodeMain,SensorEventListener
{
    private static final String TAG = "Jack";
    SensorManager sm;
    Sensor rSensor;
    float[] rotMat = new float[9];
    float[] vals = new float[3];
    private RosImageView<sensor_msgs.CompressedImage> cameraView_L,cameraView_R;
    public JackSpheroVr() {
        super("JackSpheroVR", "JackSpheroVR");
    }
    Bitmap bitmapImg;
    boolean isReceiving;
    boolean isProcessing;
    Mat cvImage;
    Mat dstImg;
    Bitmap dstBit;

    boolean isNeedToRecvImg;

    BaseLoaderCallback mOpenCVCallBack;

    @Override
    protected void init(NodeMainExecutor nodeMainExecutor) {

        try {
            java.net.Socket socket = new java.net.Socket(getMasterUri().getHost(), getMasterUri().getPort());
            java.net.InetAddress local_network_address = socket.getLocalAddress();
            socket.close();
            NodeConfiguration nodeConfiguration =
                    NodeConfiguration.newPublic(local_network_address.getHostAddress(), getMasterUri());
            nodeMainExecutor.execute(this, nodeConfiguration);


        } catch (IOException e) {
            // Socket problem
        }
        /*NodeConfiguration nodeConfiguration = NodeConfiguration.newPublic(getRosHostname());
        nodeConfiguration.setMasterUri(getMasterUri());
        nodeMainExecutor.execute(this, nodeConfiguration);*/
        // The RosTextView is also a NodeMain that must be executed in order to
        // start displaying incoming messages.
    }
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        sm = (SensorManager)getSystemService(SENSOR_SERVICE);
        rSensor = sm.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
        cameraView_L = (RosImageView<sensor_msgs.CompressedImage>) findViewById(R.id.image_L);

        cameraView_R = (RosImageView<sensor_msgs.CompressedImage>) findViewById(R.id.image_R);
        //cvImage = new Mat();
        isNeedToRecvImg = true;

    }


    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS: {
                    Log.i(TAG, "OpenCV loaded successfully");
                }
                break;
                default: {
                    super.onManagerConnected(status);
                }
                break;
            }
        }
    };

    @Override
    protected void onPause() {
        super.onPause();
        sm.unregisterListener(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        sm.registerListener(this,rSensor,SensorManager.SENSOR_DELAY_FASTEST);
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_11, this, mLoaderCallback);
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }

        dstBit = Bitmap.createBitmap(240, 240, Bitmap.Config.ARGB_8888);
        isProcessing = false;
    }

    public void safeImgCpy(Mat src, Mat dst, int start_x, int start_y)
    {
        for(int i=0; i<dst.rows(); i++)
        {
            for(int j=0; j<dst.cols(); j++)
            {
                if ( ( (start_x + j) < 0 || (start_x + j) >= src.cols() ) || ( (start_y + i) < 0 || (start_y + i) >= src.rows() ) ) {
                    byte[] pixelInten = new byte[3];
                    pixelInten[0] = 0;
                    pixelInten[1] = 0;
                    pixelInten[2] = 0;
                    try {
                        dst.put(i, j, pixelInten);
                    }
                    catch (java.lang.UnsupportedOperationException e)
                    {

                    }
                    //Log.d("SafeImgCpy", "Cnt " + i + "row " + j + "cols ");
                }
                else
                {

                    //double[] data = src.get(i+ start_y, j + start_x); //Stores element in an array
                    //dst.put(i, j, data); //Puts element back into matrix
                    byte[] pixelInten = new byte[3];
                    try {
                    src.get(i + start_y, j + start_x, pixelInten);
                    dst.put(i,j,pixelInten);
                }
                catch (java.lang.UnsupportedOperationException e)
                {

                }
                }
            }
        }
    }
    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {
        if (sensorEvent.sensor.getType() == Sensor.TYPE_ROTATION_VECTOR)
        {
            // Convert the rotation-vector to a 4x4 matrix.
            SensorManager.getRotationMatrixFromVector(rotMat, sensorEvent.values);
            //SensorManager.remapCoordinateSystem(rotMat,SensorManager.AXIS_X, SensorManager.AXIS_Y,vals);
            SensorManager.getOrientation(rotMat, vals);

            // Optionally convert the result from radians to degrees
            vals[0] = (float) Math.toDegrees(vals[0]);
            vals[1] = (float) Math.toDegrees(vals[1]);
            vals[2] = (float) Math.toDegrees(vals[2]);

//            tv.setText(" Yaw: " + vals[0] + " Pitch: "
//                    + vals[1] + " Roll : "
//                    + vals[2]);

        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {

    }

    @Override
    public GraphName getDefaultNodeName() {
        //
        return GraphName.of("android/jack_vr");
    }

    @Override
    public void onShutdown(Node node) {

    }

    @Override
    public void onShutdownComplete(Node node) {

    }

    @Override
    public void onError(Node node, Throwable throwable) {

    }

    public void onStart(ConnectedNode connectedNode) {


        final Publisher publisher = connectedNode.newPublisher("jack_vr/orientation", "std_msgs/Float32MultiArray");
        connectedNode.executeCancellableLoop(new CancellableLoop() {
            private int sequenceNumber;

            protected void setup() {
                this.sequenceNumber = 0;
            }

            protected void loop() throws InterruptedException {
                std_msgs.Float32MultiArray arr = (std_msgs.Float32MultiArray)publisher.newMessage();
                arr.setData(vals);
                publisher.publish(arr);


                if(isNeedToRecvImg)
                {
                    return;
                }

                while(isReceiving) {}
                while(isProcessing) {}

                isProcessing = true;

                int maxRow = cvImage.rows();
                int maxCol = cvImage.cols();

                final int viewSize = 240;
                final int viewSizeHalf = viewSize / 2;

                final int viewYawSize = (int)(viewSize * 1.414 + 0.5);
                final int viewYawSizeHalf = viewYawSize / 2;

                int viewX = (int)(maxCol * vals[0] / 180.0);
                int viewY = (int)(maxRow * (vals[2] + 180) / 150.0);

                int viewSX = viewX - viewYawSizeHalf;
                int viewSY = viewY - viewYawSizeHalf;

                if (viewSX < 0) viewSX = 0;
                if (viewSY < 0) viewSY = 0;
                if (viewSX >= maxCol - viewYawSize) viewSX = maxCol - viewYawSize-1;
                if (viewSY >= maxRow - viewYawSize) viewSY = maxRow - viewYawSize-1;

                Rect roi = new Rect(viewSX,viewSY,viewYawSize,viewYawSize);
                Mat yawImg = new Mat(cvImage, roi);
                Point pt = new Point(yawImg.cols() / 2., yawImg.rows() / 2.);

                Mat r = getRotationMatrix2D(pt,-vals[1],1.0);

                int size_diff = viewYawSize - viewSize;
                int half_size_diff = size_diff / 2;
                Mat rotImg = new Mat();
                warpAffine(yawImg, rotImg, r, new Size(yawImg.cols(),yawImg.rows()));

                try {
                    Rect roipwa = new Rect(half_size_diff,half_size_diff,viewSize,viewSize);
                    dstImg = new Mat(rotImg, roipwa);
                }
                catch (CvException e)
                {
                    Log.e("cv", "Error, rect = " + viewSX + ", " + viewSY);
                    return;
                }

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        //Mat dstImg2 = new Mat();
                        //dstImg2.create(240,240,CvType.CV_8UC3);
                        //safeImgCpy(cvImage,dstImg2,viewSX,viewSY);

                        Bitmap dstBit = Bitmap.createBitmap(240, 240, Bitmap.Config.ARGB_8888);;
                        Utils.matToBitmap(dstImg, dstBit);

                        cameraView_L.setImageBitmap(dstBit);
                        cameraView_R.setImageBitmap(dstBit);
                        isProcessing = false;
                    }
                });

                //cameraView_L.postInvalidate();
                //cameraView_R.postInvalidate();
                ++this.sequenceNumber;
                Thread.sleep(15L);
            }
        });


        Subscriber subscriber = connectedNode.newSubscriber("cv/video/compressed", "sensor_msgs/CompressedImage");
        subscriber.addMessageListener(new MessageListener() {
            //method 1
            public void onNewMessage(final Object message) {
                while(isProcessing) {}
                isReceiving = true;
                bitmapImg = (Bitmap) new BitmapFromCompressedImage().call((sensor_msgs.CompressedImage)message);
                if(isNeedToRecvImg)
                    cvImage = new Mat(bitmapImg.getWidth(),bitmapImg.getHeight(),CvType.CV_8UC3);
                Utils.bitmapToMat(bitmapImg, cvImage);
                isNeedToRecvImg = false;
                isReceiving = false;

                //Rect roi = new Rect(200,100,240,240);
                //dstImg = new Mat(cvImage, roi);
                //dstImg.create(240,240,CvType.CV_8UC1);
                //safeImgCpy(cvImage,dstImg,viewSX,viewSY);
                //Utils.matToBitmap(dstImg, dstBit);

                //method2

                /*
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        bitmapImg = (Bitmap) new BitmapFromCompressedImage().call((sensor_msgs.CompressedImage)message);
                        Mat cvImage = new Mat(bitmapImg.getWidth(),bitmapImg.getHeight(),CvType.CV_8UC3);
                        Utils.bitmapToMat(bitmapImg, cvImage);


                        int maxRow = cvImage.rows();
                        int maxCol = cvImage.cols();

                        final int viewSize = 240;
                        final int viewSizeHalf = 120;

                        int viewX = (int)(maxCol * vals[0] / 180.0);
                        int viewY = (int)(maxRow * (vals[2] + 180) / 150.0);

                        int viewSX = viewX - viewSizeHalf;
                        int viewSY = viewY - viewSizeHalf;

                        if (viewSX < 0) viewSX = 0;
                        if (viewSY < 0) viewSY = 0;
                        if (viewSX >= maxCol - viewSize) viewSX = maxCol - viewSize-1;
                        if (viewSY >= maxRow - viewSize) viewSY = maxRow - viewSize-1;

                        Rect roi = new Rect(viewSX,viewSY,240,240);
                        //Mat dstImage = new Mat(cvImage, roi);

                        try {
                            dstImg = new Mat(cvImage, roi);
                        }
                        catch (CvException e)
                        {
                            Log.e("cv", "Error, rect = " + viewSX + ", " + viewSY);
                            return;
                        }
                        //Mat dstImg2 = new Mat();
                        //dstImg2.create(240,240,CvType.CV_8UC3);
                        //safeImgCpy(cvImage,dstImg2,viewSX,viewSY);

                        Bitmap dstBit = Bitmap.createBitmap(240, 240, Bitmap.Config.ARGB_8888);;
                        Utils.matToBitmap(dstImg, dstBit);

                        cameraView_L.setImageBitmap(dstBit);
                        cameraView_R.setImageBitmap(dstBit);
                    }
                });
                */


                //cameraView_L.postInvalidate();
                //cameraView_R.postInvalidate();
            }
        });

        // Callback Register
        // {



        // Image Update

        // }



    }

}
