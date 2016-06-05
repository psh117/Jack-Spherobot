cmake_minimum_required(VERSION 2.8.3)
project(cv_stitch_ex)

FIND_PACKAGE(CUDA REQUIRED)


find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
)

find_package(OpenCV 2.4.13 REQUIRED)

catkin_package(

)

include_directories(
#  ${OpenCV_SOURCE_DIR}
  ${catkin_INCLUDE_DIRS}
)

add_executable(cv_stitch src/st_node.cpp)

target_link_libraries(cv_stitch
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
)

set(CMAKE_BUILD_TYPE Debug)
