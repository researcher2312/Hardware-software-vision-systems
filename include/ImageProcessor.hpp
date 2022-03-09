#include "opencv2/imgproc/imgproc.hpp"

class ImageProcessor{
public:
  void openImage(int iImage);

private:
cv::Mat inputImage, previousImage, bgImage, fgMask, movingMask,
          labelledMask, labelStats, labelCentroids;
};