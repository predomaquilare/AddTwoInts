#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class SumPublisher : public rclcpp::Node
{
public:
    SumPublisher() : Node("SumPub")
    {
        RCLCPP_INFO(this->get_logger(), "SumPub starting");
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("number_topic", 10);
        this->CatchTwoNum();
    }

private:
    void CatchTwoNum()
    {
        auto msg1 = std_msgs::msg::Int32();
        auto msg2 = std_msgs::msg::Int32();
        std::cout << "Digite o primeiro numero: ";
        std::cin >> msg1.data;
        std::cout << "Digite o segundo numero: ";
        std::cin >> msg2.data;

        publisher_->publish(msg1);
        publisher_->publish(msg2);
    }

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SumPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
