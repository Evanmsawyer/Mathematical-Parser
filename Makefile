# Makefile for calcutil

CXX = g++ # compiler

TARGET = calcutil # target executable

CXXFLAGS = -Wall -std=c++11 # compiler flags

all: $(TARGET) # default target

$(TARGET): driver.o parser.o # build target executable
	$(CXX) $(CXXFLAGS) -o $(TARGET) driver.o parser.o 

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp -o driver.o

parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) -c parser.cpp -o parser.o

run: $(TARGET) # run target executable
	./$(TARGET)

clean: # remove object files and executable
	rm -f $(TARGET)
	rm -f *.o