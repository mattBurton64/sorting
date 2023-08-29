#!/bin/bash

> output.txt

while IFS= read -r line; do
    # Run the C++ program with the current line as input
    output=$(echo "$line" | ./Source/cppSumCorrect.o)

    # Append the output to the output file
    echo "$output" >> output.txt
done < ./TestFiles/test1.txt