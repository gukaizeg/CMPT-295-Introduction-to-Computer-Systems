# This example shows an implementation of adding two numbers

.data
arg1: .word   3
arg2: .word 5
answer: .string "Answer is"
.text
main:
 jal sum	
 la a0,answer
 li a7, 4
 ecall
 mv a0,t2
 li a7, 1
 ecall
 li a7,10
 ecall

sum:
 lw t0, arg1
 lw t1, arg2
 add t2,t0,t1
 ret	