#include "objectParameters.hpp"
#include "utilities.hpp"

objectParameters::objectParameters(cv::Mat &mainImage, cv::Mat labelStats):
                                    imageToDrawOn{mainImage}
{
    bbox.x = labelStats.at<int>(cv::CC_STAT_LEFT);
    bbox.y = labelStats.at<int>(cv::CC_STAT_TOP);
    bbox.width = labelStats.at<int>(cv::CC_STAT_WIDTH);
    bbox.height = labelStats.at<int>(cv::CC_STAT_HEIGHT);
    area = labelStats.at<int>(cv::CC_STAT_AREA);
}

void objectParameters::drawRect(cv::Scalar color){    
    cv::rectangle(imageToDrawOn, bbox, color);
}

bool objectParameters::isMoving(cv::Mat &movingMask){
    unsigned int movingPixels = 0;
    for (int i = bbox.x; i < bbox.x+bbox.width; i+=2){
        for (int j = bbox.y; j < bbox.y+bbox.height; j+=2){
            if (movingMask.at<uchar>(j, i) == 255)
            movingPixels += 1;
        }
    }
    float movingCoefficient = (float)movingPixels*4/area;
    // char buf[100];
    // sprintf(buf,"%f",movingCoefficient);
    // cv::putText(imageToDrawOn,buf , cv::Point(bbox.x,bbox.y),
    //             cv::FONT_HERSHEY_PLAIN, 0.8, green, 1);
    if (movingCoefficient > 0.2)
        return true;
    else
        return false;
}