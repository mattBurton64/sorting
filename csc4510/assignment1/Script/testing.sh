#!/bin/bash
# This script passes all test files through the four summing programs (correct cpp, error cpp, correct ada, error ada) and stores the output of each in a corresponding output file

# Got this outter structure from ~moudshoorn/CSC4510/Scripts/dirlisting.sh
testFiles=(`ls ./TestFiles`) # Gets a list of all the test files from the ./TestFiles directory
size=${#testFiles[@]} # Gets the number of files

# Creates new directories for the output files
mkdir -p Output/cpp/correct
mkdir -p Output/cpp/error
mkdir -p Output/ada/correct
mkdir -p Output/ada/error

fileNum=0
while [ $fileNum -lt $size ] # For every test file...
do
    currentTestFile="./TestFiles/${testFiles[$fileNum]}" # updates the current test file to the current file number

    # overwrites/creates the output file so the file is empty before the test
    > "Output/cpp/correct/output$((fileNum + 1)).txt"
    > "Output/cpp/error/output$((fileNum + 1)).txt"
    > "Output/ada/correct/output$((fileNum + 1)).txt"
    > "Output/ada/error/output$((fileNum + 1)).txt"

    while IFS= read -r line; # For every line in the test file... (IFS= ensures each input is a whole line)
    do 
        # Pipes the line from the test file into each of the four programs and stores thier results
        echo "$line" | ./Source/cpp/sumCorrect.o >> Output/cpp/correct/output$((fileNum + 1)).txt 
        echo "$line" | ./Source/cpp/sumError.o >> Output/cpp/error/output$((fileNum + 1)).txt
        echo "$line" | ./Source/ada/sumcorrect >> Output/ada/correct/output$((fileNum + 1)).txt 
        echo "$line" | ./Source/ada/sumerror >> Output/ada/error/output$((fileNum + 1)).txt 

    done < "$currentTestFile" # Passes in the current test files as input
    ((fileNum++)) # Incrementor
done