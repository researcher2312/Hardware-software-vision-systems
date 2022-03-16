#include "opencv2/imgproc/imgproc.hpp"

class ImageProcessor{
public:
  void openImage(int iImage);
  void initImages(int iImage);
  void performSegmentation();
  void displayImages();
  void applyFilters();
  void copyInputToPrevious(){previousImage = inputImage.clone();};

private:
cv::Mat inputImage, previousImage, bgImage, fgMask, movingMask,
          labelledMask, labelStats, labelCentroids;
};