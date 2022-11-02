/* -- myMod.s */
.global main
main:
mov r1, #5 /* y */
mov r2, #4 /* x */
udiv r3, r2, r1
mul r4, r3, r1
sub r0, r2, r4
bx lr
