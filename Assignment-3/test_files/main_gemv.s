.import ../read_matrix.s
.import ../gemv.s
.import ../dot.s
.import ../utils.s

.data
output_step1: .asciiz "\n**Step result = gemv(matrix, vector)**\n"


.globl main

.text
main:
    # =====================================
    # COMMAND LINE ARGUMENTS
    # =====================================
    # Args:
    #   a0: int argc
    #   a1: char** argv
    #
    # Usage:
    #   main.s <VECTOR_PATH> <MATRIX_PATH> 

    # Exit if incorrect number of command line args
    li  t0, 3
    bne a0, t0, main_exit3
    
    # Prologue
    addi sp, sp, -80
    sw   a0, 0(sp)   
    sw   a1, 4(sp)   
    sw   s0, 8(sp)   
    sw   s1, 12(sp) 
    sw   s2, 16(sp)  
    sw   s3, 20(sp)  
    sw   ra, 24(sp)  


# =====================================
# LOAD MATRIX and VECTOR. Iterate over argv.
# =====================================
# Load Matrix        
# Load Vector


	lw  t0, 4(sp)   
	lw  a0, 4(t0)
    jal read_matrix
    sw  a0, 28(sp) # mat 1
    sw  a1, 32(sp) # row 1
    sw  a2, 36(sp) # col 1


	lw  t0, 4(sp)   
	lw  a0, 8(t0)
    jal read_matrix
    sw  a0, 40(sp) # mat 2
    sw  a1, 44(sp) # row 2
    sw  a2, 48(sp) # col 2

    # lw a1 , 48(sp)
    # jal print_int

# =====================================
# RUN GEMV
# =====================================
# SPMV :    m * v


	lw  a0, 44(sp) # row 2
	slli a0, a0, 2
	jal malloc
	beq a0, zero, main_exit3
	sw  a0, 52(sp) # return

	lw a0, 40(sp) # mat 2
	lw a1, 44(sp) # row 2
	lw a2, 48(sp) # col 2
	lw a3, 28(sp) # mat 1
	lw a4, 32(sp) # row 1
	lw a5, 52(sp) # return
	jal gemv

    la a1, output_step1
    jal print_str

    ## FILL OUT. Output is a dense vector.
    lw a0, 52(sp) # return
    lw a1, 44(sp) # row 2
    li a2, 1
    jal print_int_array 


    lw a0, 28(sp)
    jal free
    lw a0, 40(sp)
    jal free
    lw a0, 52(sp)
    jal free


    # Prologue
    addi sp, sp, 80
    lw   a0, 0(sp)   
    lw   a1, 4(sp)   
    lw   s0, 8(sp)   
    lw   s1, 12(sp) 
    lw   s2, 16(sp)  
    lw   s3, 20(sp)  
    lw   ra, 24(sp)  


    jal exit


    
main_exit3:
    li a1 3
    jal exit2





    
 




















    # Print newline afterwards for clarity
    li a1 '\n'
    jal print_char

    jal exit
