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

  ImageProcessor imageProcessor;

  imageProcessor.initImages(beginning_frame);
  
  // std::map<int, objectParameters> trackedStaticObjects;
  // int nextFreeID = 0;

  for(int iImage=beginning_frame; iImage<=ending_frame; iImage+=step){  
    imageProcessor.openImage(iImage);
    
    imageProcessor.performSegmentation();

    // cv::medianBlur(movingMask, movingMask, 7);
    // cv::medianBlur(fgMask, fgMask, 7);
    // cv::morphologyEx(fgMask, fgMask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7)));
    // previousImage = inputImage.clone();

    // int labelsCount = cv::connectedComponentsWithStats(fgMask,labelledMask,labelStats,labelCentroids,8,CV_16U);

    // std::vector<objectParameters> newObjects;

    // for (auto &[key, trackedObject]: trackedStaticObjects){
    //   trackedObject.isVisible = false;
    // }

    // for (int i = 1; i < labelsCount; ++i){
    //   newObjects.emplace_back(inputImage, labelStats.row(i));
    // }

    // for (auto &checkedObject: newObjects){
    //   if (checkedObject.area > areaTreshold){
    //     if (!checkedObject.isMoving(movingMask)){
    //       float biggestIntersection = 0;
    //       int biggestIntersectionID = -1;
    //       for (auto &[key, trackedObject]: trackedStaticObjects){
    //         float newIntersection = intersectionOverUnion(checkedObject.bbox, trackedObject.bbox);
    //         if (newIntersection > biggestIntersection){
    //           biggestIntersection = newIntersection;
    //           biggestIntersectionID = key;
    //         }
    //       }
    //       char buf[50];
    //       sprintf(buf,"%.1f, %d", biggestIntersection, biggestIntersectionID);
    //       checkedObject.writeText(buf, green);

    //       if (biggestIntersectionID == -1 || biggestIntersection < intersectionOverUnionTreshold){
    //         checkedObject.staticCounter = step;
    //         trackedStaticObjects.insert(std::pair<int, objectParameters>(nextFreeID, checkedObject));
    //         ++nextFreeID;
    //       }
    //       else {
    //         trackedStaticObjects.at(biggestIntersectionID).isVisible = true;
    //         trackedStaticObjects.at(biggestIntersectionID).staticCounter += step;
    //       }
    //     }
    //   }
    // }

    // for (auto &[key, trackedObject]: trackedStaticObjects){
    //   if (trackedObject.staticCounter > staticTimeTreshold){
    //     char buf[50];
    //     sprintf(buf,"Abandoned luggage ID %d", key);
    //     trackedObject.writeText(buf, red);
    //     trackedObject.drawRect(red);
    //   }
    // }

    imageProcessor.displayImages();
    cv::waitKey(2);
  }
  
  return 0;
}
