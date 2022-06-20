#include <iostream>
#include "Ros2GuiNode.hpp"

#include "QApplication"
#include <rclcpp/rclcpp.hpp>


int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  rclcpp::init(argc, argv);

  MainWindow mw;
  mw.show();
  
  return app.exec();
}