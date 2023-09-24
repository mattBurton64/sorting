# Assignment 3
Write a generic sorting method that works on all data types as well as a custom list of colors

## Directories
Script - contains the shell automation scripts used for compiling and executing the sort program  
Source - contains the generic C++ sort program and its executable  
TestFiles - contains the set of test files separated into folders which define their data type that are passed into the program as input  

## Usage
For commands to work as expected, make sure you are in the assignment3/ directory.

To execute the sorting program run...
```
./Script/consolidate.sh
```
## Output
After running the consolidate script the terminal should look like this...
```
Compiling program
=================
sort.cpp compiled

Executing
=========
sort.cpp
characters.txt
Vector before sorting...
t
f
9
0
{
]
s
v
`
:
n
S
e
V
c
1
a
x
Z
!
.
%

Vector after sorting...
!
%
.
0
1
9
:
S
V
Z
]
`
a
c
e
f
n
s
t
v
x
{

colors.txt
Vector before sorting...
ORANGE
RED
BLUE
GREEN
INDIGO
YELLOW
RED
VIOLET
ORANGE
BLUE
BLUE
YELLOW

Vector after sorting...
RED
RED
ORANGE
ORANGE
YELLOW
YELLOW
GREEN
BLUE
BLUE
BLUE
INDIGO
VIOLET

floats.txt
Vector before sorting...
0
-1.2
-5.8
1.1
9.72
2.264
-2.353
3.14
0.2141
6.32
-7.293

Vector after sorting...
-7.293
-5.8
-2.353
-1.2
0
0.2141
1.1
2.264
3.14
6.32
9.72

integers.txt
Vector before sorting...
-8
5
1
99
-32
213
40
2
-2
723
-9402

Vector after sorting...
-9402
-32
-8
-2
1
2
5
40
99
213
723

strings.txt
Vector before sorting...
Java
C++
Python
methods
functions
objects
class
123
ABC
xyz
attributes
variables
error
input
output
Ruby
Ada
Perl
HTML
TypeScript
program
code
<element>

Vector after sorting...
123
<element>
ABC
Ada
C++
HTML
Java
Perl
Python
Ruby
TypeScript
attributes
class
code
error
functions
input
methods
objects
output
program
variables
xyz

Sorting complete
```

## Credits
Matt Burton - author of programs and scripts  
ChatGPT - explained how to use templates and overloaded functions
Michael Oudshoorn - provided an exampe of generics in Ada for reference 