#!/bin/bash
# This script calls the compile script and runs the execute script

### COMPILING ###
echo -e "Compiling program\n=================" # section header
./Script/compile.sh sort # compiles the sort.cpp program

### EXECUTING ###
echo -e "\nExecuting\n=========" # section header
echo "sort.cpp" # program label
./Script/execute.sh # sorts the  test files

echo "Sorting complete"
exit # success
