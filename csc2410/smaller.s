// Matt Burton

//To compile:
// as -o smaller.o smaller.s
// gcc -o smaller.o smaller.s

//To execute:
// smaller.o; echo $?

.global main
main:
 mov r1, #5
 mov r2, #4
 cmp r1, r2
 beq same
 blt less
 bgt more

same:
 mov r0, r1
 b end

less:
 mov r0, r1
 b end

more:
 mov r0, r2
 b end 

end:
 bx lr
