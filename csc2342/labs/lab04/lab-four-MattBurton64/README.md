# CSC2342-01 F20 Lab Four
## Dr. Jason M. Pittman

## Purpose
The purpose of this work is to implement programmatic logic such that a user can enter a set or sets, an assignment of elements, select from possible function types, and have the program determine whether the given element assignments are valid.

## Requirements
Your program, at a minimum, must include the following features. Be certain to submit your assignment through the GitHub Classroom assignment after you are finished programming *and* testing.

## Features
   The minimum features are as follows. I recommend programming to each successive feature and testing it before moving on.

   1.  Ask the user to input a set or multiple sets to be defined as *1,2,3* or *a,b,c*. You can instruct the user to enter elements however you wish but you must accept arbitrary but finite input of either *char* or *int* types. You can name the sets internally whatever you wish.
   2.  Ask the user to select the function from a menu of:
      (1) One-to-One
      (2) Onto
   3. Compute a valid set of element assignments for the selected function. 
      **DO NOT HARDCODE THIS**. Program the *rules*!
   4. Display the function output (e.g., f: 1 -> c, 2 -> a, 3 -> c).
   5. Ask the user if they would like to enter another set or quit.

*Hint: set cardinality can help determine if a function type is valid given the set inputs. Think about it.

## Rubric
The grading rubric for this lab is as follows. You can construct your testing procedures based on the rubric, FYI.

   1. Does the program compile or run without error?
   2. Does the program present me with instructions to use, enter sets, and select functions?
   3. Does the program generate valid assignments for the selected function?   
      3.1 Two sets: {1,2,3}, {a,b,c}  
         a *Onto* = ?  
         b *One-to-One* = ?  
      3.4 Two sets: {1,2,3,4}, {a,b,c}  
         a *Onto* = ?  
         b *One-to-One* = ?  
      3.5 Two sets: {1,2,3}, {a,b,c,d}  
         a *Onto* = ?  
         b *One-to-One* = ? 
