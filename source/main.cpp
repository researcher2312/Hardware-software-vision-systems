#include <iostream>
#include <cmath>
#include <map>
#include <vector>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "coefficients.hpp"
#include "objectParameters.hpp"
#include "utilities.hpp"
#include "ImageProcessor.hpp"

int main(){
  ImageProcessor imageProcessor(beginning_frame);
  
  for(int iImage=beginning_frame; iImage<=ending_frame; iImage+=step){  
    imageProcessor.openImage(iImage);
    imageProcessor.performSegmentation();
    imageProcessor.applyFilters();
    imageProcessor.copyInputToPrevious();
    imageProcessor.connectLabels();
    imageProcessor.highlightFoundObjects();
    imageProcessor.displayImages();
    cv::waitKey(2);
  }
  return 0;
}