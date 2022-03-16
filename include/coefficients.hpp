#include <string>

constexpr int beginning_frame = 1, ending_frame = 1200, step = 5,
              foregroundTreshold = 60, movingTreshold = 20, areaTreshold = 400,
              staticTimeTreshold = 100;

constexpr float movingCoefficientTreshold = 0.2, intersectionOverUnionTreshold = 0.5;

const std::string imageFoldername {"/home/lsriw/pets_2006/"};