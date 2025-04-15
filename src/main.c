#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include <cpu.h>
#include <utils.h>

#define VERSION			"0.1.5"

/*
--------------------------------------------------
VM i8086
Virtual Machine based on Intel 8086 processor

Author: Truzme_
License: MIT

CHANGELOG:
v0.1.3
- Added AND opcode
- Code refactoring

v0.1.4
- Added OR, NOT, XOR opcodes

v0.1.5
- Fixed bug in ADD, SUB AND and OR
- Code refactoring
--------------------------------------------------
*/

bool DEBUG = false;
Registers registers = {0};
uint8_t *mem;

uint8_t *regs8[8] = {
	&registers.ax.low, &registers.cx.low, &registers.dx.low, &registers.bx.low,
	&registers.ax.high, &registers.cx.high, &registers.dx.high, &registers.bx.high
};

uint16_t *regs16[4] = {
	&registers.ax.base, &registers.cx.base, &registers.dx.base, &registers.bx.base
};

char *reg8_names[8] = {
	"al", "cl", "dl", "bl",
	"ah", "ch", "dh", "bh"
};

char *reg16_names[4] = {
	"ax", "cx", "dx", "bx"
};

void mov_imm8(uint8_t opcode) {
	uint8_t index = opcode - 0xB0;	// 0xB0 - AL

	registers.ip++;

	if (DEBUG) {
		printf("%02X ", mem[registers.ip]);
	}

	if (DEBUG) {
		printf("mov %s, %X", reg8_names[index], mem[registers.ip]);
	}

	*regs8[index] = mem[registers.ip];
}

