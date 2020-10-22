CXX=g++
CXX_FLAGS=-std=c++11

INCLUDE=-I./include/ -I/usr/include/opencv4/

OPENCV_LIBS=`pkg-config --libs --cflags --static opencv4`

TARGET=main
OBJECT=octree.o $(TARGET).o

all: $(OBJECT)
	$(CXX) $(CXX_FLAGS) $(OPENCV_LIBS) -o $(TARGET) $(OBJECT)

clean:
	rm -f ./*.o

$(TARGET).o: $(TARGET).cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE) $(TARGET).cpp

octree.o: octree.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE) octree.cpp
