#include "Camera_calibration.h"

using namespace cv;
using namespace std;

Camera_calibration::Camera_calibration()
{

}

/*void Camera_calibration::createKnownBoardPosition(Size boardSize, float squareEdgeLenght, vector<Point3f> &corners)
{
  for(int i=0; i<boardSize.height; i++)
  {
    for(int j=0; j<boardSize.width; j++)
    {
      corners.push_back(Point3f(j* squareEdgeLenght, i* squareEdgeLenght, 0.0f));
    }
  }
}

void Camera_calibration::getChessboardCorners(vector<Mat> images, vector<vector<Point2f>>& allFoundCorners, bool showResults=false)
{
  for(vector<Mat>::iterator iter=images.begin();iter!= images.end();iter++)
  {
    vector<Point2f> pointBuff;
    bool found =findChessboardCorners(*iter, Size(9,6), pointBuff, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
    if(found)
    {
      allFoundCorners.push_back(pointBuff);

    }

    if(showResults)
    {
      drawChessboardCorners(*iter,Size(9,6),pointBuff,found);
      imshow("corners", *iter);
      waitKey(0);
    }
  }
}*/

void Camera_calibration::calibrateCam(VideoCapture &cap)
{
  Mat frame, drawToFrame;

  Mat cameraMatrix= Mat::eye(3,3,CV_64F);

  Mat distanceCoefficients;

  vector<Mat> savedImages;
  vector<vector<Point2f>> markerCorners, rejectedCandidates;

  namedWindow("Cam",WINDOW_AUTOSIZE);

  while(true)
  {
    vector<Vec2f> foundPoints;
    bool found=false;
    cap.read(frame);

    found = findChessboardCorners(frame, chessboardDimension, foundPoints, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
    frame.copyTo(drawToFrame);
    drawChessboardCorners(drawToFrame, chessboardDimension, foundPoints, found);
    if(found)
    {
      imshow("Cam", drawToFrame);
    }
    else
    {
      imshow("Cam", frame);
    }

    waitKey(1000/20);
  }
}
