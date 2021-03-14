#include <iostream>
#include <cmath>

#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"

typedef cv::Vec<uchar,3> vec_uchar_3;

constexpr int beginning_frame = 1, ending_frame = 1200, step = 10;

void openImage(cv::Mat &inputImage, int iImage){
  char buffer[100];
  std::string s_sequencePath = "/home/researcher/ald/pets_2006/";
  sprintf(buffer,"in%06d.jpg",iImage);
  inputImage = cv::imread(s_sequencePath+buffer);
}

int L1_normalisation(vec_uchar_3 a, vec_uchar_3 b){
  int sum = 0;
  for(int i=0; i<2; ++i){
    sum += abs((int)(a[i] - b[i]));
  }
  return sum;
}

int main(){
  cv::Mat inputImage, bgImage, fgMask;
  
  openImage(inputImage, beginning_frame);
  fgMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);
  bgImage = inputImage.clone();

  for(int iImage=beginning_frame; iImage<ending_frame+1; iImage+=step){
    openImage(inputImage, iImage);
    
    for(int jj=0; jj < inputImage.rows; jj++){
      for(int ii=0; ii < inputImage.cols; ii++){
        vec_uchar_3 fg_pixel = inputImage.at<vec_uchar_3>(jj,ii);
        vec_uchar_3 bg_pixel = bgImage.at<vec_uchar_3>(jj,ii);
        
        int normal = L1_normalisation(fg_pixel, bg_pixel);
        if (normal > 0){
          bgImage.at<vec_uchar_3>(jj,ii) = bgImage.at<vec_uchar_3>(jj,ii) + 1;
        }
        if (normal < 0){
          bgImage.at<vec_uchar_3>(jj,ii) = bgImage.at<vec_uchar_3>(jj,ii) - 1;
        }
      }
    }
    
    std::cerr << iImage << std::endl;

    cv::imshow("Inputimage", inputImage);
    cv::imshow("Backgroundimage", bgImage);
    cv::waitKey(5);
  }
  
  
  
  
  return 0;
}
