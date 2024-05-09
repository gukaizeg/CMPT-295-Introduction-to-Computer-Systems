.globl sdot

.text
# =======================================================
# FUNCTION: Dot product of 1 sparse vectors and 1 dense vector
# Arguments:
#   a0 is the pointer to the start of v0 (sparse, coo format)
#   a1 is the pointer to the start of v1 (dense)
#   a2 is the number of non-zeros in vector v0
# Returns:
#   a0 is the sparse dot product of v0 and v1
# =======================================================
#
# struct coo {
#   int row;
#   int index;
#   int val;
# };   
# Since these are vectors row = 0 always for v0.
#for (int i = 0 i < nnz; i++) {
#    sum = sum + v0[i].value * v1[coo[i].index];
# }
sdot:
    # Prologue    

    # Save arguments
    addi sp, sp, -44
    sw   s0, 0(sp)  # pointer to the start of v0 sparse
    sw   s1, 4(sp)  # pointer to the start of v1 dense
    sw   s2, 8(sp)  # number of non-zeros in vector v0
    sw   s3, 12(sp)  
    sw   s4, 16(sp)  
    sw   s5, 20(sp)  

    mv   s0, a0
    mv   s1, a1
    mv   s2, a2
    # Set strides. Note that v0 is struct. v1 is array.
    # Set loop index
    # Set accumulation to 0
    li t5, 0

    li   t0, 0
loop_start:

    # Check outer loop condition
    bge  t0, s2, loop_end
    # load v0[i].value. The actual value is located at offset  from start of coo entry
    li   t1, 12
    mul  t1, t1, t0
    add  t1, t1, s0
    # Load v1[coo[i].index]
    lw   t2, 8(t1)  # value of v0
    lw   t3, 4(t1)  # index of v1
    slli t3, t3, 2
    add  t3, t3, s1
    lw   t3, 0(t3)

    # Multiply and accumulate
    mul  t4, t2, t3
    add  t5, t5, t4

    # What is the index of the coo element?
    # Lookup corresponding index in dense vector
    
    
    # Bump ptr to coo entry
    # Increment loop index
    addi t0, t0, 1
    j loop_start
loop_end:
    mv a0, t5

    # Epilogue
    lw   s0, 0(sp)  # pointer to the start of v0 sparse
    lw   s1, 4(sp)  # pointer to the start of v1 dense
    lw   s2, 8(sp)  # number of non-zeros in vector v0
    lw   s3, 12(sp)  
    lw   s4, 16(sp)  
    lw   s5, 20(sp)  
    addi sp, sp, 44

    ret
