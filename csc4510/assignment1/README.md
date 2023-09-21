# Assignment 1
Learning to use Unix scripting to test programs

## Directories
Correct - contains a set of files with the *expected* output for each test file  
Output - contains the most recent set of files with the *actual* output for each test file  
Script - contains the four shell automation scripts used for compiling, testing, and comparing programs  
Source - contains the cpp and ada summing programs and their executables  
TestFiles - contains the set of test files that are passed into the programs as input  

## Usage
For commands to work as expected, make sure you are in the assignment1/ directory.

To compile, test, and compare the programs run...
```
./Script/consolidate.sh
```
## Output
After running the consolidate script the terminal should look like this...
```
Compiling programs
==================
sumCorrect.cpp compiled
sumError.cpp compiled
gnatmake: "sumCorrect" up to date.
sumCorrect.adb compiled
gnatmake: "sumError" up to date.
sumError.adb compiled

Testing
=======
sumCorrect.cpp
Test 1: PASSED
Test 2: PASSED
Test 3: PASSED
Test 4: PASSED
Test 5: PASSED
Test 6: PASSED
Test 7: PASSED

sumError.cpp
Test 1: PASSED
Test 2: PASSED
Test 3: PASSED
Test 4: PASSED
Test 5: FAILED
2c2
< 1 + 1 = 2
---
> 1 + -1 = 0

Test 6: FAILED
2c2
< 1 + 1 = 2
---
> -1 + -1 = -2

Test 7: PASSED

sumCorrect.adb
Test 1: PASSED
Test 2: PASSED
Test 3: PASSED
Test 4: PASSED
Test 5: PASSED
Test 6: PASSED
Test 7: PASSED

sumError.adb
Test 1: PASSED
Test 2: PASSED
Test 3: PASSED
Test 4: PASSED
Test 5: FAILED
2c2
< 1 + 1 = 2
---
> 1 + -1 = 0

Test 6: FAILED
2c2
< 1 + 1 = 2
---
> -1 + -1 = -2

Test 7: PASSED
Testing complete
```

## Credits
Matt Burton - author of programs and scripts  
Ryan Hirscher - helped me interpret the instructions/requirements  
Michael Oudshoorn, AdaCore, Rosetta Code, and ChatGPT - taught me how to use unix scripts and ada  