#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include <i8086.h>

#define VERSION			"0.1.5"
#define BUFFER_SIZE		1024
#define MEMORY_SIZE 	1048576

/*

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

*/

bool DEBUG = false;
Registers registers = {0};
uint8_t *memory;

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

void read(uint8_t *memory, FILE *fp, size_t file_length) {
	uint8_t buffer[BUFFER_SIZE];
	uint8_t *memory_ptr = memory;
	int bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
		memcpy(memory_ptr, buffer, bytes_read);
		memory_ptr += bytes_read;
	}
}

void registers_dump(const char* filename) {
	FILE* fp = fopen(filename, "w");

	if (fp == NULL) {
		printf("Erorr opening file %s\n", filename);
		exit(1);
	}

	fprintf(fp, "AL:0x%X\nBL:0x%X\nCL:0x%X\nDL:0x%X\n", registers.AX.low, registers.BX.low, registers.CX.low, registers.DX.low);
	fprintf(fp, "AH:0x%X\nBH:0x%X\nCH:0x%X\nDH:0x%X\n", registers.AX.high, registers.BX.high, registers.CX.high, registers.DX.high);
	fprintf(fp, "AX:0x%X\nBX:0x%X\nCX:0x%X\nDX:0x%X\n", registers.AX.base, registers.BX.base, registers.CX.base, registers.DX.base);

	fclose(fp);
}

void memory_dump(const char *filename) {
	FILE *fp = fopen(filename, "wb");

	if (fp == NULL) {
		printf("Error opening file %s\n", filename);
		exit(1);
	}

	fwrite(memory, 1, MEMORY_SIZE, fp);

	fclose(fp);

	printf("Memory dumped!\n");
}

void mov8(uint8_t opcode) {
	uint8_t index = opcode - AL_REG;

	registers.IP++;

	if (DEBUG) {
		printf("%02X ", memory[registers.IP]);
	}

	if (DEBUG) {
		printf("mov %s, %X", reg8_names[index], memory[registers.IP]);
	}

	*pregs8[index] = memory[registers.IP];
}

