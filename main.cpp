#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "BasicTest.h"
#include "Cupdetection.h"


int main()
{

	cv::Mat img =cv::imread("test.jpg");
	BasicTest *test = new BasicTest();

	test->test(img);

	cv::waitKey(0);
	return 0;
}
