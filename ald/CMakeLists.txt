cmake_minimum_required(VERSION 3.13)
project(ald)

set(CMAKE_CXX_STANDARD 17)

add_executable(ald main.cpp)

# == OpenCV (3.4.5.0) / (4.0.1) configuration ==
# Where to find CMake modules and OpenCV
set(OpenCV_DIR "/opt/opencv/opencv/build/")  #check path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# Linking
target_link_libraries(ald ${OpenCV_LIBS})
