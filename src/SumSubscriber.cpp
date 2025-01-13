#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class SumSub : public rclcpp::Node
{
public:
    SumSub() : Node("SumSub"), first_number_(0), second_number_(0), sum(0), received_first_(false)
    {
        RCLCPP_INFO(this->get_logger(), "SumSub starting");

        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "number_topic", 10,
            std::bind(&SumSub::SumTwoNum, this, std::placeholders::_1));

        publisher_ = this->create_publisher<std_msgs::msg::Int32>("result_topic", 10);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&SumSub::PublishSum, this));
    }

private:
    void SumTwoNum(const std_msgs::msg::Int32::SharedPtr msg)
    {
        if (!received_first_)
        {
            first_number_ = msg->data;
            received_first_ = true;
        }
        else
        {
            second_number_ = msg->data;
            received_first_ = false;
            sum = first_number_ + second_number_;
        }
    }

    void PublishSum()
    {
        if (received_first_)
        {
            return;
        }

        auto msg = std_msgs::msg::Int32();
        msg.data = this->sum;
        publisher_->publish(msg);
    }

    int first_number_;
    int second_number_;
    int sum;
    bool received_first_;

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SumSub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
