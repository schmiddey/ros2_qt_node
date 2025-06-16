#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <opencv2/opencv.hpp>

// Test OpenCV functionality that's used in the main application
class OpenCVTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a simple test image
        test_image = cv::Mat::zeros(480, 640, CV_8UC3);
        cv::rectangle(test_image, cv::Point(100, 100), cv::Point(300, 200), cv::Scalar(255, 255, 255), -1);
    }

    cv::Mat test_image;
};

TEST_F(OpenCVTest, ImageResize) {
    cv::Mat resized;
    cv::resize(test_image, resized, cv::Size(800, 600));
    
    EXPECT_EQ(resized.cols, 800);
    EXPECT_EQ(resized.rows, 600);
    EXPECT_EQ(resized.channels(), 3);
}

TEST_F(OpenCVTest, ImageResizeToSpecificDimensions) {
    cv::Mat resized;
    cv::resize(test_image, resized, cv::Size(400, 320));
    
    EXPECT_EQ(resized.cols, 400);
    EXPECT_EQ(resized.rows, 320);
}

// Test basic message formatting functionality used in the application
TEST(MessageTest, StringMessageFormatting) {
    std_msgs::msg::String msg;
    msg.data = "Hello Ros2Gui";
    
    EXPECT_EQ(msg.data, "Hello Ros2Gui");
    
    // Test message formatting with counter (as used in pb_pub_clicked)
    std::size_t counter = 42;
    msg.data = "Hello Ros2Gui";
    msg.data += ": " + std::to_string(counter);
    
    EXPECT_EQ(msg.data, "Hello Ros2Gui: 42");
}

TEST(UtilityTest, StringConversion) {
    // Test string to const char* conversion as used in the GUI
    std::string test_string = "test message";
    const char* c_str = test_string.c_str();
    
    EXPECT_STREQ(c_str, "test message");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}