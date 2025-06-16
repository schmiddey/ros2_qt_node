#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

// Test basic ROS2 functionality
class BasicRos2Test : public ::testing::Test {
protected:
    void SetUp() override {
        if (!rclcpp::ok()) {
            rclcpp::init(0, nullptr);
        }
    }

    void TearDown() override {
        // Note: We don't call rclcpp::shutdown() here as it may be needed by other tests
    }
};

TEST_F(BasicRos2Test, NodeCreation) {
    auto node = rclcpp::Node::make_shared("test_node");
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->get_name(), std::string("test_node"));
}

TEST_F(BasicRos2Test, PublisherCreation) {
    auto node = rclcpp::Node::make_shared("test_publisher_node");
    auto publisher = node->create_publisher<std_msgs::msg::String>("/test_topic", 10);
    EXPECT_NE(publisher, nullptr);
}

TEST_F(BasicRos2Test, SubscriberCreation) {
    auto node = rclcpp::Node::make_shared("test_subscriber_node");
    auto callback = [](const std_msgs::msg::String::SharedPtr) {};
    auto subscriber = node->create_subscription<std_msgs::msg::String>("/test_topic", 10, callback);
    EXPECT_NE(subscriber, nullptr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}