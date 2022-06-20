#include "Ros2GuiNode.hpp"

#include "ui_ros2_gui.h"

#include <cv_bridge/cv_bridge.h>

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    rclcpp::Node("ros2_gui_node"),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

  _timer_spin = new QTimer(this);
  connect(_timer_spin, SIGNAL(timeout()), this, SLOT(timer_spin_callback()));

  //btn
  connect(ui->pB_topic_vid, SIGNAL(clicked()), this, SLOT(pb_topic_vid_clicked()));
  connect(ui->pB_pub, SIGNAL(clicked()), this, SLOT(pb_pub_clicked()));


  _sub_string = this->create_subscription<std_msgs::msg::String>("/ros2_gui/string", 10, std::bind(&MainWindow::sub_str_callback, this, std::placeholders::_1));

  _pub_string = this->create_publisher<std_msgs::msg::String>("/ros2_gui/string", 10);


  // image_transport::Subscriber _sub_cam_drive;
  // //image_transport::Subscriber _sub_cam_thermo;



  _timer_spin->start(5);
  // cv::namedWindow("drive");
}

void MainWindow::show_black()
{
  cv::Mat black(cv::Size(400, 320), CV_8UC3, cv::Scalar(0, 0, 0));

  QImage imgIn= QImage((uchar*) black.data, black.cols, black.rows, black.step, QImage::Format_RGB888);
  // ui->label_video_drive->setPixmap(QPixmap::fromImage(imgIn));
  ui->label_video->setPixmap(QPixmap::fromImage(imgIn));
}

void MainWindow::callbackCamera(const sensor_msgs::msg::Image::ConstSharedPtr& msg)
{
  try
  {
    // First let cv_bridge do its magic
    cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
    cv::Mat img = cv_ptr->image;

    cv::Mat scaled = this->resize_to800(img);

    QImage imgIn= QImage((uchar*) scaled.data, scaled.cols, scaled.rows, scaled.step, QImage::Format_RGB888);
    ui->label_video->setPixmap(QPixmap::fromImage(imgIn));
    // ui->label_video_drive->bac


    // cv::imshow("drive", img);
    // cv::waitKey(5);
  }
  catch (cv_bridge::Exception& e)
  {
  }
}


void MainWindow::sub_str_callback(const std_msgs::msg::String::SharedPtr msg)
{
  RCLCPP_INFO(this->get_logger(), "sub_str_callback: %s", msg->data.c_str());
  ui->lineEdit_sub->setText(msg->data.c_str());
}








MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_spin_callback()
{
  // std::cout << "timer" << std::endl;
  rclcpp::spin_some(this->get_node_base_interface());
}