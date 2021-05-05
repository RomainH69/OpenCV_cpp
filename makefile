all: main 
	g++ main.o -o opencv -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

main: main.cpp
	g++ -c main.cpp -I/usr/include/opencv4

clean:
	del *.o
	del a.out
