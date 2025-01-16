#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include "i8086.h"

#define VERSION			"0.1"
#define BUFFER_SIZE		1024
#define MEMORY_SIZE 	1048576

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

	if (argc < 2) {
		printf("Usage: %s [file]\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
		printf("VM v%s\n", VERSION);
		return 0;
	}

	bool DEBUG = false;
	bool REGISTERS_VIEW = false;
	bool MEMORY_DUMP = false;

	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
				DEBUG = true;
			} else if (strcmp(argv[i], "-rv") == 0 || strcmp(argv[i], "--registers-view") == 0) {
				REGISTERS_VIEW = true;
			} else if (strcmp(argv[i], "-md") == 0 || strcmp(argv[i], "--memory-dump") == 0) {
				MEMORY_DUMP = true;
			}
		}
	}

	uint8_t *memory = malloc(MEMORY_SIZE);

	FILE *fp = fopen(argv[1], "rb");

	if (fp == NULL) {
		printf("Error opening file!\n");
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
			printf("%05d ", registers.IP);
		}

		if (DEBUG) {
			printf("%02X ", memory[registers.IP]);
		}

		switch (memory[registers.IP]) {
			case MOV_REG_REG:
				registers.IP++;

				if (DEBUG) {
					printf("%02X ", memory[registers.IP]);
				}
				
				switch (memory[registers.IP]) {
					case MOV_AX_AX:
						if (DEBUG) {
							printf("mov ax, ax");
						}

						registers.AX = registers.AX;
						break;
					case MOV_AX_BX:
						if (DEBUG) {
							printf("mov ax, bx");
						}

						registers.AX = registers.BX;						
						break;
					case MOV_AX_CX:
						if (DEBUG) {
							printf("mov ax, cx");
						}

						registers.AX = registers.CX;
						break;
					case MOV_AX_DX:
						if (DEBUG) {
							printf("mov ax, dx");
						}

						registers.AX = registers.DX;
						break;
					case MOV_BX_AX:
						if (DEBUG) {
							printf("mov bx, ax");
						}

						registers.BX = registers.AX;
						break;
					case MOV_BX_BX:
						if (DEBUG) {
							printf("mov bx, bx");
						}

						registers.BX = registers.BX;
						break;
					case MOV_BX_CX:
						if (DEBUG) {
							printf("mov bx, cx");
						}

						registers.BX = registers.CX;
						break;
					case MOV_BX_DX:
						if (DEBUG) {
							printf("mov bx, dx");
						}

						registers.BX = registers.DX;
						break;
					case MOV_CX_AX:
						if (DEBUG) {
							printf("mov cx, ax");
						}

						registers.CX = registers.AX;
						break;
					case MOV_CX_BX:
						if (DEBUG) {
							printf("mov cx, bx");
						}

						registers.CX = registers.BX;
						break;
					case MOV_CX_CX:
						if (DEBUG) {
							printf("mov cx, cx");
						}

						registers.CX = registers.CX;
						break;
					case MOV_CX_DX:
						if (DEBUG) {
							printf("mov cx, dx");
						}

						registers.CX = registers.DX;
						break;
					case MOV_DX_AX:
						if (DEBUG) {
							printf("mov dx, ax");
						}

						registers.DX = registers.AX;
						break;
					case MOV_DX_BX:
						if (DEBUG) {
							printf("mov dx, bx");
						}

						registers.DX = registers.BX;
						break;
					case MOV_DX_CX:
						if (DEBUG) {
							printf("mov dx, cx");
						}

						registers.DX = registers.CX;
						
						break;
					case MOV_DX_DX:
						if (DEBUG) {
							printf("mov dx, dx");
						}

						registers.DX = registers.DX;
						break;
					default:
						if (DEBUG) {
							printf("Unknwon instruction!");
						}
						break;
				}
				break;
			case AX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				registers.AX = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov ax, %X", registers.AX);
				}
				break;
			case BX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				registers.BX = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov bx, %X", registers.BX);
				}
				break;
			case CX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				registers.CX = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov cx, %X", registers.CX);
				}
				break;
			case DX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				registers.DX = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov dx, %X", registers.DX);
				}
				break;
			case ADD_REG_REG:
				registers.IP++;

				switch (memory[registers.IP]) {
					case ADD_AX_AX:
						registers.AX += registers.AX;

						if (DEBUG) {
							printf("add ax, ax");
						}
						break;
					case ADD_AX_BX:
						registers.AX += registers.BX;
						
						if (DEBUG) {
							printf("add ax, bx");
						}
						break;
					case ADD_AX_CX:
						registers.AX += registers.CX;
						
						if (DEBUG) {
							printf("add ax, cx");
						}
						break;
					case ADD_AX_DX:
						registers.AX += registers.DX;
						
						if (DEBUG) {
							printf("add ax, dx");
						}
						break;
					case ADD_BX_AX:
						registers.BX += registers.AX;

						if (DEBUG) {
							printf("add bx, ax");
						}
						break;
					case ADD_BX_BX:
						registers.BX += registers.BX;
						
						if (DEBUG) {
							printf("add bx, bx");
						}
						break;
					case ADD_BX_CX:
						registers.BX += registers.CX;
						
						if (DEBUG) {
							printf("add bx cx");
						}
						break;
					case ADD_BX_DX:
						registers.BX += registers.DX;
						
						if (DEBUG) {
							printf("add bx, dx");
						}
						break;
					case ADD_CX_AX:
						registers.CX += registers.AX;

						if (DEBUG) {
							printf("add cx, ax");
						}
						break;
					case ADD_CX_BX:
						registers.CX += registers.BX;
						
						if (DEBUG) {
							printf("add cx, bx");
						}
						break;
					case ADD_CX_CX:
						registers.CX += registers.CX;
						
						if (DEBUG) {
							printf("add cx, cx");
						}
						break;
					case ADD_CX_DX:
						registers.CX += registers.DX;
						
						if (DEBUG) {
							printf("add cx, dx");
						}
						break;
					case ADD_DX_AX:
						registers.DX += registers.AX;

						if (DEBUG) {
							printf("add dx, ax");
						}
						break;
					case ADD_DX_BX:
						registers.DX += registers.BX;
						
						if (DEBUG) {
							printf("add dx, bx");
						}
						break;
					case ADD_DX_CX:
						registers.DX += registers.CX;
						
						if (DEBUG) {
							printf("add dx, cx");
						}
						break;
					case ADD_DX_DX:
						registers.DX += registers.DX;
						
						if (DEBUG) {
							printf("add dx, dx");
						}
						break;
					default:
						if (DEBUG) {
							printf("Unknwon instruction!");
						}
						break;
				}
				break;
			case SUB_REG_REG:
				registers.IP++;

				switch (memory[registers.IP]) {
					case ADD_AX_AX:
						registers.AX -= registers.AX;

						if (DEBUG) {
							printf("sub ax, ax");
						}
						break;
					case ADD_AX_BX:
						registers.AX -= registers.BX;
						
						if (DEBUG) {
							printf("sub ax, bx");
						}
						break;
					case ADD_AX_CX:
						registers.AX -= registers.CX;
						
						if (DEBUG) {
							printf("sub ax, cx");
						}
						break;
					case ADD_AX_DX:
						registers.AX -= registers.DX;
						
						if (DEBUG) {
							printf("sub ax, dx");
						}
						break;
					case ADD_BX_AX:
						registers.BX -= registers.AX;

						if (DEBUG) {
							printf("sub bx, ax");
						}
						break;
					case ADD_BX_BX:
						registers.BX -= registers.BX;
						
						if (DEBUG) {
							printf("sub bx, bx");
						}
						break;
					case ADD_BX_CX:
						registers.BX -= registers.CX;
						
						if (DEBUG) {
							printf("sub abx cx");
						}
						break;
					case ADD_BX_DX:
						registers.BX -= registers.DX;
						
						if (DEBUG) {
							printf("sub bx, dx");
						}
						break;
					case ADD_CX_AX:
						registers.CX -= registers.AX;

						if (DEBUG) {
							printf("sub cx, ax");
						}
						break;
					case ADD_CX_BX:
						registers.CX -= registers.BX;
						
						if (DEBUG) {
							printf("sub cx, bx");
						}
						break;
					case ADD_CX_CX:
						registers.CX -= registers.CX;
						
						if (DEBUG) {
							printf("sub cx, cx");
						}
						break;
					case ADD_CX_DX:
						registers.CX -= registers.DX;
						
						if (DEBUG) {
							printf("sub cx, dx");
						}
						break;
					case ADD_DX_AX:
						registers.DX -= registers.AX;

						if (DEBUG) {
							printf("sub dx, ax");
						}
						break;
					case ADD_DX_BX:
						registers.DX -= registers.BX;
						
						if (DEBUG) {
							printf("sub dx, bx");
						}
						break;
					case ADD_DX_CX:
						registers.DX -= registers.CX;
						
						if (DEBUG) {
							printf("sub dx, cx");
						}
						break;
					case ADD_DX_DX:
						registers.DX -= registers.DX;
						
						if (DEBUG) {
							printf("sub dx, dx");
						}
						break;
					default:
						if (DEBUG) {
							printf("Unknwon instruction!");
						}
						break;
				}
				break;
			case INC_AX:
				registers.AX++;
				break;
			case INC_BX:
				registers.BX++;
				break;
			case INC_CX:
				registers.CX++;
				break;
			case INC_DX:
				registers.DX++;
				break;
			case DEC_AX:
				registers.AX--;
				break;
			case DEC_BX:
				registers.BX--;
				break;
			case DEC_CX:
				registers.CX--;
				break;
			case DEC_DX:
				registers.DX--;
				break;
			case INC_DEC:
				if (DEBUG) {
					printf("inc/dec");
				}

				switch(memory[++registers.IP]) {
					case INC_AL:
						registers.AX = (registers.AX & 0xFF00) | ((registers.AX & 0xFF) + 1);
						break;
					case INC_BL:
						registers.BX = (registers.BX & 0xFF00) | ((registers.BX & 0xFF) + 1);
						break;
					case INC_CL:
						registers.CX = (registers.CX & 0xFF00) | ((registers.CX & 0xFF) + 1);
						break;
					case INC_DL:
						registers.DX = (registers.DX & 0xFF00) | ((registers.DX & 0xFF) + 1);
						break;
					case INC_AH:
						registers.AX = ((registers.AX & 0xFF00) + 0x0100) | (registers.AX & 0xFF);
						break;
					case INC_BH:
						registers.BX = ((registers.BX & 0xFF00) + 0x0100) | (registers.BX & 0xFF);
						break;
					case INC_CH:
						registers.CX = ((registers.CX & 0xFF00) + 0x0100) | (registers.AX & 0xFF);
						break;
					case INC_DH:
						registers.DX = ((registers.DX & 0xFF00) + 0x0100) | (registers.DX & 0xFF);
						break;
					case DEC_AL:
						registers.AX = (registers.AX & 0xFF00) | ((registers.AX & 0xFF) - 1);
						break;
					case DEC_BL:
						registers.BX = (registers.BX & 0xFF00) | ((registers.BX & 0xFF) - 1);
						break;
					case DEC_CL:
						registers.CX = (registers.CX & 0xFF00) | ((registers.CX & 0xFF) - 1);
						break;
					case DEC_DL:
						registers.DX = (registers.DX & 0xFF00) | ((registers.DX & 0xFF) - 1);
						break;
					case DEC_AH:
						registers.AX = ((registers.AX & 0xFF00) - 0x0100) | (registers.AX & 0xFF);
						break;
					case DEC_BH:
						registers.BX = ((registers.BX & 0xFF00) - 0x0100) | (registers.BX & 0xFF);
						break;
					case DEC_CH:
						registers.CX = ((registers.CX & 0xFF00) - 0x0100) | (registers.AX & 0xFF);
						break;
					case DEC_DH:
						registers.DX = ((registers.DX & 0xFF00) - 0x0100) | (registers.DX & 0xFF);
						break;
				}
				break;
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
					printf("Unknwon instruction!");
				}
				break;
		}

		if (REGISTERS_VIEW) {
			printf("\tAX = %04X\tBX = %04X\tCX = %04X\tDX = %04X", registers.AX, registers.BX, registers.CX, registers.DX);
		}

		printf("\n");

		registers.IP++;
	}

	if (MEMORY_DUMP) {
		memory_dump("memory.dump", memory);
	}

	free(memory);

	return 0;
}
