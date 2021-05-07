#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "BasicTest.h"
#include "Cupdetection.h"

using namespace cv;


int hmin=0, smin=70, vmin=153;
int hmax=50, smax=240, vmax=255;


int main()
{

	Mat img =imread("test.jpg");
	BasicTest *test = new BasicTest();
	Cupdetection *red= new Cupdetection();

	//test->test(img);

	// Webcam
	VideoCapture cap(2);
	Mat cam;

	//Trackbars to adjust bounds
	namedWindow("Trackbars", (600,200));
	createTrackbar("Hue min", "Trackbars", &hmin, 179);
	createTrackbar("Hue max", "Trackbars", &hmax, 255);

	createTrackbar("Sat min", "Trackbars", &smin, 255);
	createTrackbar("Sat max", "Trackbars", &smax, 255);

	createTrackbar("Val min", "Trackbars", &vmin, 255);
	createTrackbar("Val max", "Trackbars", &vmax, 255);


	while (true) {
		cap.read(cam);

		//definition of color bounds
		Scalar lower=(hmin, smin, vmin);
		Scalar upper=(hmax, smax, vmax);

		Mat mask=red->colordetection(cam, lower, upper);

		imshow("Cam", cam);
		imshow("Mask", mask);
		waitKey(1);
	}

	return 0;
}
