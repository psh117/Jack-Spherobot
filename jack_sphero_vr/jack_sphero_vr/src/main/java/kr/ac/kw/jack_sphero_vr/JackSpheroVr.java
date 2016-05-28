package kr.ac.kw.jack_sphero_vr;

import android.graphics.Bitmap;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.ImageView;
import org.ros.android.BitmapFromCompressedImage;
import org.ros.android.MessageCallable;
import org.ros.android.RosActivity;
import org.ros.android.view.RosImageView;
import org.ros.concurrent.CancellableLoop;
import org.ros.message.MessageListener;
import org.ros.namespace.GraphName;
import org.ros.namespace.NameResolver;
import org.ros.node.ConnectedNode;
import org.ros.node.Node;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMain;
import org.ros.node.NodeMainExecutor;
import org.ros.node.topic.Publisher;
import org.ros.node.topic.Subscriber;
import java.io.IOException;

import sensor_msgs.CompressedImage;

public class JackSpheroVr extends RosActivity implements NodeMain,SensorEventListener
{
    SensorManager sm;
    Sensor rSensor;
    float[] rotMat = new float[9];
    float[] vals = new float[3];
    private RosImageView<sensor_msgs.CompressedImage> cameraView_L,cameraView_R;
    public JackSpheroVr() {
        super("JackSpheroVR", "JackSpheroVR");
    }


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


    }

    @Override
    protected void onPause() {
        super.onPause();
        sm.unregisterListener(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        sm.registerListener(this,rSensor,SensorManager.SENSOR_DELAY_FASTEST);
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
                ++this.sequenceNumber;
                Thread.sleep(15L);
            }
        });


        Subscriber subscriber = connectedNode.newSubscriber("usb_cam/image_raw/compressed", "sensor_msgs/CompressedImage");
        subscriber.addMessageListener(new MessageListener() {
            //method 1
            public void onNewMessage(final Object message) {
               /*ameraView_L.post(new Runnable() {
                    @Override
                    public void run() {
                        cameraView_L.setImageBitmap((Bitmap) new BitmapFromCompressedImage().call((sensor_msgs.CompressedImage)message));

                    }//bitmap으로 받아야
                });
                cameraView_R.post(new Runnable() {
                    @Override
                    public void run() {
                        cameraView_R.setImageBitmap((Bitmap) new BitmapFromCompressedImage().call((sensor_msgs.CompressedImage)message));
                    }
                });
                cameraView_L.postInvalidate();
                cameraView_R.postInvalidate();*/

                //method2
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        cameraView_L.setImageBitmap((Bitmap) new BitmapFromCompressedImage().call((sensor_msgs.CompressedImage)message));
                        cameraView_R.setImageBitmap((Bitmap) new BitmapFromCompressedImage().call((sensor_msgs.CompressedImage)message));
                    }
                });
                cameraView_L.postInvalidate();
                cameraView_R.postInvalidate();

            }
        });

        // Callback Register
        // {



        // Image Update

        // }



    }

}
