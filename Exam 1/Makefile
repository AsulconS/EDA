CC=gcc
CXX=g++

INCLUDE_DIR=./include/

CC_FLAGS=-std=c11
CXX_FLAGS=-std=c++11

TARGET=main

O_DEPENDENCIES=glad.o shader.o cubeMesh.o octree.o $(TARGET).o
L_DEPENDENCIES=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all: $(O_DEPENDENCIES)
	$(CXX) $(CXX_FLAGS) $(L_DEPENDENCIES) -o $(TARGET) $(O_DEPENDENCIES)

glad.o: glad.c
	$(CC) -c $(CC_FLAGS) -I$(INCLUDE_DIR) glad.c

shader.o: shader.cpp
	$(CXX) -c $(CXX_FLAGS) -I$(INCLUDE_DIR) shader.cpp

cubeMesh.o: cubeMesh.cpp
	$(CXX) -c $(CXX_FLAGS) -I$(INCLUDE_DIR) cubeMesh.cpp

octree.o: octree.cpp
	$(CXX) -c $(CXX_FLAGS) -I$(INCLUDE_DIR) octree.cpp

$(TARGET).o: $(TARGET).cpp
	$(CXX) -c $(CXX_FLAGS) -I$(INCLUDE_DIR) $(TARGET).cpp
