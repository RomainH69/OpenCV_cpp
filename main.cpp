#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "BasicTest.h"
#include "Cupdetection.h"
#include "Camera_calibration.h"

using namespace cv;
using namespace std;


int main()
{
	string camConfig="calibration";
	ifstream camConf(camConfig);
	Mat img =imread("test.jpg");
	BasicTest *test = new BasicTest();
	Cupdetection *red= new Cupdetection(0,16,111,255,202,255,Scalar(0,0,255));
	Cupdetection *green= new Cupdetection(49,92,87,255,75,202,Scalar(0,255,0));
	Camera_calibration *camera=new Camera_calibration();



	//test->test(img);

	// Webcam
	VideoCapture cap(2);
	Mat cam;
	cap.read(cam);
	Size frameSize(cam.cols, cam.rows);

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
	if(!camConf)
	{
		camera->calibrateCam(cap);
	}

	Matx33f K(Matx33f::eye());
	Vec<float, 5> k(0,0,0,0,0);

	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			camConf >> K(i,j);
		}
	}

	for(int i=0;i<5;i++)
	{
		camConf >> k(i);
	}

	Mat mapx, mapy, img_undistored;
	Matx33f new_cam_matrix;
	//fisheye::estimateNewCameraMatrixForUndistortRectify(K,k,frameSize, Matx33f::eye(), new_cam_matrix,1);
	initUndistortRectifyMap(K,k, Matx33f::eye(), getOptimalNewCameraMatrix(K, k, frameSize, 1, frameSize, 0), frameSize, CV_16SC2, mapx, mapy);

	Mat red_mask, green_mask, img_contours;
	red->calibrateHSV(cap);
	green->calibrateHSV(cap);

	while (true) {
		cap.read(cam);

		remap(cam, img_undistored, mapx, mapy, INTER_LINEAR);
		/*cam.copyTo(img_contours);

		red->colordetection(cam, red_mask);
		red->contourdetection(red_mask,img_contours);

		green->colordetection(cam, green_mask);
		green->contourdetection(green_mask,img_contours);

		*/
		imshow("Cam", cam);
		imshow("Undistored", img_undistored);
		//imshow("Contours", img_contours);
		waitKey(1);
	}

	return 0;
}
