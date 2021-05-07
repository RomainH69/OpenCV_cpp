#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class Cupdetection
{
  public :
  Cupdetection();
  cv::Mat colordetection(cv::Mat img, cv::Scalar lower,cv::Scalar upper);
};
