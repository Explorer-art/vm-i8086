#pragma once

#include <stdint.h>

/*
R/M - Register/Memory
IMM - Immediate

RM8 - R/M byte
RM16 - R/M word
IMM8 - IMM byte
IMM16 - IMM word
*/

#define ADD_RM8_REG 0x00
#define ADD_RM16_REG 0x01
#define ADD_AL_IMM8 0x04
#define ADD_AX_IMM16 0x05

#define AND_RM8_REG 0x20
#define AND_RM16_REG 0x21
#define AND_AL_IMM8 0x24
#define AND_AX_IMM16 0x25

#define XOR_RM8_REG 0x30
#define XOR_RM16_REG 0x31
#define XOR_AL_IMM8 0x34
#define XOR_AX_IMM16 0x35

#define OR_RM8_REG 0x08
#define OR_RM16_REG 0x09
#define OR_AL_IMM8 0x0C
#define OR_AX_IMM16 0x0D

#define SUB_RM8_REG 0x28
#define SUB_RM16_REG 0x29
#define SUB_AL_IMM8 0x2C
#define SUB_AX_IMM16 0x2D

#define INC_AX 0x40
#define INC_CX 0x41
#define INC_DX 0x42
#define INC_BX 0x43

#define DEC_AX 0x48
#define DEC_CX 0x49
#define DEC_DX 0x4A
#define DEC_BX 0x4B

#define MOV_AL_IMM8 0xB0
#define MOV_CL_IMM8 0xB1
#define MOV_DL_IMM8 0xB2
#define MOV_BL_IMM8 0xB3
#define MOV_AH_IMM8 0xB4
#define MOV_CH_IMM8 0xB5
#define MOV_DH_IMM8 0xB6
#define MOV_BH_IMM8 0xB7
#define MOV_RM8_REG 0x88
#define MOV_RM16_REG 0x89

#define AL_REG 0xB0
#define CL_REG 0xB1
#define DL_REG 0xB2
#define BL_REG 0xB3
#define AH_REG 0xB4
#define CH_REG 0xB5
#define DH_REG 0xB6
#define BH_REG 0xB7
#define AX_REG 0xB8
#define CX_REG 0xB9
#define DX_REG 0xBA
#define BX_REG 0xBB
#define MOV_8REG_REG 0x88
#define MOV_16REG_REG 0x89
#define MOV_AX_AX 0xC0
#define MOV_AX_BX 0xD8
#define MOV_AX_CX 0xC8
#define MOV_AX_DX 0xD0
#define MOV_BX_AX 0xC3
#define MOV_BX_BX 0xDB
#define MOV_BX_CX 0xCB
#define MOV_BX_DX 0xD3
#define MOV_CX_AX 0xC1
#define MOV_CX_BX 0xD9
#define MOV_CX_CX 0xC9
#define MOV_CX_DX 0xD1
#define MOV_DX_AX 0xC2
#define MOV_DX_BX 0xDA
#define MOV_DX_CX 0xCA
#define MOV_DX_DX 0xD2
#define ADD_8REG_REG 0x00
#define ADD_16REG_REG 0x01
#define ADD_AL_VALUE 0x04
#define ADD_AX_VALUE 0x05
#define ADD_CL 0xC1
#define ADD_DL 0xC2
#define ADD_BL 0xC3
#define ADD_AH 0xC4
#define ADD_CH 0xC5
#define ADD_DH 0xC6
#define ADD_BH 0xC7
#define ADD_AX 0xC0
#define ADD_CX 0xC1
#define ADD_DX 0xC2
#define ADD_BX 0xC3
#define SUB_8REG_REG 0x28
#define SUB_16REG_REG 0x29
#define SUB_AL_VALUE 0x2C
#define SUB_AX_VALUE 0x2D
#define INC_DEC_R8 0xFE
#define INC_AX 0x40
#define INC_CX 0x41
#define INC_DX 0x42
#define INC_BX 0x43
#define DEC_AX 0x48
#define DEC_CX 0x49
#define DEC_DX 0x4A
#define DEC_BX 0x4B
#define INC_AL 0xC0
#define INC_CL 0xC1
#define INC_DL 0xC2
#define INC_BL 0xC3
#define INC_AH 0xC4
#define INC_CH 0xC5
#define INC_DH 0xC6
#define INC_BH 0xC7
#define DEC_AL 0xC8
#define DEC_CL 0xC9
#define DEC_DL 0xCA
#define DEC_BL 0xCB
#define DEC_AH 0xCC
#define DEC_CH 0xCD
#define DEC_DH 0xCE
#define DEC_BH 0xCF
#define AND_8REG_REG 0x20
#define AND_16REG_REG 0x21
#define AND_AL_VALUE 0x24
#define AND_AX_VALUE 0x25
#define AND_16REG_VALUE 0x81
#define OR_8REG_REG 0x08
#define OR_16REG_REG 0x09
#define OR_AL_VALUE 0x0C
#define OR_AX_VALUE 0x0D
#define NOT_8REG 0xF6
#define NOT_16REG 0xF7
#define NOT_AL 0xD0
#define NOT_CL 0xD1
#define NOT_DL 0xD2
#define NOT_BL 0xD3
#define NOT_AH 0xD4
#define NOT_CH 0xD5
#define NOT_DH 0xD6
#define NOT_BH 0xD7
#define NOT_AX 0xD0
#define NOT_CX 0xD1
#define NOT_DX 0xD2
#define NOT_BX 0xD3
#define XOR_8REG_REG 0x30
#define XOR_16REG_REG 0x31
#define NOP 0x90
#define HLT_INS 0xF4

void mov8(uint8_t* dst, uint8_t* src);
void mov16(uint16_t* dst, uint16_t* src);
void add8(uint8_t* dst, uint8_t* src);
void add16(uint16_t* dst, uint16_t* src);
void sub8(uint8_t* dst, uint8_t* src);
void sub16(uint16_t* dst, uint16_t* src);
void and8(uint8_t* dst, uint8_t* src);
void and16(uint16_t* dst, uint16_t* src);
void or8(uint8_t* dst, uint8_t* src);
void or16(uint16_t* dst, uint16_t* src);
void xor8(uint8_t* dst, uint8_t* src);
void xor16(uint16_t* dst, uint16_t* src);
