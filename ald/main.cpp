#include <iostream>
#include <cmath>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

typedef cv::Vec<uchar,3> vec_uchar_3;
typedef cv::Vec<char,3> vec_char_3;

constexpr int beginning_frame = 1, ending_frame = 1200, step = 5,
              foregroundTreshold = 60, movingTreshold = 20;

void openImage(cv::Mat &inputImage, int iImage){
  char buffer[100];
  std::string s_sequencePath = "/home/researcher/hs-vision/ald/pets_2006/";
  sprintf(buffer,"in%06d.jpg",iImage);
  inputImage = cv::imread(s_sequencePath+buffer);
}

int L1_normalisation(vec_uchar_3 a, vec_uchar_3 b){
  int sum = 0;
  for(int i=0; i<3; ++i){
    sum += abs((int)a[i] - (int)b[i]);
  }
  return sum;
}

uchar tresholding(vec_uchar_3 a, vec_uchar_3 b, int treshold){
  if (L1_normalisation(a, b) > treshold)
    return 255;
  else
    return 0;
}

void drawRect(){
  
}

vec_char_3 sigmaDelta_uchar_3(vec_uchar_3 a, vec_uchar_3 b){
  vec_char_3 sigma(0,0,0);
  for(int i=0; i<3; ++i){
    if ((int)a[i] - (int)b[i] > 0){
      sigma[i] = 1;
    }
    else if ((int)a[i] - (int)b[i] < 0){
      sigma[i] = -1;
    }
  }
  return sigma;
}

int main(){
  cv::Mat inputImage, bgImage, fgMask, previousImage, movingMask,
          labelledMask, labelStats, labelCentroids;
  
  openImage(inputImage, beginning_frame);
  bgImage = inputImage.clone();
  previousImage = inputImage.clone();
  fgMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);
  movingMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);

  for(int iImage=beginning_frame; iImage<=ending_frame; iImage+=step){  
    openImage(inputImage, iImage);
    
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

    cv::medianBlur(movingMask, movingMask, 7);
    cv::medianBlur(fgMask, fgMask, 7);
    cv::morphologyEx(fgMask, fgMask,  cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7)));
    previousImage = inputImage.clone();

    int labelsCount = cv::connectedComponentsWithStats(fgMask,labelledMask,labelStats,labelCentroids,8,CV_16U);

    for (int i = 1; i < labelsCount; ++i){
      int area = labelStats.at<int>(i,cv::CC_STAT_AREA);
      cv::Rect bbox;
      bbox.x = labelStats.at<int>(i,cv::CC_STAT_LEFT);
      bbox.y = labelStats.at<int>(i,cv::CC_STAT_TOP);
      bbox.width = labelStats.at<int>(i,cv::CC_STAT_WIDTH);
      bbox.height = labelStats.at<int>(i,cv::CC_STAT_HEIGHT);
      cv::rectangle(inputImage, bbox, cv::Scalar(255, 0, 0));
    }

    cv::imshow("Input Image", inputImage);
    cv::imshow("Background Image", bgImage);
    cv::imshow("Foreground Mask", fgMask);
    cv::imshow("Move Mask", movingMask);
    cv::waitKey(2);
  }
  
  return 0;
}
