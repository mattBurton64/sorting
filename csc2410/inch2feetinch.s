/* -- myMod.s */
.global main
main:
mov r1, #121 /* starting number of inches */
mov r2, #12 /* inches per foot */
udiv r3, r1, r2 /* divides inches by 12 */
mul r4, r3, r2 /* determine number of inches from feet, used for getting remaining inches */
udiv r11, r1, r2 /* number of feet */
sub r12, r1, r4 /* number of inches */
bx lr
