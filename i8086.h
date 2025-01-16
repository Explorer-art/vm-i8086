#pragma once

#include <stdint.h>

typedef struct {
	uint16_t AX;
	uint16_t BX;
	uint16_t CX;
	uint16_t DX;
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
#define DL_REG 0xB6
#define BL_REG 0xB7
#define AX_REG 0xB8
#define CX_REG 0xB9
#define DX_REG 0xBA
#define BX_REG 0xBB
#define MOV_REG_REG 0x89
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
#define ADD_REG_REG 0x01
#define SUB_REG_REG 0x29
#define ADD_AX_AX 0xC0
#define ADD_AX_BX 0xD8
#define ADD_AX_CX 0xC8
#define ADD_AX_DX 0xD0
#define ADD_BX_AX 0xC3
#define ADD_BX_BX 0xDB
#define ADD_BX_CX 0xCB
#define ADD_BX_DX 0xD3
#define ADD_CX_AX 0xC1
#define ADD_CX_BX 0xD9
#define ADD_CX_CX 0xC9
#define ADD_CX_DX 0xD1
#define ADD_DX_AX 0xC2
#define ADD_DX_BX 0xDA
#define ADD_DX_CX 0xCA
#define ADD_DX_DX 0xD2
#define INC_DEC 0xFE
#define INC_AX 0x40
#define INC_CX 0x41
#define INC_DX 0x42
#define INC_BX 0x43
#define INC_AL 0xC0
#define INC_CL 0xC1
#define INC_DL 0xC2
#define INC_BL 0xC3
#define INC_AH 0xC4
#define INC_CH 0xC5
#define INC_DH 0xC6
#define INC_BH 0xC7
#define DEC_AX 0x48
#define DEC_CX 0x49
#define DEC_DX 0x4A
#define DEC_BX 0x4B
#define DEC_AL 0xC8
#define DEC_CL 0xC9
#define DEC_DL 0xCA
#define DEC_BL 0xCB
#define DEC_AH 0xCC
#define DEC_CH 0xCD
#define DEC_DH 0xCE
#define DEC_BH 0xCF
#define NOP 0x90
#define HLT_INS 0xF4