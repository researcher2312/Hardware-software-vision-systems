#ifndef __OBJECT_PARAMETERS_HPP
#define __OBJECT_PARAMETERS_HPP

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"

struct objectParameters{
  bool isVisible = true;// is the object visible ?
  cv::Rect bbox;// bounding box
  int area = 0;// area
  unsigned int staticCounter = 0;     // for how long the object was static ?
  cv::Mat &imageToDrawOn;
  objectParameters(cv::Mat &mainImage, cv::Mat labelStats);
  bool isMoving(cv::Mat &movingMask);
  void drawRect(cv::Scalar color);
  void writeText(char display[], cv::Scalar color);
};

#endif