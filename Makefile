# Makefile for calcutil

CXX = g++ # compiler

TARGET = calcutil # target executable

SRC = driver.cpp # source file

CXXFLAGS = -Wall -std=c++11 # compiler flags

all: $(TARGET) # default target

$(TARGET): $(SRC) # build target executable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) 

run: $(TARGET) # run target executable
	./$(TARGET)

clean: # remove object files and executable
	rm -f $(TARGET)