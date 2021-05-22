#include "Cupdetection.h"

using namespace cv;
using namespace std;

Cupdetection::Cupdetection(int _hmin, int _hmax, int _smin, int _smax, int _vmin, int _vmax, Scalar _color)
{
  hmin=_hmin;
  hmax=_hmax;
  smin=_smin;
  smax=_smax;
  vmin=_vmin;
  vmax=_vmax;

  color=_color;

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
    Mat img_HSV;
    cvtColor(img, img_HSV, COLOR_BGR2HSV);
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    Mat mask;
    inRange(img_HSV, lower, upper, mask);

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

void Cupdetection::contourdetection(Mat &img, Mat &img_contours)
{
  Mat img_canny, img_dilate;
  Canny(img, img_canny,50,75);
  imshow("Canny", img_canny);
  Mat kernel=getStructuringElement(MORPH_RECT, Size(3,3));
  dilate(img_canny, img_dilate, kernel);

  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;

  findContours(img_dilate, contours,hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  vector<Rect> boundRect(contours.size());

  for(int i=0;i<contours.size();i++)
  {
    int area = contourArea(contours[i]);

    if (area>10000)
    {
      drawContours(img_contours, contours, i, Scalar(255,0,0),2);
      boundRect[i]=boundingRect(contours[i]);
      rectangle(img_contours,boundRect[i].tl(),boundRect[i].br(), color,5);
    }
  }
}
