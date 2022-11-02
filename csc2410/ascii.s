// Matt Burton

//To compile:
// as -o smaller.o smaller.s
// gcc -o smaller.o smaller.s

//To execute:
// ./smaller.o; echo $?

.global main
main:
    mov r0, #33
    mov r1, #30
    mov r2, #39
    cmp r0, r1
    bge overThirty
    blt less
    bgt more

overThirty:
    cmp r0, r2
    ble between

between:
    sub r0, #30
    b end

less:
    mov r0, #50
    b end

more:
    mov r0, #50
    b end

end:
    bx lr
