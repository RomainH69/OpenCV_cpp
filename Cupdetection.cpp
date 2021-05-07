#include "Cupdetection.h"

Cupdetection::Cupdetection()
{

}

cv::Mat Cupdetection::colordetection(cv::Mat img, cv::Scalar lower,cv::Scalar upper)
{
  cv::Mat img_HSV, mask;
  cv::cvtColor(img, img_HSV, cv::COLOR_BGR2HSV);

  cv::inRange(img_HSV, lower, upper, mask);

  return mask;
}
