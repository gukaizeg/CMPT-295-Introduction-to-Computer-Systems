.globl read_matrix


.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#   If any file operation fails or doesn't read the proper number of bytes,
#   exit the program with exit code 1.
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 is the pointer to string representing the filename
# Returns:
#   a0 is the pointer to the matrix in memory
#   a1 is a pointer to an integer, we will set it to the number of rows
#   a2 is a pointer to an integer, we will set it to the number of columns
# ==============================================================================
read_matrix:
    # prologue
    # check file path
    # malloc row pointer
    # Malloc col pointer
    # Read number of cols
    # Read number of rows
    # Calculate bytes
    # Allocate space for matrix and read it.
    # Return value
    # Epilogue
    addi sp, sp, -40
    sw   a0, 0(sp)  # filename
    sw   s0, 4(sp)   
    sw   s1, 8(sp)   
    sw   s2, 12(sp)  
    sw   ra, 16(sp) 

    # open file
    lw  a1, 0(sp)
    li  a2, 0
    jal fopen
    beq a0, zero, eof_or_error
    sw  a0, 20(sp)  # fp

    # read byte 0-3, 
    lw   a1, 20(sp) # fp
    addi a2, sp, 24   # row
    li   a3, 4
    jal  fread 
    li   t0, 4
    bne  a0, t0, eof_or_error

    # read byte 4-7 
    lw   a1, 20(sp) # fp
    addi a2, sp, 28   # col
    li   a3, 4
    jal  fread 
    li   t0, 4
    bne  a0, t0, eof_or_error


    # s1 total number of element
    lw t0, 24(sp)
    lw s1, 28(sp)
    mul s1, s1, t0

    # malloc space
    slli a0, s1, 2
    jal malloc
    beq a0, zero, eof_or_error
    mv  s0, a0  # s0 is the base address


    # read remainning data
    slli s1, s1, 2

    lw   a1, 20(sp) # fp
    mv   a2, s0
    mv   a3, s1
    jal  fread 
    mv   t0, s1
    bne  a0, t0, eof_or_error

    # close file
    lw   a1, 20(sp) # fp
    jal  fclose
	bne  a0, zero, eof_or_error


    # return 3 value
    mv   a0, s0
    lw   a1, 24(sp)
    lw   a2, 28(sp)
    
    lw   s0, 4(sp)   
    lw   s1, 8(sp)   
    lw   s2, 12(sp)  
    lw   ra, 16(sp) 
    addi sp, sp, 40
    
    ret

eof_or_error:
    li a1 1
    jal exit2
