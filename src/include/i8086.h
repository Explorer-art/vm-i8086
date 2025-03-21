#pragma once

#include <stdint.h>

typedef union {
	uint16_t base;
	struct {
		uint8_t low;
		uint8_t high;
	};
} Register;

typedef struct {
	Register AX;
	Register BX;
	Register CX;
	Register DX;
	uint16_t SP;
	uint16_t BP;
	uint16_t SI;
	uint16_t DI;
	uint16_t CS;
	uint16_t DS;
	uint16_t SS;
	uint16_t ES;
	uint16_t IP;
	uint16_t FLAGS;
} Registers;

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
#define MOV_REG_VALUE 0b1011
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
#define ADD_8REG_VALUE 0x80
#define ADD_16REG_VALUE 0x83
#define ADD_AL_VALUE 0x04
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
#define INC_DEC 0xFE
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
