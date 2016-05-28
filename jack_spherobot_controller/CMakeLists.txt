cmake_minimum_required(VERSION 2.8.3)
project(jack_spherobot_controller)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(jack_node src/jack_node.cpp)

target_link_libraries(jack_node
  ${catkin_LIBRARIES}
)


set(CMAKE_BUILD_TYPE Debug)
