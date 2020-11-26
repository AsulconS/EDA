CXX=g++
CXX_FLAGS=-std=c++11

INCLUDE=-I./include/ -I/usr/include/opencv4/

OPENCV_LIBS=`pkg-config --libs --cflags --static opencv4`

TARGET=main
OBJECTS=algorithm.o kdtree.o $(TARGET).o

all: build trash

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OPENCV_LIBS) -o $(TARGET) $(OBJECTS)

$(TARGET).o: $(TARGET).cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE) $(TARGET).cpp

algorithm.o: algorithm.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE) algorithm.cpp

kdtree.o: kdtree.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE) kdtree.cpp

trash:
	rm -f ./*.o

clean: trash
	rm -f ./main
