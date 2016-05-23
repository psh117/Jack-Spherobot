package kr.ac.kw.jack_sphero_vr;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;

import org.ros.android.RosActivity;
import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.ConnectedNode;
import org.ros.node.Node;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMain;
import org.ros.node.NodeMainExecutor;
import org.ros.node.topic.Publisher;

public class JackSpheroVr extends RosActivity implements NodeMain,SensorEventListener
{
    SensorManager sm;
    Sensor rSensor;
    float[] rotMat = new float[9];
    float[] vals = new float[3];


    public JackSpheroVr() {
        super("JackSpheroVR", "JackSpheroVR");
    }


    @Override
    protected void init(NodeMainExecutor nodeMainExecutor) {

        NodeConfiguration nodeConfiguration = NodeConfiguration.newPublic(getRosHostname());
        nodeConfiguration.setMasterUri(getMasterUri());
        nodeMainExecutor.execute(this, nodeConfiguration);
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


        // Callback Register
        // {



        // Image Update

        // }



    }

}
