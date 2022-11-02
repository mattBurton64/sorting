/*
Matt Burton
csc2410
Yong Wei
Lab 11 - Sum all the numbers between 0 and 22 which are even and return the value in r0

to compile:
as -o evenSum.o evenSum.s
gcc -o evenSum evenSum.o

to execute:
./evenSum; echo $?

expected answer: 132
*/
.global main

main:
  mov r0, #0 //sum of all values
  mov r1, #0 //counter index
  mov r2, #22 //max value
  mov r3, #0 //mod check value
  mov r4, #1 //step value
  mov r5, #2 //even divisor number
  b loop

loop:
 while_condition:
  cmp r1, r2 //compare the counter to the max value
  bge end

  add r1, r1, r4 //increment counter by step value

  udiv r6, r1, r5
  mul r7, r6, r5
  sub r8, r1, r7
  cmp r8, r3
  beq sum

  b while_condition

sum:
 add r0, r0, r1 //add counter value to r0 
 b loop

end:
 bx lr
