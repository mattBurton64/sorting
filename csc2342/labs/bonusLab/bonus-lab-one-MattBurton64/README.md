# CSC2342-01 SP21 Bonus Lab One
## Dr. Jason M. Pittman

## Purpose
We're going to explore the Von Neumann universe construct by iteratively (recursively) computing the power set based on an intitial null set input.

## Instructions
1. Build a function, `P()` or `PowerSet()` to compute the power set of given set `S`. You may set the intitial element(s) of `S` in the source as opposed to asking the user for input. Use zero ( 0 ) instead of the null character.   

2. Use a loop (I recommend `while()`) to iterate no less than five generations. Run more generations at your own risk.  

3. For each generation, output the elapsed time as `generation [n]: [elapsed time]` where the relevant values are inserted in the `[ ]`.

4. For each geneartion, output the complete computed power set to a new line in a plain text file named `results.txt`. The file should exist in this repository (along with your source code!).  

5. For each generation, use the computed power set as input to a recursive call to your `P()` or `PowerSet()` function.

## Examples
The expected output for two generations is:  

```
  P(0)={0}  
  P({0})={0,{0}}  
```

## Submission
You must submit your Python source code and the final `results.txt` to receive full credit through this GitHub Classroom repository.
