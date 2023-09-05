# Assignment 1
Learning to use Unix scripting to test programs

## Usage
For commands to work as expected, make sure you are in the assignment1/ directory.

To compile, test, and compare the programs run...
```
./Script/consolidate.sh
```
## Output
Below is an example of one of the output files after running a test file through the correct ada program...
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
Comparing output
Test 0: PASSED
Test 1: PASSED
Test 2: PASSED

sumError.cpp
Comparing output
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
Comparing output
Test 0: PASSED
Test 1: PASSED
Test 2: PASSED

sumError.adb
Comparing output
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
```

## Credits
Matt Burton - author of programs and scripts

Ryan Hirscher - helped me interpret the instructions/requirements

Michael Oudshoorn, AdaCore, Rosetta Code, and ChatGPT - taught me how to use unix scripts and ada