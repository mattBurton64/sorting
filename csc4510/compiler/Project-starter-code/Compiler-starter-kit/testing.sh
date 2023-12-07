#!/usr/bin/bash
# This script runs the compiler on the test files in the TestFiles/ directory

if (( $# < 1 )) # error if there are too few arguments
then
    echo "Error: There must be a folder argument"
    exit 1 # failure
elif (( $# == 1 )) # compiles if there are an appropriate amount of arguments
then
   make # runs the makefile

   testFiles=(`ls ./TestFiles/"$1"`) # Gets a list of all the test files from the ./TestFiles directory
   size=${#testFiles[@]} # Gets the number of files

   fileNum=0
   while [ $fileNum -lt $size ] # For every test file...
   do
      currentTestFile="./TestFiles/$1/${testFiles[$fileNum]}" # updates the current test file to the current file number

      echo -e "$currentTestFile\n" # "${testFiles[$fileNum]}"  # prints the name of the test file
      cat "$currentTestFile" # prints the contents of the test file
      ./compiler "$currentTestFile" # compiles the test file
   
      echo -e "\n"

      ((fileNum++)) # Incrementor
   done
else # error if there are too many arguments
    echo "Error: Too many arguments"
    exit 1 # failure
fi
exit # success
