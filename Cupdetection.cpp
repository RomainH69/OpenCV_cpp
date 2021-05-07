#include "Cupdetection.h"

using namespace cv;

Cupdetection::Cupdetection()
{

}

Mat Cupdetection::colordetection(Mat img, Scalar lower,Scalar upper)
{
  Mat img_HSV, mask;
  cvtColor(img, img_HSV, COLOR_BGR2HSV);

  inRange(img_HSV, lower, upper, mask);
  //imshow("HSV",img_HSV);

  return mask;
}
