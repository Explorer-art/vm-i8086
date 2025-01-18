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
#define DH_REG 0xB6
#define BH_REG 0xB7
#define AX_REG 0xB8
#define CX_REG 0xB9
#define DX_REG 0xBA
#define BX_REG 0xBB
#define MOV_8REG_REG 0x88
#define MOV_AL_AL 0xC0
#define MOV_AL_BL 0xD8
#define MOV_AL_CL 0xC8
#define MOV_AL_DL 0xD0
#define MOV_BL_AL 0xC3
#define MOV_BL_BL 0xDB
#define MOV_BL_CL 0xCB
#define MOV_BL_DL 0xD3
#define MOV_CL_AL 0xC1
#define MOV_CL_BL 0xD9
#define MOV_CL_CL 0xC9
#define MOV_CL_DL 0xD1
#define MOV_DL_AL 0xC2
#define MOV_DL_BL 0xDA
#define MOV_DL_CL 0xCA
#define MOV_DL_DL 0xD2
#define MOV_AH_AH 0xE4
#define MOV_AH_BH 0xFC
#define MOV_AH_CH 0xEC
#define MOV_AH_DH 0xF4
#define MOV_BH_AH 0xE7
#define MOV_BH_BH 0xFF
#define MOV_BH_CH 0xEF
#define MOV_BH_DH 0xF7
#define MOV_CH_AH 0xE5
#define MOV_CH_BH 0xFD
#define MOV_CH_CH 0xED
#define MOV_CH_DH 0xF5
#define MOV_DH_AH 0xE6
#define MOV_DH_BH 0xFE
#define MOV_DH_CH 0xEE
#define MOV_DH_DH 0xF6
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
#define SUB_8REG_REG 0x28
#define SUB_16REG_REG 0x29
#define OP_AX_AX 0xC0
#define OP_AX_BX 0xD8
#define OP_AX_CX 0xC8
#define OP_AX_DX 0xD0
#define OP_BX_AX 0xC3
#define OP_BX_BX 0xDB
#define OP_BX_CX 0xCB
#define OP_BX_DX 0xD3
#define OP_CX_AX 0xC1
#define OP_CX_BX 0xD9
#define OP_CX_CX 0xC9
#define OP_CX_DX 0xD1
#define OP_DX_AX 0xC2
#define OP_DX_BX 0xDA
#define OP_DX_CX 0xCA
#define OP_DX_DX 0xD2
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
