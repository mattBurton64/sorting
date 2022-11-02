# CSC2342-01 SP21 Lab Three
## Dr. Jason M. Pittman

## Purpose
The purpose of this work is to implement programmatic logic such that a user can enter Boolean values representative of propositions and evaluate a Truth Value outcome given a rule of inference.

## Requirements
Your program, at a minimum, must include the following features. Be certain to submit your assignment in the GitHub Classroom assignment after you are finished programming *and* testing.

## Prerequisites
You will need to use a Python module to implement the necessary features and run the program. Please install **sympy** using `pip3 install sympy` or the correct version of `pip` for your system.

## Features
The minimum features are as follows. I recommend programming to each successive feature and testing it before moving on.

Note: line numbers reference the provided source code. Once you begin modifying the program, line numbers will obviously change.

1. Starting on line 28, implement a class method which implements the modus ponens rule of inference and returns the appropraite Truth Value based on the Boolean inputs for p, q.

2. Starting on line 31, implement a class method which implements the modus ponens rule of inference and returns the appropraite Truth Value based on the Boolean inputs for p, q.

3. Use a block comment to neutralize the example code between lines 36 - 44.

4. Starting on line 46, develop code to:
	a. ask the user for Boolean inputs representative of the p and q the user wishes to evaluate.
	b. ask the user which rule of inference they wish to employ and call the asoociated method using the values from (a) as parameters.
	c. print the return value from the rule of inference method.

5. Modify the program header on lines 3 - 10. Add your information; don't remove mine. 

## Rubric
The grading rubric for this lab is as follows. You can construct your testing procedures based on the rubric, FYI.

   1. Does the program compile or run without error?
   2. Does the program present me with instructions to use, enter propositions, and select a rule of inference?
   3. Does the program output the correct Truth Values for (a) modus ponens and (b) modus tollens in all `p -> q` combinations?
