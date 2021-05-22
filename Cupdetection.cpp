#include "Cupdetection.h"

using namespace cv;

Cupdetection::Cupdetection(int _hmin, int _hmax, int _smin, int _smax, int _vmin, int _vmax)
{
  hmin=_hmin;
  hmax=_hmax;
  smin=_smin;
  smax=_smax;
  vmin=_vmin;
  vmax=_vmax;

  Scalar lower(hmin, smin, vmin);
  Scalar upper(hmax, smax, vmax);
}

void Cupdetection::OK_callback(int state, void* userData)
{
  button=true;
}

void Cupdetection::calibrateHSV(VideoCapture cap)
{
  Mat img;
  button=false;
  int finish=0;
  std::cout<<"yolo";
  namedWindow("Trackbars", (600,200));
  createTrackbar("Hue min", "Trackbars", &hmin, 255);
  createTrackbar("Hue max", "Trackbars", &hmax, 255);

  createTrackbar("Sat min", "Trackbars", &smin, 255);
  createTrackbar("Sat max", "Trackbars", &smax, 255);

  createTrackbar("Val min", "Trackbars", &vmin, 255);
  createTrackbar("Val max", "Trackbars", &vmax, 255);

  createTrackbar("Finsh", "Trackbars", &finish, 255);

  while(finish<255)
  {

    cap.read(img);
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    Mat mask;
    inRange(img, lower, upper, mask);

    imshow("Calibration",mask);
    waitKey(1);


  }

  destroyAllWindows();

}

void Cupdetection::colordetection(Mat &img, Mat &mask)
{
  Mat img_HSV;
  cvtColor(img, img_HSV, COLOR_BGR2HSV);
  Scalar lower(hmin, smin, vmin);
  Scalar upper(hmax, smax, vmax);
  inRange(img_HSV, lower, upper, mask);
}

void Cupdetection::colordetection_bgr(Mat &img, Scalar &lower,Scalar &upper,Mat &mask)
{
  inRange(img, lower, upper, mask);
}
