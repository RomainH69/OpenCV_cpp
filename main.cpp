#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "BasicTest.h"
#include "Cupdetection.h"

using namespace cv;


int main()
{

	Mat img =imread("test.jpg");
	BasicTest *test = new BasicTest();
	Cupdetection *red= new Cupdetection(0,16,87,255,229,255);

	//test->test(img);

	// Webcam
	VideoCapture cap(2);
	Mat cam;

	//Trackbars to adjust bounds



/*
	namedWindow("Trackbars BGR", (600,200));
	createTrackbar("Blue min", "Trackbars BGR", &bmin, 255);
	createTrackbar("Blue max", "Trackbars BGR", &bmax, 255);

	createTrackbar("Green min", "Trackbars BGR", &gmin, 255);
	createTrackbar("Green max", "Trackbars BGR", &gmax, 255);

	createTrackbar("Red min", "Trackbars BGR", &rmin, 255);
	createTrackbar("Red max", "Trackbars BGR", &rmax, 255);

	*/
	Mat mask;
	red->calibrateHSV(cap);

	while (true) {
		cap.read(cam);


		red->colordetection(cam, mask);

		imshow("Cam", cam);
		imshow("Mask", mask);
		waitKey(1);
	}

	return 0;
}
