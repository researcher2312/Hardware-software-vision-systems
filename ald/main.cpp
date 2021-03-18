#include <iostream>
#include <cmath>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

typedef cv::Vec<uchar,3> vec_uchar_3;
typedef cv::Vec<char,3> vec_char_3;

constexpr int beginning_frame = 1, ending_frame = 1200, step = 1, treshold = 100;

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
  cv::Mat inputImage, bgImage, fgMask;
  
  openImage(inputImage, beginning_frame);
  bgImage = inputImage.clone();

  for(int iImage=beginning_frame; iImage<=ending_frame; iImage+=step){
    
    openImage(inputImage, iImage);
    fgMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);

    
    for(int jj=0; jj < inputImage.rows; jj++){
      for(int ii=0; ii < inputImage.cols; ii++){
        
        vec_uchar_3 input_pixel = inputImage.at<vec_uchar_3>(jj,ii);
        vec_uchar_3 bg_pixel = bgImage.at<vec_uchar_3>(jj,ii);
        
        int normal = L1_normalisation(input_pixel, bg_pixel);

        if (normal > treshold)
          fgMask.at<uchar>(jj,ii) = 255;
        else
          bgImage.at<vec_uchar_3>(jj,ii) += sigmaDelta_uchar_3(input_pixel, bg_pixel); 
      }
    }

    cv::imshow("InputImage", inputImage);
    cv::imshow("BackgroundImage", bgImage);
    cv::imshow("ForegroundMask", fgMask);
    cv::waitKey(2);
  }
  
  return 0;
}
