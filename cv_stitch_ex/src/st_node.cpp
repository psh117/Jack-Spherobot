#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

using namespace std;

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>

static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
    image_transport::ImageTransport it;
    image_transport::Subscriber left_image_sub;
    image_transport::Subscriber right_image_sub;

    boost::mutex right_img_mutex;
    boost::mutex left_img_mutex;

public:

    ImageConverter(ros::NodeHandle& nh) : it(nh), updated(0)
    {
        // Subscrive to input video feed and publish output video feed
        image_transport::TransportHints hints("compressed", ros::TransportHints(), nh);
        //left_image_sub = it.subscribe("/left_cam/image_rect_color", 1,  &ImageConverter::leftImageCb, this,hints);
        //right_image_sub = it.subscribe("/right_cam/image_rect_color", 1,  &ImageConverter::rightImageCb, this,hints);
        left_image_sub = it.subscribe("/left_cam/image_rect_color", 1,  &ImageConverter::leftImageCb, this,hints);
        right_image_sub = it.subscribe("/right_cam/image_rect_color", 1,  &ImageConverter::rightImageCb, this,hints);
        image_pub = it.advertise("/cv/video", 1);
    }

    ~ImageConverter()
    {
    }

    bool mutex_acq()
    {
        if(left_img_mutex.try_lock())
        {
            if(right_img_mutex.try_lock())
            {
                return true;
            }
            else
            {
                left_img_mutex.unlock();
            }
        }
    }
    bool mutex_unlock()
    {
        left_img_mutex.unlock();
        right_img_mutex.unlock();
    }

    void rightImageCb(const sensor_msgs::ImageConstPtr& msg)
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
        right_img_mutex.lock();
        right_img = cv_ptr->image;
        right_img_mutex.unlock();
        updated |= 1;

    }

    void leftImageCb(const sensor_msgs::ImageConstPtr& msg)
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
        left_img_mutex.lock();
        left_img = cv_ptr->image;
        left_img_mutex.unlock();
        updated |= 2;

    }


    image_transport::Publisher image_pub;

    cv::Mat left_img;
    cv::Mat right_img;

    int updated;
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ros::NodeHandle nh;

  ImageConverter ic(nh);


  cv::Mat panorama;

  std::vector<cv::Mat> dstImages(2);
  int count = 0;
  ROS_INFO("Create");
  cv::Stitcher stitcher = cv::Stitcher::createDefault(true);
  stitcher.setWarper(new cv::SphericalWarperGpu());
  stitcher.setWaveCorrection(false);
  stitcher.setSeamEstimationResol(0.001);
  stitcher.setPanoConfidenceThresh(0.1);

  //stitcher.setSeamFinder(new cv::detail::NoSeamFinder());
  stitcher.setBlender(cv::detail::Blender::createDefault(cv::detail::Blender::MULTI_BAND, true));
  //stitcher.setExposureCompensator(cv::detail::ExposureCompensator::createDefault(cv::detail::ExposureCompensator::NO));
  //stitcher.setExposureCompensator(new cv::detail::NoExposureCompensator());


  //stitcher.set
  ROS_INFO("Done");
  bool firstTime = true;

  int trial = 0;
  ros::Rate rate(10);
  while(ros::ok())
  {

      //ROS_INFO("Looping");
      ros::spinOnce();
      if(ic.updated == 3)
      {

          if(ic.mutex_acq())
          {
              dstImages[0] = ic.left_img;
              dstImages[1] = ic.right_img;
              // gpuImages[0].upload(ic.left_img);
              // gpuImages[1].upload(ic.right_img);
              ic.mutex_unlock();
              if (firstTime)
              {
                  try{
                  cv::Stitcher::Status status = stitcher.estimateTransform(dstImages);
                  if(status != cv::Stitcher::OK)
                  {
                      ROS_INFO("Can't stitch estimation, error code = %d" ,status);
                      trial++;
                      rate.sleep();
                      continue;
                  }
                  }
                  catch(cv::Exception e)
                  {
                      ROS_ERROR("%s",e.what());
                      rate.sleep();
                      continue;
                  }

                     firstTime = false;
                     rate.sleep();
                     continue;
              }
              try{
              cv::Stitcher::Status status = stitcher.composePanorama(dstImages,panorama);

              }

              catch(cv::Exception e)
              {
                  ROS_ERROR("%s",e.what());
                  rate.sleep();
                  firstTime = true;
                  continue;
              }

              //pano_result_gpu.download(panorama);
              //cv::imshow("panorama", panorama);
              //cv::imshow("1", images[0]);
              //cv::imshow("2", images[1]);

              count ++;
              std_msgs::Header header;
              header.seq = count;
              header.stamp = ros::Time::now();
              cv_bridge::CvImage dstImage_bridge(header, sensor_msgs::image_encodings::BGR8, panorama);
              ic.image_pub.publish(dstImage_bridge.toImageMsg());
          }
      }



  }
  return 0;
}
