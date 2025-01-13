cmake_minimum_required(VERSION 3.8)
project(SumPackage)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(SumPub src/SumPublisher.cpp)
add_executable(SumSub src/SumSubscriber.cpp)

ament_target_dependencies(SumPub rclcpp std_msgs)
ament_target_dependencies(SumSub rclcpp std_msgs)

install(TARGETS
  SumSub
  SumPub
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
