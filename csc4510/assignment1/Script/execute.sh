#!/bin/bash
# Used for running all four programs (correct cpp, error cpp, correct ada, error ada), passing in the entire list of test files for each program, and finally storing the output of each program in test case in a corresponding output file

testFiles=(`ls ./TestFiles`) # Gets a list of all the test files from the ./TestFiles directory
size=${#testFiles[@]} # Gets the number of files

# Creates directories for the test outputs to be stored
mkdir -p Output/cpp/correct
mkdir -p Output/cpp/error
mkdir -p Output/ada/correct
mkdir -p Output/ada/error

index=0
while [ $index -lt $size ] # For every test file...
do
    > "output$((index + 1)).txt" # Creates a new output file for the cpp correct tests
    while IFS= read -r line; # For every line in the test file...
    do 
        # Runs the four programs and store thier results
        echo "$line" | ./Source/cpp/sumCorrect.o >> Output/cpp/correct/output$((index + 1)).txt 
        echo "$line" | ./Source/cpp/sumError.o >> Output/cpp/error/output$((index + 1)).txt
        echo "$line" | ./Source/ada/sumcorrect >> Output/ada/correct/output$((index + 1)).txt 
        echo "$line" | ./Source/ada/sumerror >> Output/ada/error/output$((index + 1)).txt 

    done < "./TestFiles/${testFiles[$index]}"
    index=$((index + 1))
done