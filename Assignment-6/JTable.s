main:
addi a0,zero,1
addi t1,t1,1
beq a0,t1,choice1
addi t1,t1,1
beq a0,t1,choice2
addi t1,t1,1
beq a0,t1,choice3
choice1: # Jumped into choice 1
j end
choice2: # Jumped into choice 2.
j end
choice3:
j end
end:
addi a7, zero, 10
ecall # terminate ecall