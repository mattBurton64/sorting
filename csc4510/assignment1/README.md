# Assignment 1
Learning to use Unix scripting to test programs

## Directories
Correct - contains a set of files with the *expected* output for each test file
Output - contains the most recent set of files with the *actual* output for each test file
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
Test 0: PASSED
Test 1: PASSED
Test 2: PASSED

sumError.cpp
Test 0: FAILED
10c10
< 1 + 1 = 2
---
> 1 + -1 = 0
12c12
< 1 + 1 = 2
---
> -1 + -1 = -2

Test 1: FAILED
10c10
< 10 + 10 = 20
---
> 10 + -10 = 0
12c12
< 10 + 10 = 20
---
> -10 + -10 = -20

Test 2: FAILED
10c10
< 32 + 16 = 48
---
> 32 + -16 = 16
12c12
< 32 + 16 = 48
---
> -32 + -16 = -48


sumCorrect.adb
Test 0: PASSED
Test 1: PASSED
Test 2: PASSED

sumError.adb
Test 0: FAILED
10c10
< 1 + 1 = 2
---
> 1 + -1 = 0
12c12
< 1 + 1 = 2
---
> -1 + -1 = -2

Test 1: FAILED
10c10
< 10 + 10 = 20
---
> 10 + -10 = 0
12c12
< 10 + 10 = 20
---
> -10 + -10 = -20

Test 2: FAILED
10c10
< 32 + 16 = 48
---
> 32 + -16 = 16
12c12
< 32 + 16 = 48
---
> -32 + -16 = -48

Testing complete
```

## Credits
Matt Burton - author of programs and scripts

Ryan Hirscher - helped me interpret the instructions/requirements

Michael Oudshoorn, AdaCore, Rosetta Code, and ChatGPT - taught me how to use unix scripts and ada