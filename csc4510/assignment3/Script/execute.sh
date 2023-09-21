#!/bin/bash
# This script is intended to run the sort program on every test file

testFolders=(`ls ./TestFiles`) # Gets a list of all the test type folders
numberOfFolders=${#testFolders[@]} # Gets the number of folders

folderNum=0
while [ $folderNum -lt $numberOfFolders ] # For every test folder...
do
    currentFolder="./TestFiles/${testFolders[$folderNum]}"
    testFiles=($(ls "$currentFolder")) # Gets a list of all the test files in the current folder
    folderSize=${#testFiles[@]} # Gets the number of files in the current folder

    fileNum=0
    while [ $fileNum -lt $folderSize ] # For every test file...
    do
        currentTestFile="./$currentFolder/${testFiles[$fileNum]}" # updates the current test file to the current file number

        # Determine the data type based on the folder name
        case "$currentFolder" in
            *"character"*)
                dataType="character"
                ;;
            *"color"*)
                dataType="color"
                ;;
            *"float"*)
                dataType="float"
                ;;
            *"integer"*)
                dataType="integer"
                ;;
            *"string"*)
                dataType="string"
                ;;
            *)
                dataType="unknown"
                ;;
        esac

        echo "${testFiles[$fileNum]}"
        # Passes in the current test file into the sort.o program
        ./Source/sort.o $dataType < "$currentTestFile"
        ((fileNum++)) # Incrementor
    done
    ((folderNum++)) # Incrementor
done