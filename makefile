all: main BasicTest Cupdetection Camera_calibration
	g++ *.o -o opencv -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio  -lopencv_calib3d $(pkg-config --libs opencv)

main: main.cpp
	g++ -c main.cpp -I/usr/include/opencv4

BasicTest: BasicTest.cpp BasicTest.h
	g++ -c BasicTest.cpp -I/usr/include/opencv4

Cupdetection: Cupdetection.cpp Cupdetection.h
	g++ -c Cupdetection.cpp -I/usr/include/opencv4

Camera_calibration: Camera_calibration.cpp Camera_calibration.h
	g++ -c Camera_calibration.cpp -I/usr/include/opencv4

clean:
	del *.o
	del *.out
