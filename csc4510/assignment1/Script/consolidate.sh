#!/bin/bash
# This script calls the other three scripts in order to compile the programs, execute the tests, and compare the results

### COMPILING ###
echo -e "Compiling programs\n==================" # section header
./Script/compile.sh cpp sumCorrect # compiles the sumCorrect.cpp program
./Script/compile.sh cpp sumError # compiles the sumError.cpp program
./Script/compile.sh ada sumCorrect # compiles the sumCorrect.adb program
./Script/compile.sh ada sumError # compiles the sumError.adb program

### TESTING ###
echo -e "\nTesting\n=======" # section header
echo "sumCorrect.cpp" # program label
./Script/testing.sh ./Source/cpp/sumCorrect.o # runs the test
./Script/compare.sh # runs the comparison script

echo -e "\nsumError.cpp" # program label
./Script/testing.sh ./Source/cpp/sumError.o # runs the test
./Script/compare.sh # runs the comparison script

echo -e "\nsumCorrect.adb" # program label
./Script/testing.sh ./Source/ada/sumCorrect # runs the test
./Script/compare.sh # runs the comparison script

echo -e "\nsumError.adb" # program label
./Script/testing.sh ./Source/ada/sumError # runs the test
./Script/compare.sh # runs the comparison script

echo "Testing complete"
exit # success
