#include "Camera_calibration.h"

using namespace cv;
using namespace std;

Camera_calibration::Camera_calibration()
{

}

void Camera_calibration::createKnownBoardPosition(Size boardSize, float squareEdgeLenght, vector<Point3f> &corners)
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
      drawChessboardCorners(*iter,Size(6,9),pointBuff,found);
      imshow("corners", *iter);
      waitKey(0);
    }
  }
}

void Camera_calibration::cameraCalibration(vector<Mat> calibrationImage, Size boardSize, float squareEdgeLenght, Mat &cameraMatrix, Mat &distanceCoefficients)
{
  vector<vector<Point2f>> checkerboardImageSpacePoints;
  getChessboardCorners(calibrationImage, checkerboardImageSpacePoints, false);

  vector<vector<Point3f>> worldSpaceCornerPoints(1);

  createKnownBoardPosition(boardSize, squareEdgeLenght, worldSpaceCornerPoints[0]);
  worldSpaceCornerPoints.resize(checkerboardImageSpacePoints.size(), worldSpaceCornerPoints[0]);

  vector<Mat> rVector, tVector;
  distanceCoefficients=Mat::zeros(8,1, CV_64F);

  calibrateCamera(worldSpaceCornerPoints, checkerboardImageSpacePoints, boardSize, cameraMatrix, distanceCoefficients, rVector, tVector);

}

bool Camera_calibration::saveCameraCalibration(string name, Mat cameraMatrix, Mat distanceCoefficients)
{
  ofstream outStream(name);
  if(outStream)
  {
    uint16_t rows=cameraMatrix.rows;
    uint16_t columns=cameraMatrix.cols;

    for(int r=0; r<rows;r++)
    {
      for(int c=0;c<columns;c++)
      {
        double value=cameraMatrix.at<double>(r,c);
        outStream <<value<<endl;
      }
    }

    rows=distanceCoefficients.rows;
    columns=distanceCoefficients.cols;

    for(int r=0; r<rows;r++)
    {
      for(int c=0;c<columns;c++)
      {
        double value=distanceCoefficients.at<double>(r,c);
        outStream <<value<<endl;
      }
    }
    outStream.close();
    return true;
  }
  return false;
}


int Camera_calibration::calibrateCam(VideoCapture &cap)
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

    char key = waitKey(1000/20);

    switch(key)
    {
      case ' ':
        //save
        if(found)
        {
          Mat temp;
          frame.copyTo(temp);
          savedImages.push_back(temp);
        }
        break;

      case 13:
        //Start calibration
        if(savedImages.size()>15)
        {
          cameraCalibration(savedImages, chessboardDimension, squareDimension, cameraMatrix, distanceCoefficients);
          saveCameraCalibration("calibration", cameraMatrix, distanceCoefficients);
        }

        break;

      case 27:
        //exit
        return 0;
    }
  }
}