void mov_imm16(uint8_t opcode) {
	uint8_t index = opcode - AX_REG;

	registers.ip++;

	if (DEBUG) {
		printf("%02X ", mem[registers.ip]);
	}

	if (DEBUG) {
		printf("mov %s, %X", reg16_names[index], mem[registers.ip] | (mem[registers.ip + 1] << 8));
	}

	*regs16[index] = mem[registers.ip] | (mem[++registers.ip] << 8);
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s <file> [options]\n\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("Usage: %s <file> [options]\n\n", argv[0]);
		printf("Options:\n");
		printf("-d - debug mode\n");
		printf("-vR - view registers values\n");
		printf("-rd - create registers dump\n");
		printf("-md - create memory dump\n");
		return 0;
	} else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
		printf("VM version: %s\n", VERSION);
		return 0;
	}

	bool REGISTERS_VIEW = false;
	bool MEMORY_DUMP = false;
	bool REGISTERS_DUMP = false;

	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
				DEBUG = true;
			} else if (strcmp(argv[i], "-vr") == 0 || strcmp(argv[i], "--view-registers") == 0) {
				REGISTERS_VIEW = true;
			} else if (strcmp(argv[i], "-rd") == 0 || strcmp(argv[i], "--registers-dump") == 0) {
				REGISTERS_DUMP = true;
			} else if (strcmp(argv[i], "-md") == 0 || strcmp(argv[i], "--memory-dump") == 0) {
				MEMORY_DUMP = true;
			}
		}
	}

	mem = malloc(MEMORY_SIZE);

	FILE *fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	size_t file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	read(mem, fp, file_length);

	fclose(fp);

	bool running = true;

	while (running) {
		if (DEBUG) {
			printf("0x%05X ", registers.ip);
		}

		if (DEBUG) {
			printf("%02X ", mem[registers.ip]);
		}

		switch (mem[registers.ip]) {
			case MOV_8REG_REG: {
				if (DEBUG) {
					printf("%02X ", mem[registers.ip]);
				}

				registers.ip++;

				uint8_t modrm = mem[registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("mov %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*regs8[reg1] = *regs8[reg2];
				break;
			}
			case MOV_16REG_REG: {
				if (DEBUG) {
					printf("%02X ", mem[registers.ip]);
				}

				registers.ip++;

				uint8_t modrm = mem[registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("mov %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*regs16[reg1] = *regs16[reg2];
				break;
			}
			case AL_REG:
			case BL_REG:
			case CL_REG:
			case DL_REG:
			case AH_REG:
			case BH_REG:
			case CH_REG:
			case DH_REG:
				mov_imm8(mem[registers.ip]);
				break;
			case AX_REG:
			case BX_REG:
			case CX_REG:
			case DX_REG:
				mov_imm16(mem[registers.ip]);
				break;
			case ADD_8REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("add %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*regs8[reg1] += *regs8[reg2];
				break;
			}
			case ADD_16REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("add %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*regs16[reg1] += *regs16[reg2];
				break;
			}
			case SUB_8REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("sub %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*regs8[reg1] -= *regs8[reg2];
				break;
			}
			case SUB_16REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("sub %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*regs16[reg1] -= *regs16[reg2];
				break;
			}
			case ADD_AL_VALUE:
				registers.ip++;

				if (DEBUG) {
					printf("add al, %X", mem[registers.ip]);
				}

				registers.ax.low += mem[registers.ip];
				break;
			case ADD_AX_VALUE:
				uint16_t value = mem[++registers.ip] | (mem[++registers.ip] << 8);

				if (DEBUG) {
					printf("add ax, %X", value);
				}

				registers.ax.base += value;
				break;
			case 0x80: {
				if ((mem[++registers.ip] - 0xC0) <= 7) {
					uint8_t index = mem[registers.ip] - 0xC0; // 0xC0 - AL (8 bits)
					registers.ip++;

					if (DEBUG) {
						printf("add %s, %X", reg8_names[index], mem[registers.ip]);
					}

					*regs8[index] += mem[registers.ip];
				} else {
					if ((mem[registers.ip] - 0xC8) <= 7) {
						uint8_t index = mem[registers.ip] - 0xC8;
						registers.ip++;

						if (DEBUG) {
							printf("and %s, %X", reg8_names[index], mem[registers.ip]);
						}

						*regs8[index] |= mem[registers.ip];
					} else {
						if ((mem[registers.ip] - 0xE0) <= 7) {
							uint8_t index = mem[registers.ip++] - 0xE0;

							if (DEBUG) {
								printf("and %s, %X", reg8_names[index], mem[registers.ip]);
							}

							*regs8[index] &= mem[registers.ip];
						} else {
							uint8_t index = mem[registers.ip++] - 0xE8;

							if (DEBUG) {
								printf("sub %s, %X", reg8_names[index], mem[registers.ip]);
							}

							*regs8[index] -= mem[registers.ip];
						}
					}
				}
				break;
			}
			case 0x83: {
				if ((mem[++registers.ip] - 0xC0) <= 7) {
					uint8_t index = mem[registers.ip] - 0xC0; // 0xC0 - AX (16 bits)
					uint16_t value = mem[++registers.ip] | (0xFF << 8); // 0xE0 - AX only if value => 0xFF80 (16 bits)

					if (DEBUG) {
						printf("add %s, %X", reg16_names[index], value);
					}

					*regs16[index] += value;
				} else {
					// OR AX, R/M => 0xFF80
					if ((mem[registers.ip] - 0xC8) <= 7) {
						uint8_t index = mem[registers.ip] - 0xC8; // 0xC8 - AX (16 bits)
						uint16_t value = mem[++registers.ip] | (0xFF << 8);

						if (DEBUG) {
							printf("or %s, %X", reg16_names[index], value);
						}

						*regs16[index] |= value;
					} else {
						// AND AX, R/M => 0xFF80
						uint8_t index = mem[registers.ip] - 0xE0;
						uint16_t value = mem[++registers.ip] | (0xFF << 8);

						if (DEBUG) {
							printf("and %s, %X", reg16_names[index], value);
						}

						*regs16[index] &= value;
					}
				}
				break;
			}
			case SUB_AL_VALUE: {
				uint16_t value = mem[++registers.ip];

				if (DEBUG) {
					printf("sub al, %X", value);
				}

				registers.ax.low -= value;
				break;
			}
			case SUB_AX_VALUE: {
				uint16_t value = mem[++registers.ip] | (mem[++registers.ip] << 8);

				if (DEBUG) {
					printf("sub ax, %X", value);
				}

				registers.ax.base -= value;
				break;
			}
			case INC_AX:
				if (DEBUG) {
					printf("inc ax");
				}
				registers.ax.base++;
				break;
			case INC_BX:
				if (DEBUG) {
					printf("inc bx");
				}
				registers.bx.base++;
				break;
			case INC_CX:
				if (DEBUG) {
					printf("inc cx");
				}
				registers.cx.base++;
				break;
			case INC_DX:
				if (DEBUG) {
					printf("inc dx");
				}
				registers.dx.base++;
				break;
			case DEC_AX:
				if (DEBUG) {
					printf("dec ax");
				}
				registers.ax.base--;
				break;
			case DEC_BX:
				if (DEBUG) {
					printf("dec bx");
				}
				registers.bx.base--;
				break;
			case DEC_CX:
				if (DEBUG) {
					printf("dec cx");
				}
				registers.cx.base--;
				break;
			case DEC_DX:
				if (DEBUG) {
					printf("dec dx");
				}
				registers.dx.base--;
				break;
			case INC_DEC_R8: {
				if (mem[++registers.ip] - 0xC0 <= 7) {
					uint8_t index = mem[registers.ip] - 0xC0;

					if (DEBUG) {
						printf("inc %s", reg8_names[index]);
					}

					(*regs8[index])++;
				} else {
					uint8_t index = mem[registers.ip] - 0xC8;

					if (DEBUG) {
						printf("dec %s", reg8_names[index]);
					}

					(*regs8[index])--;
				}
				break;
			}
			case AND_8REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("and %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*regs8[reg1] &= *regs8[reg2];
				break;
			}
			case AND_16REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("and %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*regs16[reg1] &= *regs16[reg2];
				break;
			}
			case AND_AL_VALUE:
				registers.ip++;
				if (DEBUG) {
					printf("and al, %X", mem[registers.ip]);
				}
				registers.ax.low &= mem[registers.ip];
				break;
			case AND_AX_VALUE: {
				uint16_t value = mem[++registers.ip] | (mem[++registers.ip] << 8);

				if (DEBUG) {
					printf("and ax, %X", value);
				}

				*regs16[0] &= value;
				break;
			}
			case AND_16REG_VALUE: {
				if ((mem[++registers.ip] - 0xC0) <= 7) {
					uint8_t index = mem[registers.ip] - 0xC0; // 0xC0 - AX (16 bits)
					uint16_t value = mem[++registers.ip] | (mem[++registers.ip] << 8);

					if (DEBUG) {
						printf("or %s, %X", reg16_names[index], value);
					}

					*regs16[index] |= value;
				} else {
					if ((mem[registers.ip] - 0xE0) <= 7) {
						uint8_t index = mem[registers.ip] - 0xE0;
						uint16_t value = mem[++registers.ip] | (mem[++registers.ip] << 8);

						if (DEBUG) {
							printf("and %s, %X", reg16_names[index], value);
						}

						*regs16[index] &= value;
					} else {
						uint8_t index = mem[registers.ip] - 0xE8;
						uint16_t value = mem[++registers.ip] | (mem[++registers.ip] << 8);

						if (DEBUG) {
							printf("sub %s, %X", reg16_names[index], value);
						}

						*regs16[index] -= value;
					}
				}
				break;
			}
			case OR_8REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("or %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*regs8[reg1] |= *regs8[reg2];
				break;
			}
			case OR_16REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("or %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*regs16[reg1] |= *regs16[reg2];
				break;
			}
			case OR_AL_VALUE: {
				registers.ip++;

				if (DEBUG) {
					printf("or ax, %X", mem[registers.ip]);
				}

				*regs8[0] |= mem[registers.ip];
				break;
			}
			case OR_AX_VALUE: {
				uint16_t value = mem[++registers.ip] | (mem[++registers.ip] << 8);

				if (DEBUG) {
					printf("or ax, %X", value);
				}

				*regs16[0] |= value;
				break;
			}
			case NOT_8REG: {
				switch (mem[++registers.ip]) {
					case NOT_AL:
						if (DEBUG) {
							printf("not al");
						}
						registers.ax.low = ~registers.ax.low;
						break;
					case NOT_BL:
						if (DEBUG) {
							printf("not bl");
						}
						registers.bx.low = ~registers.bx.low;
						break;
					case NOT_CL:
						if (DEBUG) {
							printf("not cl");
						}
						registers.cx.low = ~registers.cx.low;
						break;
					case NOT_DL:
						if (DEBUG) {
							printf("not dl");
						}
						registers.dx.low = ~registers.dx.low;
						break;
					case NOT_AH:
						if (DEBUG) {
							printf("not ah");
						}
						registers.ax.high = ~registers.ax.high;
						break;
					case NOT_BH:
						if (DEBUG) {
							printf("not bh");
						}
						registers.bx.high = ~registers.bx.high;
						break;
					case NOT_CH:
						if (DEBUG) {
							printf("not ch");
						}
						registers.cx.high = ~registers.cx.high;
						break;
					case NOT_DH:
						if (DEBUG) {
							printf("not dh");
						}
						registers.dx.high = ~registers.dx.high;
						break;
				}
				break;
			}
			case NOT_16REG:
				switch (mem[++registers.ip]) {
					case NOT_AX:
						if (DEBUG) {
							printf("not ax");
						}
						registers.ax.base = ~registers.ax.base;
						break;
					case NOT_BX:
						if (DEBUG) {
							printf("not bx");
						}
						registers.bx.base = ~registers.bx.base;
						break;
					case NOT_CX:
						if (DEBUG) {
							printf("not cx");
						}
						registers.cx.base = ~registers.cx.base;
						break;
					case NOT_DX:
						if (DEBUG) {
							printf("not dx");
						}
						registers.dx.base = ~registers.dx.base;
						break;
				}
				break;
			case XOR_8REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("xor %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*regs8[reg1] ^= *regs8[reg2];
				break;
			}
			case XOR_16REG_REG: {
				uint8_t modrm = mem[++registers.ip];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("xor %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*regs16[reg1] ^= *regs16[reg2];
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

				running = false;
				break;
			default:
				if (DEBUG) {
					printf("Unknown opcode!");
				}
				break;
		}

		if (REGISTERS_VIEW) {
			printf("\tAX = %04X\tBX = %04X\tCX = %04X\tDX = %04X", registers.ax.base, registers.bx.base, registers.cx.base, registers.dx.base);
		}

		if (DEBUG) {
			printf("\n");
		}

		registers.ip++;
	}

	if (DEBUG) {
		printf("CPU halted\n");
	}

	if (REGISTERS_DUMP) {
		registers_dump("registers.dump", &registers);
	}

	if (MEMORY_DUMP) {
		memory_dump("memory.dump", mem);
	}

	free(mem);

	return 0;
}
