#!/bin/bash
# Used for running all four programs (correct cpp, error cpp, correct ada, error ada), passing in the entire list of test files for each program, and finally storing the output of each program in test case in a corresponding output file

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
    > "Output/cpp/correct/output$((fileNum + 1)).txt"
    > "Output/cpp/error/output$((fileNum + 1)).txt"
    > "Output/ada/correct/output$((fileNum + 1)).txt"
    > "Output/ada/error/output$((fileNum + 1)).txt"

    while IFS= read -r line; # For every line in the test file...
    do 
        # Pipes the line from the test file into each of the four programs and stores thier results
        echo "$line" | ./Source/cpp/sumCorrect.o >> Output/cpp/correct/output$((fileNum + 1)).txt 
        echo "$line" | ./Source/cpp/sumError.o >> Output/cpp/error/output$((fileNum + 1)).txt
        echo "$line" | ./Source/ada/sumcorrect >> Output/ada/correct/output$((fileNum + 1)).txt 
        echo "$line" | ./Source/ada/sumerror >> Output/ada/error/output$((fileNum + 1)).txt 

    done < "./TestFiles/${testFiles[$fileNum]}" # Passes in each of the test files as input
    ((fileNum++)) # Incrementor
done