.globl gemv

.text
# =======================================================
# FUNCTION: Matrix Vector Multiplication
# 	d = gemv(m0, m1)
#   If the dimensions don't match, exit with exit code 2
# Arguments:
# 	a0 is the pointer to the start of m0
#	a1 is the # of rows (height) of m0
#	a2 is the # of columns (width) of m0
#	a3 is the pointer to the start of v
# 	a4 is the # of rows (height) of v
#	a5 is the pointer to the the start of d
# Returns:
#	None, sets d = gemv(m0, m1)
# =======================================================
gemv:

    # Error if mismatched dimensions
    bne a2, a4, mismatched_dimensions
    
    # Prologue
    addi sp, sp, -44
    sw   a0, 0(sp)  # start of m
    sw   a1, 4(sp)  # rows of m0
    sw   a2, 8(sp)  # col of m0
    sw   a3, 12(sp) # start of v
    sw   a4, 16(sp) # row of v
    sw   a5, 20(sp) # start of d

    sw   s0, 24(sp)
    sw   s1, 28(sp)
    sw   s2, 32(sp)
    sw   s3, 36(sp)
    sw   ra, 40(sp)

    li   s0, 0      # i

outer_loop_start_gemv:

	lw   t0, 4(sp)   # rows of m0
	bge  s0, t0, outer_loop_end_gemv

	lw   t0, 8(sp)   # col of m0
	slli t0, t0, 2
	mul  t0, t0, s0  # i
	lw   a0, 0(sp)   # start of m
	add  a0, a0, t0
	lw   a1, 12(sp)
	lw   a2, 8(sp)
	jal  dot

	# d[i] = a0
	slli t0, s0, 2  # i
	lw   t1, 20(sp) # start of d
	add  t1, t1, t0
	sw   a0, 0(t1)

	addi s0, s0, 1
	j outer_loop_start_gemv

outer_loop_end_gemv:

#Epilogue
    lw s0, 24(sp)
    lw s1, 28(sp)
    lw s2, 32(sp)
    lw s3, 36(sp)
    lw ra, 40(sp)
    addi sp, sp, 44

    ret

mismatched_dimensions:
    li a1 2
    jal exit2
    