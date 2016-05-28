
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

class JackController
{
    ros::NodeHandle nh;
    ros::Subscriber joy_sub;

    int x_speed;
    int y_speed;


    enum button_map {BTN_A = 0, BTN_B, BTN_X, BTN_Y, BTN_L1, BTN_R1, BTN_BACK, BTN_START, BTN_HOME, BTN_LSTICK, BTN_RSTICK};
    enum axis_map {AXS_LX, AXS_LY, AXS_LTRIG, AXS_RX, AXS_RY, AXS_RTRIG, AXS_BTN_X, AXS_BTN_Y};

    boost::asio::io_service io;
    boost::asio::serial_port serial;

public:
    JackController() : io(), serial(io,"/dev/ttyACM0")
    {
        serial.set_option(boost::asio::serial_port_base::baud_rate(500000));
        joy_sub = nh.subscribe("joy",1,&JackController::joyCallback,this);
    }
    void joyCallback(const sensor_msgs::JoyConstPtr &msg)
    {
        std::stringstream ss;
        ss << "$" << std::fixed << std::setprecision(3) << msg->axes[AXS_LX] << "," << msg->axes[AXS_LY] << "," << msg->axes[AXS_RX] << "\n";
        ROS_INFO("sent: %s",ss.str().c_str());
        writeString(ss.str());
    }
    void writeString(std::string s)
    {
        boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
    }

    std::string readLine()
    {
        //Reading data char by char, code is optimized for simplicity, not speed
        using namespace boost;
        char c;
        std::string result;
        for(;;)
        {
            asio::read(serial,asio::buffer(&c,1));
            switch(c)
            {
                case '\r':
                    break;
                case '\n':
                    return result;
                default:
                    result+=c;
            }
        }
    }

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "jack_controller");

  JackController jc;
  ros::spin();
  return 0;
}
