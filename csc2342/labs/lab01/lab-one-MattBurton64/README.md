# CSC2342-01 F20 Lab One
## Dr. Jason M. Pittman

## Purpose
The purpose of this work is to implement fundamental propositional logic concepts in a program such that a user can enter two or more propositional variables with connectives and the program generates a correct truth table.

## Requirements
Please develop your solution using Python 3 (my current version is 3.7.5). Do not use third party libraries or code snippets!   

You may work in groups. However, everyone must submit an individual assignment. If you collaborate, please list the names of all collaborators in your program header.

## Features
Your program, at a minimum, must include the following features:

1. At runtime, display text message explaining to the user how to use the program and enter propositional statements. That means variables and connectives. You should also show an example of valid input.

2. Parse upper or lower case propositional variables (any valid Latin alphabet character). Convert to lowercase for the programs output. Do not accept anything other than letters.

3. Handle the entered connectives of `/\`, `\/`, and `>`. That’s `and`, `or`, and `implies`.

4. Handle the negation operator as `~`.

5. Handle parentheses for order of operations grouping and process using our stated order of operations.

6. Based on the (a) variables entered and (b) connectives present, construct a valid truth table and display using tab delimiters between fields. We don’t need horizontal or vertical lines. Use `T` for True and `F` for False.

## Rubic
My grading rubric is straightforward. **You must indicate in the program header which rubric you want to earn.**

R1: Completing requirements 1 through 3 and 6 will earn a maximum of a `C` grade.   
R2: Completing requirements 1 through 4 and 6 will earn a maximum of a `B` grade.  
R3: Completing requirements 1 through 6 (all) will earn a maximum of a `A` grade.  

Detailed assessment points are:

1. Does the program run without error?    
2. Does the program present me with instructions to use and enter propositional statements?    
3. Does the program parse input correctly?  
   (a) Single proposition (R1)  
   (b) Two propositions with single connective (R1)  
   (c) Three propositions with two connectives (R2)  
   (d) Three propositions with parentheses and three connectives (R3)  
4. Does the program produce correct, valid truth tables?
5. Is the output orderly and readable  

*Note: any hardcoding of entire truth tables will result in an `F` grade for the lab.
Note: failure to indicate your selected rubric in the program header will result in a one letter grade deduction.*
