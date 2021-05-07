all: main BasicTest Cupdetection
	g++ main.o BasicTest.o Cupdetection.o -o opencv -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

main: main.cpp
	g++ -c main.cpp -I/usr/include/opencv4

BasicTest: BasicTest.cpp BasicTest.h
	g++ -c BasicTest.cpp -I/usr/include/opencv4

Cupdetection: Cupdetection.cpp Cupdetection.h
	g++ -c Cupdetection.cpp -I/usr/include/opencv4

clean:
	del *.o
	del a.out
