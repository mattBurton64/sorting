# Assignment 2
Investigating how parameter passing works and differs in C++ and Java

## Usage
Run the follow command from the assignment2 folder for it to work as expected

```
./Script/consolidate.sh
```

## Output
Below is a sample of the expected output

```
Compiling programs
==================
value.cpp compiled
reference.cpp compiled
value-result.cpp compiled
scope.cpp compiled
alias.cpp compiled
delete.cpp compiled
Value.java compiled
ValueResult.java compiled
Scope.java compiled

Testing
=======
value.cpp
Integer
=======
before: 1
 after: 1

Float
=====
before: 1
 after: 1

Boolean
=======
before: 1
 after: 1

Character
=========
before: a
 after: a

Small Array
===========
before: 0 0 0 0 0 
 after: 1 1 1 1 1 

Large Array
===========
before: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 after: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 

reference.cpp
Integer
=======
before: 1
 after: 0

Float
=====
before: 1
 after: 0

Boolean
=======
before: 1
 after: 0

Character
=========
before: a
 after: z

Small Array
===========
before: 0 0 0 0 0 
 after: 1 1 1 1 1 

Large Array
===========
before: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 after: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 

value-result.cpp
Integer
=======
before: 1
 after: 0

Float
=====
before: 1
 after: 0

Boolean
=======
before: 1
 after: 0

Character
=========
before: a
 after: z

Small Array
===========
before: 0 0 0 0 0 
 after: 1 1 1 1 1 

Large Array
===========
before: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 after: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 

scope.cpp
Integer
=======
before: 1
 after: 0

alias.cpp
  Integer before: 1
  Pointer before: 1
Reference before: 1
   Integer after: 0
   Pointer after: 0
 Reference after: 0

delete.cpp
dyld[18639]: Symbol not found: __ZdlPvm
  Referenced from: <E4C49EC5-FFEB-3537-A2F2-1A92D9241E1E> /Users/matt/Documents/GitHub/college-classes/csc4510/assignment2/Source/cpp/delete.o
  Expected in:     <3F5CB4D5-26D1-3E43-B241-2688FF0A67BD> /usr/lib/libstdc++.6.dylib
./Script/consolidate.sh: line 40: 18639 Abort trap: 6           ./Source/cpp/delete.o

Value.java
Integer
=======
before: 1
 after: 1

Float
=====
before: 1.0
 after: 1.0

Boolean
=======
before: true
 after: true

Character
=========
before: a
 after: a

Small Array
===========
before: 0 0 0 0 0 
 after: 1 1 1 1 1 

Large Array
===========
before: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 after: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 

ValueResult.java
Integer
=======
before: 1
 after: 0

Float
=====
before: 1.0
 after: 0.0

Boolean
=======
before: true
 after: false

Character
=========
before: a
 after: z

Small Array
===========
before: 0 0 0 0 0 
 after: 1 1 1 1 1 

Large Array
===========
before: 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 after: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 

Scope.java
Integer
=======
before: 1
 after: 0
Testing complete
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
Dangling Pointers

## Instructions
Write programs in C++ and Java that explore the parameter passing mechanism in each language, the issue of aliasing and side effects, and the interaction of scope rules, aliasing, side effects and parameter passing to identify strengths and weaknesses in each language. Specifically, you are asked to create small experiments to identify what kind of parameter passing mechanism each language supports (call by value, call by reference etc) and if it is consistent across different types of values/objects or if the semantics change is the entity passed is large. Can you create examples where multiple names exist to refer to the same memory location? What happens of you delete the memory location? Can you create a legal reference to a memory location that should no longer be accessible? How do pointers1 cause problems? As you can see from the examples provided, the code fragments you need to write to demonstrate your point are typically quite small.

## Credits
Matt Burton - Programs and essay
ChatGPT - experimental workarounds for features that don't exist in Java
Concepts of Programming Langiages Chapter 9.5 - background information on parameter passing