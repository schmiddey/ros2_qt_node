cmake_minimum_required(VERSION 3.8)
project(ros2_qt_node)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)


find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
# find_package(Qt5Widgets)

include_directories(include)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


set(dependencies rclcpp
std_msgs
sensor_msgs
geometry_msgs
std_srvs
nav_msgs
tf2
tf2_ros
visualization_msgs
image_transport
cv_bridge) 


add_executable(ros2_qt_node
    src/ros2_gui.ui
    src/Ros2GuiNode.cpp
    src/main.cpp
)
ament_target_dependencies(ros2_qt_node ${dependencies})

target_link_libraries(ros2_qt_node Qt5::Widgets Qt5::Core)


# set(dependencies rclcpp) #todo add other deps here

# add_executable(exec src/path_to_cpp.cpp)
# ament_target_dependencies(exec ${dependencies})

install(TARGETS ros2_qt_node
  DESTINATION lib/${PROJECT_NAME})

# install(DIRECTORY images
#   DESTINATION share/${PROJECT_NAME}
#   FILES_MATCHING PATTERN "*.png" PATTERN "*.svg")

# install(DIRECTORY launch
#   DESTINATION share/${PROJECT_NAME})


ament_package()
