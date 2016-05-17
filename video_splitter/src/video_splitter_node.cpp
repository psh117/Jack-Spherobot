#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub1;
  image_transport::Publisher image_pub2;
  image_transport::Publisher image_pub3;
  
public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/usb_cam/image_rect_color", 1,
      &ImageConverter::imageCb, this);
    image_pub1 = it_.advertise("/split_image/video1", 1);
    image_pub2 = it_.advertise("/split_image/video2", 1);
    image_pub3 = it_.advertise("/split_image/video3", 1);

    //cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    //cv::destroyWindow(OPENCV_WINDOW);
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
    cv_bridge::CvImage img1;
    cv_bridge::CvImage img2;
    cv_bridge::CvImage img3;

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
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