void mov16(uint8_t opcode) {
	uint8_t index = opcode - AX_REG;

	registers.IP++;

	if (DEBUG) {
		printf("%02X ", memory[registers.IP]);
	}

	if (DEBUG) {
		printf("mov %s, %X", reg16_names[index], memory[registers.IP] | (memory[registers.IP + 1] << 8));
	}

	*pregs16[index] = memory[registers.IP] | (memory[++registers.IP] << 8);
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

	memory = malloc(MEMORY_SIZE);

	FILE *fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	size_t file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	read(memory, fp, file_length);

	fclose(fp);

	bool running = true;

	while (running) {
		if (DEBUG) {
			printf("0x%05X ", registers.IP);
		}

		if (DEBUG) {
			printf("%02X ", memory[registers.IP]);
		}

		switch (memory[registers.IP]) {
			case MOV_8REG_REG: {
				if (DEBUG) {
					printf("%02X ", memory[registers.IP]);
				}

				registers.IP++;

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
					printf("%02X ", memory[registers.IP]);
				}

				registers.IP++;

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
			case BL_REG:
			case CL_REG:
			case DL_REG:
			case AH_REG:
			case BH_REG:
			case CH_REG:
			case DH_REG:
				mov8(memory[registers.IP]);
				break;
			case AX_REG:
			case BX_REG:
			case CX_REG:
			case DX_REG:
				mov16(memory[registers.IP]);
				break;
			case ADD_8REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("add %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] += *pregs8[reg2];
				break;
			}
			case ADD_16REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("add %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] += *pregs16[reg2];
				break;
			}
			case SUB_8REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("sub %s, %s", reg8_names[reg1], reg8_names[reg2]);
				}

				*pregs8[reg1] -= *pregs8[reg2];
				break;
			}
			case SUB_16REG_REG: {
				uint8_t modrm = memory[++registers.IP];
				uint8_t reg1 = modrm & 0b111;
				uint8_t reg2 = (modrm >> 3) & 0b111;

				if (DEBUG) {
					printf("sub %s, %s", reg16_names[reg1], reg16_names[reg2]);
				}

				*pregs16[reg1] -= *pregs16[reg2];
				break;
			}
			case ADD_AL_VALUE:
				registers.IP++;

				if (DEBUG) {
					printf("add al, %X", memory[registers.IP]);
				}

				registers.AX.low += memory[registers.IP];
				break;
			case ADD_AX_VALUE:
				uint16_t value = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("add ax, %X", value);
				}

				registers.AX.base += value;
				break;
			case ADD_8REG_VALUE: {
				if ((memory[++registers.IP] - 0xC0) <= 7) {
					uint8_t index = memory[registers.IP] - 0xC0; // 0xC0 - AL (8 bits)
					registers.IP++;

					if (DEBUG) {
						printf("add %s, %X", reg8_names[index], memory[registers.IP]);
					}

					*pregs8[index] += memory[registers.IP];
				} else {
					if ((memory[registers.IP] - 0xC8) <= 7) {
						uint8_t index = memory[registers.IP] - 0xC8;
						registers.IP++;

						if (DEBUG) {
							printf("and %s, %X", reg8_names[index], memory[registers.IP]);
						}

						*pregs8[index] |= memory[registers.IP];
					} else {
						if ((memory[registers.IP] - 0xE0) <= 7) {
							uint8_t index = memory[registers.IP++] - 0xE0;

							if (DEBUG) {
								printf("and %s, %X", reg8_names[index], memory[registers.IP]);
							}

							*pregs8[index] &= memory[registers.IP];
						} else {
							uint8_t index = memory[registers.IP++] - 0xE8;

							if (DEBUG) {
								printf("sub %s, %X", reg8_names[index], memory[registers.IP]);
							}

							*pregs8[index] -= memory[registers.IP];
						}
					}
				}
				break;
			}
			case ADD_16REG_VALUE: {
				if ((memory[++registers.IP] - 0xC0) <= 7) {
					uint8_t index = memory[registers.IP] - 0xC0; // 0xC0 - AX (16 bits)
					uint16_t value = memory[++registers.IP] | (0xFF << 8); // 0xE0 - AX only if value => 0xFF80 (16 bits)

					if (DEBUG) {
						printf("add %s, %X", reg16_names[index], value);
					}

					*pregs16[index] += value;
				} else {
					// OR AX, R/M => 0xFF80
					if ((memory[registers.IP] - 0xC8) <= 7) {
						uint8_t index = memory[registers.IP] - 0xC8; // 0xC8 - AX (16 bits)
						uint16_t value = memory[++registers.IP] | (0xFF << 8);

						if (DEBUG) {
							printf("or %s, %X", reg16_names[index], value);
						}

						*pregs16[index] |= value;
					} else {
						// AND AX, R/M => 0xFF80
						uint8_t index = memory[registers.IP] - 0xE0;
						uint16_t value = memory[++registers.IP] | (0xFF << 8);

						if (DEBUG) {
							printf("and %s, %X", reg16_names[index], value);
						}

						*pregs16[index] &= value;
					}
				}
				break;
			}
			case SUB_AL_VALUE: {
				uint16_t value = memory[++registers.IP];

				if (DEBUG) {
					printf("sub al, %X", value);
				}

				registers.AX.low -= value;
				break;
			}
			case SUB_AX_VALUE: {
				uint16_t value = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("sub ax, %X", value);
				}

				registers.AX.base -= value;
				break;
			}
			case INC_AX:
				if (DEBUG) {
					printf("inc ax");
				}
				registers.AX.base++;
				break;
			case INC_BX:
				if (DEBUG) {
					printf("inc bx");
				}
				registers.BX.base++;
				break;
			case INC_CX:
				if (DEBUG) {
					printf("inc cx");
				}
				registers.CX.base++;
				break;
			case INC_DX:
				if (DEBUG) {
					printf("inc dx");
				}
				registers.DX.base++;
				break;
			case DEC_AX:
				if (DEBUG) {
					printf("dec ax");
				}
				registers.AX.base--;
				break;
			case DEC_BX:
				if (DEBUG) {
					printf("dec bx");
				}
				registers.BX.base--;
				break;
			case DEC_CX:
				if (DEBUG) {
					printf("dec cx");
				}
				registers.CX.base--;
				break;
			case DEC_DX:
				if (DEBUG) {
					printf("dec dx");
				}
				registers.DX.base--;
				break;
			case INC_DEC_R8: {
				if (memory[++registers.IP] - 0xC0 <= 7) {
					uint8_t index = memory[registers.IP] - 0xC0;

					if (DEBUG) {
						printf("inc %s", reg8_names[index]);
					}

					(*pregs8[index])++;
				} else {
					uint8_t index = memory[registers.IP] - 0xC8;

					if (DEBUG) {
						printf("dec %s", reg8_names[index]);
					}

					(*pregs8[index])--;
				}
				break;
			}
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
			case AND_AL_VALUE:
				registers.IP++;
				if (DEBUG) {
					printf("and al, %X", memory[registers.IP]);
				}
				registers.AX.low &= memory[registers.IP];
				break;
			case AND_AX_VALUE: {
				uint16_t value = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("and ax, %X", value);
				}

				*pregs16[0] &= value;
				break;
			}
			case AND_16REG_VALUE: {
				if ((memory[++registers.IP] - 0xC0) <= 7) {
					uint8_t index = memory[registers.IP] - 0xC0; // 0xC0 - AX (16 bits)
					uint16_t value = memory[++registers.IP] | (memory[++registers.IP] << 8);

					if (DEBUG) {
						printf("or %s, %X", reg16_names[index], value);
					}

					*pregs16[index] |= value;
				} else {
					if ((memory[registers.IP] - 0xE0) <= 7) {
						uint8_t index = memory[registers.IP] - 0xE0;
						uint16_t value = memory[++registers.IP] | (memory[++registers.IP] << 8);

						if (DEBUG) {
							printf("and %s, %X", reg16_names[index], value);
						}

						*pregs16[index] &= value;
					} else {
						uint8_t index = memory[registers.IP] - 0xE8;
						uint16_t value = memory[++registers.IP] | (memory[++registers.IP] << 8);

						if (DEBUG) {
							printf("sub %s, %X", reg16_names[index], value);
						}

						*pregs16[index] -= value;
					}
				}
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
			case OR_AL_VALUE: {
				registers.IP++;

				if (DEBUG) {
					printf("or ax, %X", memory[registers.IP]);
				}

				*pregs8[0] |= memory[registers.IP];
				break;
			}
			case OR_AX_VALUE: {
				uint16_t value = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("or ax, %X", value);
				}

				*pregs16[0] |= value;
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

				running = false;
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

		if (DEBUG) {
			printf("\n");
		}

		registers.IP++;
	}

	if (DEBUG) {
		printf("CPU halted\n");
	}

	if (REGISTERS_DUMP) {
		registers_dump("registers.dump");
	}

	if (MEMORY_DUMP) {
		memory_dump("memory.dump");
	}

	free(memory);

	return 0;
}
