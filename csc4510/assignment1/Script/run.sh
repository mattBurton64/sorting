#!/bin/bash
# This script calls the other three scripts in order to compile the programs, execute the tests, and compare the results

### COMPILING ###
# compiles the cpp programs
./Script/compile.sh cpp sumCorrect
./Script/compile.sh cpp sumError

# compiles the ada programs
./Script/compile.sh ada sumCorrect
./Script/compile.sh ada sumError

### EXECUTING TESTS ###
./Script/execute.sh
