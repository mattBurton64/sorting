#!/bin/bash
# This script passes all test files through the four summing programs (correct cpp, error cpp, correct ada, error ada) and stores the output of each in a corresponding output file

if (( $# < 1 )) # error if there are too few arguments
then
    echo "Error: There must be a program argument"
    exit 1 # failure
elif (( $# == 1 )) # compiles if there are an appropriate amount of arguments
then
    # Test file structer structure from ~moudshoorn/CSC4510/Scripts/dirlisting.sh
    testFiles=(`ls ./TestFiles`) # Gets a list of all the test files from the ./TestFiles directory
    size=${#testFiles[@]} # Gets the number of files

    # Creates new directory for the output files
    mkdir -p Output

    fileNum=0
    while [ $fileNum -lt $size ] # For every test file...
    do
        currentTestFile="./TestFiles/${testFiles[$fileNum]}" # updates the current test file to the current file number

        # overwrites/creates the output file so the file is empty before testing
        > "Output/output$((fileNum + 1)).txt"

        while IFS= read -r line; # For every line in the test file... (IFS= ensures each input is the whole line from the test file)
        do 
            # Pipes the line from the test file into each of the four programs and stores thier results
            echo "$line" | $1 >> Output/output$((fileNum + 1)).txt 

        done < "$currentTestFile" # Passes in the current test files as input
        ((fileNum++)) # Incrementor
    done
else # error if there are too many arguments
    echo "Error: Too many arguments"
    exit 1 # failure
fi
exit # success