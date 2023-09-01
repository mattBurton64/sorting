#!/bin/bash
# This script is used to compile programs given their language and file name (leave out the file suffix) as arguments

# $1 is the language to compile in
# $2 is the name of the program to compile

if (( $# <= 1 )) # error if there are too few arguments
then
    echo "Error: Missing one or more argument(s)"
    exit 1 # failure
elif (( $# == 2 )) # compiles if there are an appropriate amount of arguments
then
    case $1 in # checks the value of the first argument
        "cpp") # for cpp programs...
            cd Source/cpp # move to the cpp folder so that the executable is created there
            g++ $2.cpp -o $2.o # compile the program with the name of the second argument
            echo "$2.cpp compiled";;
        "ada") # for ada programs...
            cd Source/ada # move to the ada folder so that the executable is created there
            gnatmake $2.adb -o $2 # compile the program with the name of the second argument
            echo "$2.cpp compiled";;
        *) echo "Error: invalid language argument" # if the first argument is neither cpp or ada, let the user know they made an error
            exit 1;; # failure
    esac
else # error if there are too many arguments
    echo "Error: Too many arguments"
    exit 1 # failure
fi
exit # success