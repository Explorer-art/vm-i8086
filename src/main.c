#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include <i8086.h>

#define VERSION			"0.1.4"
#define BUFFER_SIZE		1024
#define MEMORY_SIZE 	1048576

/*

VM i8086
Virtual Machine based on Intel 8086 processor

Author: Truzme_
License: MIT

===============================================

CHANGELOG:

v0.1.3
- Added AND opcode
- Code optimization

v0.1.4
- Added OR, NOT, XOR opcodes

*/

void load(uint8_t *memory, FILE *fp, size_t file_length) {
	uint8_t buffer[BUFFER_SIZE];
	uint8_t *memory_ptr = memory;
	int bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
		memcpy(memory_ptr, buffer, bytes_read);
		memory_ptr += bytes_read;
	}
}

void memory_dump(char *filename, uint8_t *memory) {
	FILE *fp = fopen(filename, "wb");

	if (fp == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	fwrite(memory, 1, MEMORY_SIZE, fp);

	fclose(fp);

	printf("Memory dumped!\n");
}

int main(int argc, char* argv[]) {
	Registers registers = {0};

	uint8_t *pregs8[8] = {
		&registers.AX.low, &registers.CX.low, &registers.DX.low, &registers.BX.low,
		&registers.AX.high, &registers.CX.high, &registers.DX.high, &registers.BX.high
	};

	char *reg8_names[8] = {
		"al", "cl", "dl", "bl",
		"ah", "ch", "dh", "bh"
	};

	uint16_t *pregs16[4] = {
		&registers.AX.base, &registers.CX.base, &registers.DX.base, &registers.BX.base
	};

	char *reg16_names[4] = {
		"ax", "cx", "dx", "bx"
	};

	if (argc < 2) {
		printf("Usage: %s <file> [options]\n\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("Usage: %s <file> [options]\n\n", argv[0]);
		printf("Options:\n");
		printf("-d - debug mode\n");
		printf("-vr - view registers values\n");
		printf("-md - create memory dump\n");
		return 0;
	} else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
		printf("VM version: %s\n", VERSION);
		return 0;
	}

	bool DEBUG = false;
	bool REGISTERS_VIEW = false;
	bool MEMORY_DUMP = false;

	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
				DEBUG = true;
			} else if (strcmp(argv[i], "-vr") == 0 || strcmp(argv[i], "--view-registers") == 0) {
				REGISTERS_VIEW = true;
			} else if (strcmp(argv[i], "-md") == 0 || strcmp(argv[i], "--memory-dump") == 0) {
				MEMORY_DUMP = true;
			}
		}
	}

	uint8_t *memory = malloc(MEMORY_SIZE);

	FILE *fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	size_t file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	load(memory, fp, file_length);

	fclose(fp);

	bool HLT = true;

	while (HLT) {
		if (DEBUG) {
			printf("0x%05X ", registers.IP);
		}

		if (DEBUG) {
			printf("%02X ", memory[registers.IP]);
		}

		switch (memory[registers.IP]) {
			case MOV_8REG_REG: {
				if (DEBUG) {
					printf("%02X ", memory[registers.IP++]);
				}

				uint8_t modrm = memory[registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("mov %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] = *pregs8[reg2];
				break;
			}
			case MOV_16REG_REG: {
				if (DEBUG) {
					printf("%02X ", memory[registers.IP++]);
				}

				uint8_t modrm = memory[registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("mov %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] = *pregs16[reg2];
				break;
			}
			case AL_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov al, %X", memory[registers.IP]);
				}

				registers.AX.low = memory[registers.IP];
				break;
			case BL_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov bl, %X", memory[registers.IP]);
				}

				registers.BX.low = memory[registers.IP];
				break;
			case CL_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov cl, %X", memory[registers.IP]);
				}

				registers.CX.low = memory[registers.IP];
				break;
			case DL_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov dl, %X", memory[registers.IP]);
				}

				registers.DX.low = memory[registers.IP];
				break;
			case AH_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov ah, %X", memory[registers.IP]);
				}

				registers.AX.high = memory[registers.IP];
				break;
			case BH_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov bh, %X", memory[registers.IP]);
				}

				registers.BX.high = memory[registers.IP];
				break;
			case CH_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov ch, %X", memory[registers.IP]);
				}

				registers.CX.high = memory[registers.IP];
				break;
			case DH_REG:
				if (DEBUG) {
					printf("%02X ", memory[++registers.IP]);
				}

				if (DEBUG) {
					printf("mov dh, %X", memory[registers.IP]);
				}

				registers.DX.high = memory[registers.IP];
				break;
			case AX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[++registers.IP], memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov ax, %X", memory[registers.IP] | (memory[registers.IP + 1] << 8));
				}

				registers.AX.base = memory[registers.IP] | (memory[++registers.IP] << 8);
				break;
			case BX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[++registers.IP], memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov bx, %X", memory[registers.IP] | (memory[registers.IP + 1] << 8));
				}

				registers.BX.base = memory[registers.IP] | (memory[++registers.IP] << 8);
				break;
			case CX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[++registers.IP], memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov cx, %X", memory[registers.IP] | (memory[registers.IP + 1] << 8));
				}

				registers.CX.base = memory[registers.IP] | (memory[++registers.IP] << 8);
				break;
			case DX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[++registers.IP], memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov dx, %X", memory[registers.IP] | (memory[registers.IP + 1] << 8));
				}

				registers.DX.base = memory[registers.IP] | (memory[++registers.IP] << 8);
				break;
			case ADD_8REG_REG: {
				uint8_t modrm = memory[registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("add %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] += *pregs8[reg2];
				break;
			}
			case ADD_16REG_REG: {
				uint8_t modrm = memory[registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("add %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] += *pregs16[reg2];
				break;
			}
			case SUB_8REG_REG: {
				uint8_t modrm = memory[registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("sub %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] -= *pregs8[reg2];
				break;
			}
			case SUB_16REG_REG: {
				uint8_t modrm = memory[registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("sub %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] -= *pregs16[reg2];
				break;
			}
			case ADD_AL_VALUE:
				if (DEBUG) {
					printf("add al, %X", memory[++registers.IP]);
				}
				registers.AX.low += memory[registers.IP];
				break;
			case ADD_8REG_VALUE:
				registers.IP++;

				switch (memory[registers.IP++]) {
					case ADD_BL:
						if (DEBUG) {
							printf("add bl, %X", memory[registers.IP]);
						}
						registers.BX.low += memory[registers.IP];
						break;
					case ADD_CL:
						if (DEBUG) {
							printf("add cl, %X", memory[registers.IP]);
						}
						registers.CX.low += memory[registers.IP];
						break;
					case ADD_DL:
						if (DEBUG) {
							printf("add dl, %X", memory[registers.IP]);
						}
						registers.DX.low += memory[registers.IP];
						break;
					case ADD_AH:
						if (DEBUG) {
							printf("add ah, %X", memory[registers.IP]);
						}
						registers.AX.high += memory[registers.IP];
					case ADD_BH:
						if (DEBUG) {
							printf("add bh, %X", memory[registers.IP]);
						}
						registers.BX.high += memory[registers.IP];
					case ADD_CH:
						if (DEBUG) {
							printf("add ch, %X", memory[registers.IP]);
						}
						registers.CX.high += memory[registers.IP];
					case ADD_DH:
						if (DEBUG) {
							printf("add dh, %X", memory[registers.IP]);
						}
						registers.DX.high += memory[registers.IP];
				}
				break;
			case INC_AX:
				registers.AX.base++;
				break;
			case INC_BX:
				registers.BX.base++;
				break;
			case INC_CX:
				registers.CX.base++;
				break;
			case INC_DX:
				registers.DX.base++;
				break;
			case DEC_AX:
				registers.AX.base--;
				break;
			case DEC_BX:
				registers.BX.base--;
				break;
			case DEC_CX:
				registers.CX.base--;
				break;
			case DEC_DX:
				registers.DX.base--;
				break;
			case INC_DEC:
				if (DEBUG) {
					printf("inc/dec");
				}

				switch(memory[++registers.IP]) {
					case INC_AL:
						registers.AX.low++;
						break;
					case INC_BL:
						registers.BX.low++;
						break;
					case INC_CL:
						registers.CX.low++;
						break;
					case INC_DL:
						registers.DX.low++;
						break;
					case INC_AH:
						registers.AX.high++;
						break;
					case INC_BH:
						registers.BX.high++;
						break;
					case INC_CH:
						registers.CX.high++;
						break;
					case INC_DH:
						registers.DX.high++;
						break;
					case DEC_AL:
						registers.AX.low--;
						break;
					case DEC_BL:
						registers.BX.low--;
						break;
					case DEC_CL:
						registers.CX.low--;
						break;
					case DEC_DL:
						registers.DX.low--;
						break;
					case DEC_AH:
						registers.AX.high--;
						break;
					case DEC_BH:
						registers.BX.high--;
						break;
					case DEC_CH:
						registers.CX.high--;
						break;
					case DEC_DH:
						registers.DX.high--;
						break;
				}
				break;
			case AND_8REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("and %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] &= *pregs8[reg2];
				break;
			}
			case AND_16REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("and %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] &= *pregs16[reg2];
				break;
			}
			case OR_8REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("or %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] |= *pregs8[reg2];
				break;
			}
			case OR_16REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("or %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] |= *pregs16[reg2];
				break;
			}
			case NOT_8REG: {
				switch (memory[++registers.IP]) {
					case NOT_AL:
						if (DEBUG) {
							printf("not al");
						}
						registers.AX.low = ~registers.AX.low;
						break;
					case NOT_BL:
						if (DEBUG) {
							printf("not bl");
						}
						registers.BX.low = ~registers.BX.low;
						break;
					case NOT_CL:
						if (DEBUG) {
							printf("not cl");
						}
						registers.CX.low = ~registers.CX.low;
						break;
					case NOT_DL:
						if (DEBUG) {
							printf("not dl");
						}
						registers.DX.low = ~registers.DX.low;
						break;
					case NOT_AH:
						if (DEBUG) {
							printf("not ah");
						}
						registers.AX.high = ~registers.AX.high;
						break;
					case NOT_BH:
						if (DEBUG) {
							printf("not bh");
						}
						registers.BX.high = ~registers.BX.high;
						break;
					case NOT_CH:
						if (DEBUG) {
							printf("not ch");
						}
						registers.CX.high = ~registers.CX.high;
						break;
					case NOT_DH:
						if (DEBUG) {
							printf("not dh");
						}
						registers.DX.high = ~registers.DX.high;
						break;
				}
				break;
			}
			case NOT_16REG:
				switch (memory[++registers.IP]) {
					case NOT_AX:
						if (DEBUG) {
							printf("not ax");
						}
						registers.AX.base = ~registers.AX.base;
						break;
					case NOT_BX:
						if (DEBUG) {
							printf("not bx");
						}
						registers.BX.base = ~registers.BX.base;
						break;
					case NOT_CX:
						if (DEBUG) {
							printf("not cx");
						}
						registers.CX.base = ~registers.CX.base;
						break;
					case NOT_DX:
						if (DEBUG) {
							printf("not dx");
						}
						registers.DX.base = ~registers.DX.base;
						break;
				}
				break;
			case XOR_8REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("xor %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] ^= *pregs8[reg2];
				break;
			}
			case XOR_16REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("xor %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] ^= *pregs16[reg2];
				break;
			}
			case NOP:
				if (DEBUG) {
					printf("nop");
				}
				break;
			case HLT_INS:
				if (DEBUG) {
					printf("hlt");
				}

				HLT = false;
				break;
			default:
				if (DEBUG) {
					printf("Unknown opcode!");
				}
				break;
		}

		if (REGISTERS_VIEW) {
			printf("\tAX = %04X\tBX = %04X\tCX = %04X\tDX = %04X", registers.AX.base, registers.BX.base, registers.CX.base, registers.DX.base);
		}

		printf("\n");

		registers.IP++;
	}

	if (DEBUG) {
		printf("CPU halted\n");
	}

	if (MEMORY_DUMP) {
		memory_dump("memory.dump", memory);
	}

	free(memory);

	return 0;
}
