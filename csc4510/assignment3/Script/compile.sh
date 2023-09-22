#!/bin/bash
# This script is used to compile C++ programs given their file name (leave out the file suffix)

# $1 is the name of the program to compile

if (( $# == 0 )) # error if there are too few arguments
then
    echo "Error: Missing file name argument"
    exit 1 # failure
elif (( $# == 1 )) # compiles if there is an argument
then
    cd Source # move to the cpp folder so that the executable is created there
    g++ $1.cpp -o $1.o # compile the program with the name of the second argument
    echo "$1.cpp compiled"
else # error if there are too many arguments
    echo "Error: Too many arguments"
    exit 1 # failure
fi
exit # success