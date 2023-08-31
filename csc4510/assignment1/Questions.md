## What directory should commands be executed from?
Assume that the user is in the Assignment1 directory and document this in the README

## Should we modify the original programs to only output the total, not the prompts and calculations?
No, let them output the prompts and calculations

## Should output files be unique for each program and test file or should they have a set of answers for each program in the same file corresponding to the input file?
Dont group outputs together

## How large should the "large numbers" be in the test files(if each is a long long then their sum will exceed the maximum space for integers)?
Just note what the expected output is when exceeding integer limits

## How many test files do you want us to make?
10 or more

## For the compile script why do you want us to pass in arguments for the name of the language used and the name of the file to be compiled (I have a compile script that compiles all four scripts already with less user effort since it only needs to be run once and the user doesnt need to know the names of the original programs)?
Make the compile script a generic compile script, and then hardcode the arguments in the fourth script

## Are the original programs supposed to loop to allow for multiple inputs from a test file, or should the testing script be responsible for running the summing programs for each line in the test files (unclear when demonstrating the intermediate step to run java addCorrect < ../TestFiles/test1.txt)?
Leave looping for the testing script

## For the comparison file should the "clear indication" of which tests passed or failed be stored in a new output file or integrated into another existing file?
Store comparison results in a new file

## Do the output files need to have generated comments?
No