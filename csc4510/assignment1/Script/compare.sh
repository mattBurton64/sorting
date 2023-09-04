#!/bin/bash
# This script compares the contents of the output files from the testing script to the correct files in the Correct/ directory

testFiles=(`ls ./TestFiles`) # Gets a list of all the test files from the ./TestFiles directory
size=${#testFiles[@]} # Gets the number of files

fileNum=0
while [ $fileNum -lt $size ] # For every test file...
do
    diff ./Output/cpp/correct/output$((fileNum + 1)).txt ./Correct/output$((fileNum + 1)).txt 
    #diff ./Output/cpp/error/output$((fileNum + 1)).txt ./Correct/output$((fileNum + 1)).txt
    #diff ./Output/ada/correct/output$((fileNum + 1)).txt ./Correct/output$((fileNum + 1)).txt
    #diff ./Output/ada/error/output$((fileNum + 1)).txt ./Correct/output$((fileNum + 1)).txt

    ((fileNum++)) # Incrementor
done