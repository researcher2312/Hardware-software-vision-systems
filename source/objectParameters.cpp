#include "coefficients.hpp"
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
    if (movingCoefficient > movingCoefficientTreshold)
        return true;
    else
        return false;
}

void objectParameters::writeText(char text[], cv::Scalar color){
    cv::putText(imageToDrawOn, text, cv::Point(bbox.x,bbox.y),
                cv::FONT_HERSHEY_PLAIN, 0.8, color, 1);
}