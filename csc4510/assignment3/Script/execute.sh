#!/bin/bash
# This script is intended to run the sort.o program on every test file

if (( $# == 0 )) # executes if there are no arguments
then
    # Test file structure from ~moudshoorn/CSC4510/Scripts/dirlisting.sh
    testFiles=(`ls ./TestFiles`) # Gets a list of all the test files from the ./TestFiles directory
    size=${#testFiles[@]} # Gets the number of files

    fileNum=0
    while [ $fileNum -lt $size ] # For every test file...
    do
        currentTestFile="./TestFiles/${testFiles[$fileNum]}" # updates the current test file to the current file number

        # Passes in the current test file into the sort.o program
        ./Source/sort.o < "$currentTestFile"

        ((fileNum++)) # Incrementor
    done
else # error if there are too many arguments
    echo "Error: Too many arguments"
    exit 1 # failure
fi
exit # success