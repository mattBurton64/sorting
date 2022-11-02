# CSC2342-01 F20 Lab Two
## Dr. Jason M. Pittman

## Purpose
The purpose of this lab is for you to develop a quantifier for unary, binary, and ternary predicates.

## Requirements
Please develop your solution using Python 3 (my current version is 3.7.5). Do not use third party libraries or code snippets!

You may work in groups. However, everyone must submit an individual assignment. If you collaborate, please list the names of all collaborators in your program header.

## Features
Your program, at a minimum, must include the following features:

1. At runtime, display text message explaining to the user how to use the program and enter predicate statements. You should also show an example of valid input.
    - our predicate variables are x (unary), x & y (binary), and x & y & z (ternary) to be used in...
    - our function is in the form arithmetic construct (e.g. `x > 0`, `x + y = 0`, or `x / y = z`) which we must correctly evaluate given... 
    - our domain is in the form of {n...n+1} (e.g. 1...10)...
    - our quantifier for each variable. We can abbreviate as `u` for universal and `e` for existential.

2. Ask the user to input each of the components (variables, function, domain, quantifiers) one at a time.

3. Quantify the given variables within the context of the function, domain, and quantifiers.

4. Output the truth value as `T` or `F`.

## Rubric
My grading rubric is straightforward. You must indicate in the program header which rubric you want to earn.

R1: Completing requirements 1 through 4 for unary quantification will earn a maximum of a C grade.   
R2: Completing requirements 1 through 4 for binary quantification will earn a maximum of a B grade.  
R3: Completing requirements 1 through 4 for ternary quantification will earn a maximum of a A grade.  

Detailed assessment points are:  
  
1. Does the program run without error?  
2. Does the program present me with instructions to use and enter propositional statements?  
3. Does the program parse input correctly?  
4. Does the program correctly quantify unary, binary, and ternary inputs (relative to stated rubric condition)?  
5. Does the program correctly compute truth values given the inputs?  
6. Is the output orderly and readable?  
