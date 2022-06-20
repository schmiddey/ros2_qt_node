#ifndef ROS2GUINODE_H_
#define ROS2GUINODE_H_


#include <rclcpp/rclcpp.hpp>

#include <QMainWindow>
#include <QTimer>

#include <std_msgs/msg/detail/float32__struct.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/float32.hpp>
#include <image_transport/image_transport.hpp>
#include <image_transport/subscriber.hpp>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/opencv.hpp>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow, public rclcpp::Node
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow() override;

private slots:
  void timer_spin_callback();

  void pb_topic_vid_clicked()
  {
    RCLCPP_INFO(this->get_logger(), "pb_topic_vid clicked");
    _sub_cam.shutdown();
    _sub_cam = image_transport::create_subscription(
      this, "/image_raw",
      std::bind(&MainWindow::callbackCamera, this, std::placeholders::_1),
      "compressed", rmw_qos_profile_sensor_data);
  }
  
  void pb_pub_clicked()
  {
    RCLCPP_INFO(this->get_logger(), "pb_pub clicked");
    std_msgs::msg::String msg;
    msg.data = "Hello Ros2Gui";
    msg.data += ": " + std::to_string(_cnt++);
    _pub_string->publish(msg);
  }

  void show_black();

private: 
  void sub_str_callback(const std_msgs::msg::String::SharedPtr msg);



  void callbackCamera(const sensor_msgs::msg::Image::ConstSharedPtr& msg);



  cv::Mat resize_to(cv::Mat img, const int width, const int height)
  {
    cv::Mat resized;
    cv::resize(img, resized, cv::Size(width, height));
    return resized;
  }

  cv::Mat resize_to400(cv::Mat img)
  {
    return resize_to(img, 400, 320);
  }

  cv::Mat resize_to800(cv::Mat input)
  {
    // cv::Mat output;
    // cv::resize(input, output, cv::Size(800, 600));
    // return output;
    return resize_to(input, 800, 600);
  }

private: 

  Ui::MainWindow* ui;

  QTimer* _timer_spin;  

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _sub_string;
  image_transport::Subscriber _sub_cam;

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _pub_string;

  std::size_t _cnt = 0;

  cv::Mat _img_drive;
};


#endif  //ROS2GUINODE_H_
