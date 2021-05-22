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
	Cupdetection *red= new Cupdetection(0,14,140,255,130,255,Scalar(0,0,255));
	Cupdetection *green= new Cupdetection(49,92,87,255,75,202,Scalar(0,255,0));

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
	Mat red_mask, green_mask, img_contours;
	red->calibrateHSV(cap);
	green->calibrateHSV(cap);

	while (true) {
		cap.read(cam);
		cam.copyTo(img_contours);

		red->colordetection(cam, red_mask);
		red->contourdetection(red_mask,img_contours);

		green->colordetection(cam, green_mask);
		green->contourdetection(green_mask,img_contours);


		imshow("Cam", cam);
		imshow("Contours", img_contours);
		waitKey(1);
	}

	return 0;
}
