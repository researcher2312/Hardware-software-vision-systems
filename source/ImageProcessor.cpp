#include "ImageProcessor.hpp"
#include "coefficients.hpp"
#include "utilities.hpp"

#include "opencv2/highgui/highgui.hpp"

void ImageProcessor::openImage(int iImage){
  char buffer[20];
  sprintf(buffer,"in%06d.jpg",iImage);
  inputImage = cv::imread(imageFoldername+buffer);
}

void ImageProcessor:: initImages(int iImage){
    bgImage = inputImage.clone();
  previousImage = inputImage.clone();
  fgMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);
  movingMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);
}