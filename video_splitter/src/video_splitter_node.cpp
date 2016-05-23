#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Joy.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

  ros::Subscriber orientation_sub;
  ros::Subscriber joy_sub;

  float yaw;
  float yaw_home;
  float roll;
  float pitch;

  int count;

  sensor_msgs::Joy joy_msg;

  enum button_map {BTN_A = 0, BTN_B, BTN_X, BTN_Y, BTN_L1, BTN_R1, BTN_BACK, BTN_START, BTN_HOME, BTN_LSTICK, BTN_RSTICK};
  enum axis_map {AXS_LX, AXS_LY, AXS_LTRIG, AXS_RX, AXS_RY, AXS_RTRIG, AXS_BTN_X, AXS_BTN_Y};

public:
  ImageConverter()
      : it_(nh_), yaw(0.0), yaw_home(0.0), roll(0.0), pitch(0.0), count(0)
  {
    // Subscrive to input video feed and publish output video feed
     joy_msg.axes.resize(8,0.0);
     joy_msg.buttons.resize(8,0);
    // cit.subscribe(nh_,"/usb_cam/image_rect_color",1, &ImageConverter::imageCb, this);
     image_transport::TransportHints hints("compressed", ros::TransportHints(), nh_);
     image_sub_ = it_.subscribe("/usb_cam/image_rect_color", 1,  &ImageConverter::imageCb, this,hints);
    image_pub_ = it_.advertise("/vr_image/video", 1);
    orientation_sub = nh_.subscribe("jack_vr/orientation",1,&ImageConverter::orientationCallback,this);
    joy_sub = nh_.subscribe("/joy",1,&ImageConverter::joyCallback, this);
    //cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    //cv::destroyWindow(OPENCV_WINDOW);
  }

  void orientationCallback(const std_msgs::Float32MultiArrayConstPtr& msg)
  {
      yaw = msg->data[0] ;
      roll = msg->data[1] ;
      pitch = msg->data[2];
  }

  void joyCallback(const sensor_msgs::JoyConstPtr& msg)
  {
      msg->buttons[8];
      joy_msg = *msg;
      if(msg->buttons[BTN_HOME])
      {
          yaw_home = yaw;
          ROS_INFO("yaw_home set to %f",yaw_home);
      }
  }

  void safe_img_copy(cv::Mat& dst, cv::Mat& src, int start_x, int start_y)
  {

      for(int i=0; i<dst.rows; i++)
      {
          for(int j=0; j<dst.cols; j++)
          {
              for(int c=0; c<dst.channels(); c++)
              {
                  if ( (start_x + j) < 0 && (start_x + j) >= src.cols || (start_y + i) < 0 && (start_y + i) >= src.rows )
                      dst.data[(i * dst.cols + j) * dst.channels() + c ] = 0;
                  else dst.data[(i * dst.cols + j) * dst.channels() + c ] = src.data[((i+start_y) * src.cols + (j+start_x)) * src.channels() + c];
              }
          }
      }
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }


    // Yaw Process

    float yaw_deg = yaw - yaw_home; // +-120
    float pitch_deg = pitch + 90;
    int pitch_pixel = pitch_deg * 2.666667;
    int yaw_pixel = yaw_deg * 3 ;
    int dst_size = 240;
    int yaw_size = dst_size * sqrt(2) + 2;
    int half_yaw_size = yaw_size / 2;
    cv::Mat yawImg(yaw_size,yaw_size,CV_8UC3);


    int x_start = yaw_pixel + cv_ptr->image.cols / 2 - half_yaw_size;
    int y_start = pitch_pixel + cv_ptr->image.rows / 2 - half_yaw_size;

    //yawImg = cv_ptr->image(cv::Rect(cv::Point(x_start, y_start),
    //                                cv::Point(x_start + yaw_size,   y_start + yaw_size)));


    safe_img_copy(yawImg, cv_ptr->image,x_start, y_start);



    // Roll Process
    cv::Mat rotateImg;
    cv::Point2f pt (yawImg.cols/2., yawImg.rows/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt,roll,1.0);
    cv::warpAffine(yawImg, rotateImg, r, cv::Size(yawImg.cols, yawImg.rows));

    int size_diff = yaw_size - dst_size;
    int half_size_diff = size_diff / 2;
    cv::Mat dstImg = rotateImg(cv::Rect(cv::Point(half_size_diff,half_size_diff), cv::Point(yaw_size-half_size_diff,yaw_size-half_size_diff)));

    count ++;
    std_msgs::Header header;
    header.seq = count;
    header.stamp = ros::Time::now();
    cv_bridge::CvImage dstImage_bridge(header, sensor_msgs::image_encodings::BGR8, dstImg);
    image_pub_.publish(dstImage_bridge.toImageMsg());
    /*
    img1.image.create(480,640,CV_8UC3);
    img1.encoding = sensor_msgs::image_encodings::BGR8;
    img2.image.create(480,640,CV_8UC3);
    img2.encoding = sensor_msgs::image_encodings::BGR8;
    img3.image.create(480,640,CV_8UC3);
    img3.encoding = sensor_msgs::image_encodings::BGR8;

    for(int x=0;x<640;x++)
    {
        for(int y=0;y<480;y++)
        {
            for(int c=0;c<3;c++)
            {
                img1.image.data[(x + y * 640) * 3 + c] = cv_ptr->image.data[(x      +   (y+300) * 1920) * 3 + c];
                img2.image.data[(x + y * 640) * 3 + c] = cv_ptr->image.data[((x+640) +  (y+300) * 1920) * 3 + c];
                img3.image.data[(x + y * 640) * 3 + c] = cv_ptr->image.data[((x+1280) + (y+300) * 1920) * 3 + c];

            }
        }
    }
    // Draw an example circle on the video stream

    // Update GUI Window
    //cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    //cv::waitKey(3);

    // Output modified video stream
    image_pub1.publish(img1.toImageMsg());
    image_pub2.publish(img2.toImageMsg());
    image_pub3.publish(img3.toImageMsg());
    */
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
