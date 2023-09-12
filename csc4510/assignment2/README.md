# Assignment 2
Investigating how parameter passing works and differs in C++ and Java

## Usage
To compile a Java program use
```
javac progam.java
```
To run a Java program use
```
java Program
```

To compile a C++ program use
```
g++ program.cpp -o program.o
```
To run a C++ program use
```
./program.o
```

## Investigations
Call by Value
Call by Reference
Call by Value-Result
Call by Name
Call by Result
Scope
Aliasing
Side Effects

## Instructions
Write programs in C++ and Java that explore the parameter passing mechanism in each language, the issue of aliasing and side effects, and the interaction of scope rules, aliasing, side effects and parameter passing to identify strengths and weaknesses in each language. Specifically, you are asked to create small experiments to identify what kind of parameter passing mechanism each language supports (call by value, call by reference etc) and if it is consistent across different types of values/objects or if the semantics change is the entity passed is large. Can you create examples where multiple names exist to refer to the same memory location? What happens of you delete the memory location? Can you create a legal reference to a memory location that should no longer be accessible? How do pointers1 cause problems? As you can see from the examples provided, the code fragments you need to write to demonstrate your point are typically quite small.