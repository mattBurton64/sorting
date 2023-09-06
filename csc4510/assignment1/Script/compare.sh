#!/bin/bash
# This script compares the contents of the output files from the testing script to the correct files in the Correct/ directory

outputFiles=(`ls ./Output`) # Gets a list of all the test files from the ./Output directory
size=${#outputFiles[@]} # Gets the number of files

fileNum=0
while [ $fileNum -lt $size ] # For every output file...
do
    fileDifference=$(diff ./Output/output$((fileNum + 1)).txt ./Correct/output$((fileNum + 1)).txt)

    if (( $? == 0 )) # if the exit statement of the previous diff command is 0 then the test passed
    then
        echo -e "Test $((fileNum + 1)): PASSED"
    else
        echo "Test $((fileNum + 1)): FAILED"
        echo -e "$fileDifference\n"
    fi

    ((fileNum++)) # Incrementor
done
exit # success