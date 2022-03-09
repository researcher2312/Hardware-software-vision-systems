#include "utilities.hpp"



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

float intersectionOverUnion(cv::Rect r1, cv::Rect r2){
    // Extract the required values
    unsigned int xmin_a=r1.x;
    unsigned int xmax_a=r1.x+r1.width;
    unsigned int ymin_a=r1.y;
    unsigned int ymax_a=r1.y +r1.height;
    unsigned int xmin_b=r2.x;
    unsigned int xmax_b=r2.x+r2.width;
    unsigned int ymin_b=r2.y;
    unsigned int ymax_b=r2.y +r2.height;
    // Compute the max/min
    unsigned int xA = std::max(xmin_a, xmin_b);
    unsigned int yA = std::max(ymin_a, ymin_b);
    unsigned int xB = std::min(xmax_a, xmax_b);
    unsigned int yB = std::min(ymax_a, ymax_b);
    // Compute intersection area
    unsigned int interArea = (xB - xA)*(yB - yA);
    // Compute both bounding box areas
    unsigned int boxAArea = (r1.width)*(r1.height);
    unsigned int boxBArea = (r2.width)*(r2.height);
    // Compute Intersection over Union
    float iou =float(interArea) /float(boxAArea + boxBArea -interArea);
    // Return value
    return iou;
}