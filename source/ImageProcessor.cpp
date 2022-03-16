#include "ImageProcessor.hpp"
#include "coefficients.hpp"
#include "utilities.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


void ImageProcessor::openImage(int iImage){
  char buffer[20];
  sprintf(buffer,"in%06d.jpg",iImage);
  inputImage = cv::imread(imageFoldername + buffer);
}

void ImageProcessor:: initImages(int iImage){
  openImage(iImage);
  bgImage = inputImage.clone();
  previousImage = inputImage.clone();
  fgMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);
  movingMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);
}

void ImageProcessor::performSegmentation(){
  for(int jj=0; jj < inputImage.rows; jj++){
      for(int ii=0; ii < inputImage.cols; ii++){
        
        vec_uchar_3 inputPixel = inputImage.at<vec_uchar_3>(jj,ii);
        vec_uchar_3 bgPixel = bgImage.at<vec_uchar_3>(jj,ii);
        vec_uchar_3 previousPixel = previousImage.at<vec_uchar_3>(jj,ii);
        
        movingMask.at<uchar>(jj,ii) = tresholding(inputPixel, previousPixel, movingTreshold);
        fgMask.at<uchar>(jj,ii) = tresholding(inputPixel, bgPixel, foregroundTreshold);
        
        if(fgMask.at<uchar>(jj,ii) + movingMask.at<uchar>(jj,ii) == 0)
          bgImage.at<vec_uchar_3>(jj,ii) += sigmaDelta_uchar_3(inputPixel, bgPixel);
      }
    }
}

void ImageProcessor::applyFilters(){
  cv::medianBlur(movingMask, movingMask, 7);
  cv::medianBlur(fgMask, fgMask, 7);
  cv::morphologyEx(fgMask, fgMask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7)));
}


void ImageProcessor::displayImages(){
  cv::imshow("Move Mask", movingMask);
  cv::imshow("Foreground Mask", fgMask);
  cv::imshow("Background Image", bgImage);
  cv::imshow("Input Image", inputImage);
}