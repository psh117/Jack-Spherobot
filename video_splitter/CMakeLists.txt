cmake_minimum_required(VERSION 2.8.3)
project(video_splitter)


find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  compressed_image_transport
  roscpp
  sensor_msgs
  std_msgs
)

catkin_package(

)


include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(video_splitter_node src/video_splitter_node.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(video_splitter_node
  ${catkin_LIBRARIES}
)

