#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"

typedef cv::Vec<uchar,3> vec_uchar_3;
typedef cv::Vec<char,3> vec_char_3;

const auto blue = cv::Scalar(255, 0, 0);
const auto green = cv::Scalar(0, 255, 0);
const auto red = cv::Scalar(0, 0, 255);

void openImage(cv::Mat &inputImage, int iImage);
int L1_normalisation(vec_uchar_3 a, vec_uchar_3 b);
uchar tresholding(vec_uchar_3 a, vec_uchar_3 b, int treshold);
vec_char_3 sigmaDelta_uchar_3(vec_uchar_3 a, vec_uchar_3 b);
float intersection_over_union(cv::Rect r1, cv::Rect r2);