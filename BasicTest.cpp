#include "BasicTest.h"

BasicTest::BasicTest()
{

}

void BasicTest::test(cv::Mat img)
{
  // Image read
  //cv::Mat img =cv::imread("test.jpg");


  //Conversion to gray
  cv::Mat img_gray;
  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

  //Edge detection
  cv::Mat img_edge;
  cv::Canny(img_gray, img_edge, 50, 150);

  //Create colored img_gray
  cv::Mat new_img(500,500, CV_8UC3, cv::Scalar(255,255,255)); //first 2 args are size and 3rd is the type, here 8bits unsigned 3 chanels

  cv::circle(new_img,cv::Point(250,250), 100, cv::Scalar(255,0,0), 5);

  //Image display
  cv::imshow("img_gray", img_gray);
  cv::imshow("Edge", img_edge);
  cv::imshow("image",new_img);
}
