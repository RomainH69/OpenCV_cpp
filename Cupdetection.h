#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;

class Cupdetection
{
  public :
  Cupdetection(int _hmin, int _hmax, int _smin, int _smax, int _vmin, int _vmax, Scalar _color);
  void OK_callback(int state, void* userData);
  void calibrateHSV(VideoCapture cap);
  void colordetection(Mat &img, Mat &mask);
  void colordetection_bgr(Mat &img, Scalar &lower,Scalar &upper,Mat &mask);
  void contourdetection(Mat &img, Mat &img_contours);

private:
  int hmin, hmax, smin, smax, vmin, vmax;
  Scalar lower;
  Scalar upper;
  Scalar color;
  bool button=false;
};
