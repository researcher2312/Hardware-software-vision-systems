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

int main(){
  cv::Mat inputImage, bgImage, fgMask, previousImage, movingMask,
          labelledMask, labelStats, labelCentroids;
  
  openImage(inputImage, beginning_frame);
  bgImage = inputImage.clone();
  previousImage = inputImage.clone();
  fgMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);
  movingMask = cv::Mat::zeros(inputImage.rows, inputImage.cols, CV_8U);

  std::map<int, objectParameters> trackedStaticObjects;
  int nextFreeID = 0;

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
    cv::morphologyEx(fgMask, fgMask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7)));
    previousImage = inputImage.clone();

    int labelsCount = cv::connectedComponentsWithStats(fgMask,labelledMask,labelStats,labelCentroids,8,CV_16U);

    std::vector<objectParameters> newObjects;

    for (auto &[key, trackedObject]: trackedStaticObjects){
      trackedObject.isVisible = false;
    }

    for (int i = 1; i < labelsCount; ++i){
      newObjects.emplace_back(inputImage, labelStats.row(i));
    }

    for (auto &checkedObject: newObjects){
      if (checkedObject.area > areaTreshold){
        if (!checkedObject.isMoving(movingMask)){
          float biggestIntersection = 0;
          int biggestIntersectionID = -1;
          for (auto &[key, trackedObject]: trackedStaticObjects){
            float newIntersection = intersectionOverUnion(checkedObject.bbox, trackedObject.bbox);
            if (newIntersection > biggestIntersection){
              biggestIntersection = newIntersection;
              biggestIntersectionID = key;
            }
          }
          char buf[50];
          sprintf(buf,"%.1f, %d", biggestIntersection, biggestIntersectionID);
          checkedObject.writeText(buf, green);
          
          if (biggestIntersectionID == -1 || biggestIntersection < intersectionOverUnionTreshold){
            checkedObject.staticCounter = step;
            trackedStaticObjects.insert(std::pair<int, objectParameters>(nextFreeID, checkedObject));
            ++nextFreeID;
          }
          else {
            trackedStaticObjects.at(biggestIntersectionID).isVisible = true;
            trackedStaticObjects.at(biggestIntersectionID).staticCounter += step;
          }

        }
      }
    }

    cv::imshow("Move Mask", movingMask);
    cv::imshow("Foreground Mask", fgMask);
    cv::imshow("Background Image", bgImage);
    cv::imshow("Input Image", inputImage);
    cv::waitKey(2);
  }
  
  return 0;
}
