.globl dot

.text
# ======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 is the pointer to the start of v0
#   a1 is the pointer to the start of v1
#   a2 is the length of the vectors
# Returns:
#   a0 is the dot product of v0 and v1
# ======================================================
dot:
    # Prologue
    addi sp, sp, -8
    sw s1, 4(sp)
    sw s0, 0(sp)

    li t3, 0  # sum
    
    li t0, 0  # i
loop_start:
    bge t0, a2, loop_end
    
    lw s0, 0(a0)
    lw s1, 0(a1)
    mul s0, s0, s1
    add t3, t3, s0

    addi a0, a0, 4
    addi a1, a1, 4
    addi t0, t0, 1
    j loop_start
loop_end:

    mv a0, t3

    # Epilogue
    lw s1, 4(sp)
    lw s0, 0(sp)
    addi sp, sp, 8

    ret
