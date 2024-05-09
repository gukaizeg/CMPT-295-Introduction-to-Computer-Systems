#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* Sign extends the given field to a 32-bit integer where field is
 * interpreted an n-bit integer. */
int sign_extend_number(unsigned   field, unsigned   n)
{
    /* YOUR CODE HERE */
    field = field << (32 - n);
    int ret = field;
    ret = ret >> (32 - n);
    return ret;
}

/* Unpacks the 32-bit machine code instruction given into the correct
 * type within the instruction struct */
Instruction parse_instruction(uint32_t instruction_bits)
{
    /* YOUR CODE HERE */
    Instruction instruction;
    // add x8, x0, x0     hex : 00000433  binary = 0000 0000 0000 0000 0000 01000
    // Opcode: 0110011 (0x33) Get the Opcode by &ing 0x1111111, bottom 7 bits
    instruction.opcode = instruction_bits & ((1U << 7) - 1);

    // Shift right to move to pointer to interpret next fields in instruction.
    instruction_bits >>= 7;

    switch (instruction.opcode)
    {
        // (1) R-Type
    case 0x33:
    case 0x2b: //--
        // instruction: 0000 0000 0000 0000 0000 destination : 01000
        instruction.rtype.rd = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 0000 0000 0000 0 func3 : 000
        instruction.rtype.funct3 = instruction_bits & ((1U << 3) - 1);
        instruction_bits >>= 3;

        // instruction: 0000 0000 0000  src1: 00000
        instruction.rtype.rs1 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 000        src2: 00000
        instruction.rtype.rs2 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // funct7: 0000 000
        instruction.rtype.funct7 = instruction_bits & ((1U << 7) - 1);
        break;
        // (2) case for I-type 
    case 0x03:
    case 0x13:
    case 0x73:
        // instruction: 0000 0000 0000 0000 0000 destination : 01000
        instruction.itype.rd = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 0000 0000 0000 0 func3 : 000
        instruction.itype.funct3 = instruction_bits & ((1U << 3) - 1);
        instruction_bits >>= 3;

        // instruction: 0000 0000 0000  src1: 00000
        instruction.itype.rs1 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 000        src2: 00000
        instruction.itype.imm = instruction_bits & ((1U << 12) - 1);
        instruction_bits >>= 12;
        break;

        // (3) case for S-type 
    case 0x23:
        // instruction: 0000 0000 0000 0000 0000 destination : 01000
        instruction.stype.imm5 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 0000 0000 0000 0 func3 : 000
        instruction.stype.funct3 = instruction_bits & ((1U << 3) - 1);
        instruction_bits >>= 3;

        // instruction: 0000 0000 0000  src1: 00000
        instruction.stype.rs1 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 000        src2: 00000
        instruction.stype.rs2 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // funct7: 0000 000
        instruction.stype.imm7 = instruction_bits & ((1U << 7) - 1);
        break;


        // (4) case for SB-type 
    case 0x63:
        // instruction: 0000 0000 0000 0000 0000 destination : 01000
        instruction.sbtype.imm5 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 0000 0000 0000 0 func3 : 000
        instruction.sbtype.funct3 = instruction_bits & ((1U << 3) - 1);
        instruction_bits >>= 3;

        // instruction: 0000 0000 0000  src1: 00000
        instruction.sbtype.rs1 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 000        src2: 00000
        instruction.sbtype.rs2 = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // funct7: 0000 000
        instruction.sbtype.imm7 = instruction_bits & ((1U << 7) - 1);
        break;


        // (5) case for U-type 
    case 0x37:
        // case 0x17:
            // instruction: 0000 0000 0000 0000 0000 destination : 01000
        instruction.utype.rd = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 0000 0000 0000 0 func3 : 000
        instruction.utype.imm = instruction_bits & ((1U << 20) - 1);

        break;

        // (6) case for UJ-type 
    case 0x6f:
        // instruction: 0000 0000 0000 0000 0000 destination : 01000
        instruction.ujtype.rd = instruction_bits & ((1U << 5) - 1);
        instruction_bits >>= 5;

        // instruction: 0000 0000 0000 0000 0 func3 : 000
        instruction.ujtype.imm = instruction_bits & ((1U << 20) - 1);

        break;


    default:
        exit(EXIT_FAILURE);
    }
    return instruction;
}

/* Return the number of bytes (from the current PC) to the branch label using
 * the given branch instruction */
int get_branch_offset(Instruction instruction)
{
    /* YOUR CODE HERE */
    unsigned int tmp, ret = 0;
    ret = instruction.sbtype.imm5 & (~1);

    unsigned int bit11 = instruction.sbtype.imm5 & 1;
    unsigned int bit12 = instruction.sbtype.imm7 >> 6;

    tmp = instruction.sbtype.imm7 & ((1U << 6) - 1);
    ret |= tmp << 5;
    ret |= bit11 << 11;
    ret |= bit12 << 12;
    return ret;
}

/* Returns the number of bytes (from the current PC) to the jump label using the
 * given jump instruction */
int get_jump_offset(Instruction instruction)
{
    /* YOUR CODE HERE */

    unsigned bit_19_12 = instruction.ujtype.imm & ((1U << 8) - 1);
    unsigned bit_11 = (instruction.ujtype.imm >> 8) & 1;
    unsigned bit_10_1 = (instruction.ujtype.imm >> 9) & ((1U << 10) - 1);
    unsigned bit_20 = (instruction.ujtype.imm >> 19) & 1;

    unsigned int ret = 0;

    ret |= bit_10_1 << 1;
    ret |= bit_11 << 11;
    ret |= bit_19_12 << 12;
    ret |= bit_20 << 20;

    return ret;
}

int get_store_offset(Instruction instruction)
{
    /* YOUR CODE HERE */
    unsigned int ret = instruction.stype.imm5 | (instruction.stype.imm7 << 5);
    return ret;
}

void handle_invalid_instruction(Instruction instruction)
{
    printf("Invalid Instruction: 0x%08x\n", instruction.bits);
}

void handle_invalid_read(Address address)
{
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address)
{
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}
