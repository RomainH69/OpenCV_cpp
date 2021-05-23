#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
using namespace cv;

class Camera_calibration
{
public:
  Camera_calibration();
  void createKnownBoardPosition(Size boardSize, float squareEdgeLenght, std::vector<Point3f> &corners);
  void getChessboardCorners(std::vector<Mat> images, std::vector<std::vector<Point2f>>& allFoundCorners, bool showResults);
  void cameraCalibration(std::vector<Mat> calibrationImage, Size boardSize, float squareEdgeLenght, Mat &cameraMatrix, Mat &distanceCoefficients);
  bool saveCameraCalibration(std::string name, Mat cameraMatrix, Mat distanceCoefficients);
  int calibrateCam(VideoCapture &cap);

private:
  const float squareDimension = 0.0234f; //meters
  const Size chessboardDimension = Size(6,9);

};
