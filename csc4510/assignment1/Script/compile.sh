#!/bin/bash

# moves into the source directory so that the executables are created within that folder
cd Source/

# compile the c++ programs
g++ sumCorrect.cpp -o cppSumCorrect.o
g++ sumError.cpp -o cppSumError.o

# compile the ada programs
gnatmake sumCorrect.adb -o adaSumCorrect.o
gnatmake sumError.adb -o adaSumError.o