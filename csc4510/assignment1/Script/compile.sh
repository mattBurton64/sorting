#!/bin/bash
# This script is used to compile programs given their language and file name (leave out the file suffix) as arguments

# $1 is the language to compile in
# $2 is the name of the program to compile

if (( $# <= 1 ))
then
    echo "Error: Missing one or more argument(s)"
    exit 1 # failure
else
    case $1 in
        "cpp")
            cd Source/cpp
            g++ $2.cpp -o $2.o;;
        "ada")
            cd Source/ada
            gnatmake $2.adb -o $2;;
        *) echo "Error: invalid language argument" 
            exit 1;; # failure
    esac
fi
exit # success