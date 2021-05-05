#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


int main()
{

	// Image read
	cv::Mat img =cv::imread("test.jpg");


	//Conversion to grey
	cv::Mat img_gray;
	cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

	//Image display
	cv::imshow("img_gray", img_gray);
	cv::waitKey(0);
	return 0;
}
