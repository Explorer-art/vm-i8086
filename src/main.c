#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include <i8086.h>

#define VERSION			"0.1.1"
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
			printf("%05d ", registers.IP);
		}

		if (DEBUG) {
			printf("%02X ", memory[registers.IP]);
		}

		switch (memory[registers.IP]) {
			case MOV_8REG_REG:
				registers.IP++;

				if (DEBUG) {
					printf("%02X ", memory[registers.IP]);
				}

				switch (memory[registers.IP]) {
					case MOV_AL_AL:
						if (DEBUG) {
							printf("mov al, al");
						}

						registers.AX.low = registers.AX.low;
						break;
					case MOV_AL_BL:
						if (DEBUG) {
							printf("mov al, bl");
						}

						registers.AX.low = registers.BX.low;
						break;
					case MOV_AL_CL:
						if (DEBUG) {
							printf("mov al, cl");
						}

						registers.AX.low = registers.CX.low;
						break;
					case MOV_AL_DL:
						if (DEBUG) {
							printf("mov al, dl");
						}

						registers.AX.low = registers.DX.low;
						break;
					case MOV_BL_AL:
						if (DEBUG) {
							printf("mov bl, al");
						}

						registers.BX.low = registers.AX.low;
						break;
					case MOV_BL_BL:
						if (DEBUG) {
							printf("mov bl, bl");
						}

						registers.BX.low = registers.BX.low;
						break;
					case MOV_BL_CL:
						if (DEBUG) {
							printf("mov bl, cl");
						}

						registers.BX.low = registers.CX.low;
						break;
					case MOV_BL_DL:
						if (DEBUG) {
							printf("mov bl, dl");
						}

						registers.BX.low = registers.DX.low;
						break;
					case MOV_CL_AL:
						if (DEBUG) {
							printf("mov cl, al");
						}

						registers.CX.low = registers.AX.low;
						break;
					case MOV_CL_BL:
						if (DEBUG) {
							printf("mov cl, bl");
						}

						registers.CX.low = registers.BX.low;
						break;
					case MOV_CL_CL:
						if (DEBUG) {
							printf("mov cl, cl");
						}

						registers.CX.low = registers.CX.low;
						break;
					case MOV_CL_DL:
						if (DEBUG) {
							printf("mov cl, dl");
						}

						registers.CX.low = registers.DX.low;
						break;
					case MOV_DL_AL:
						if (DEBUG) {
							printf("mov dl, al");
						}

						registers.DX.low = registers.AX.low;
						break;
					case MOV_DL_BL:
						if (DEBUG) {
							printf("mov dl, bl");
						}

						registers.DX.low = registers.BX.low;
						break;
					case MOV_DL_CL:
						if (DEBUG) {
							printf("mov dl, cl");
						}

						registers.DX.low = registers.CX.low;
						
						break;
					case MOV_DL_DL:
						if (DEBUG) {
							printf("mov dl, dl");
						}

						registers.DX.low = registers.DX.low;
						break;
					case MOV_AH_AH:
						if (DEBUG) {
							printf("mov ah, ah");
						}

						registers.AX.high = registers.AX.high;
						break;
					case MOV_AH_BH:
						if (DEBUG) {
							printf("mov ah, bh");
						}

						registers.AX.high = registers.BX.high;
						break;
					case MOV_AH_CH:
						if (DEBUG) {
							printf("mov ah, ch");
						}

						registers.AX.high = registers.CX.high;
						break;
					case MOV_AH_DH:
						if (DEBUG) {
							printf("mov ah, dh");
						}

						registers.AX.high = registers.DX.high;
						break;
					case MOV_BH_AH:
						if (DEBUG) {
							printf("mov bh, ah");
						}

						registers.BX.high = registers.AX.high;
						break;
					case MOV_BH_BH:
						if (DEBUG) {
							printf("mov bh, bh");
						}

						registers.BX.high = registers.BX.high;
						break;
					case MOV_BH_CH:
						if (DEBUG) {
							printf("mov bh, ch");
						}

						registers.BX.high = registers.CX.high;
						break;
					case MOV_BH_DH:
						if (DEBUG) {
							printf("mov bh, dh");
						}

						registers.BX.high = registers.DX.high;
						break;
					case MOV_CH_AH:
						if (DEBUG) {
							printf("mov ch, ah");
						}

						registers.CX.high = registers.AX.high;
						break;
					case MOV_CH_BH:
						if (DEBUG) {
							printf("mov ch, bh");
						}

						registers.CX.high = registers.BX.high;
						break;
					case MOV_CH_CH:
						if (DEBUG) {
							printf("mov ch, ch");
						}

						registers.CX.high = registers.CX.high;
						break;
					case MOV_CH_DH:
						if (DEBUG) {
							printf("mov ch, dh");
						}

						registers.CX.high = registers.DX.high;
						break;
					case MOV_DH_AH:
						if (DEBUG) {
							printf("mov dh, ah");
						}

						registers.DX.high = registers.AX.high;
						break;
					case MOV_DH_BH:
						if (DEBUG) {
							printf("mov dh, bh");
						}

						registers.DX.high = registers.BX.high;
						break;
					case MOV_DH_CH:
						if (DEBUG) {
							printf("mov dh, ch");
						}

						registers.DX.high = registers.CX.high;
						
						break;
					case MOV_DH_DH:
						if (DEBUG) {
							printf("mov dh, dh");
						}

						registers.DX.high = registers.DX.high;
						break;
					default:
						if (DEBUG) {
							printf("Unknwon instruction!");
						}
						break;
				}
				break;
			case MOV_16REG_REG:
				registers.IP++;

				if (DEBUG) {
					printf("%02X ", memory[registers.IP]);
				}
				
				switch (memory[registers.IP]) {
					case MOV_AX_AX:
						if (DEBUG) {
							printf("mov ax, ax");
						}

						registers.AX.base = registers.AX.base;
						break;
					case MOV_AX_BX:
						if (DEBUG) {
							printf("mov ax, bx");
						}

						registers.AX.base = registers.BX.base;				
						break;
					case MOV_AX_CX:
						if (DEBUG) {
							printf("mov ax, cx");
						}

						registers.AX.base = registers.CX.base;
						break;
					case MOV_AX_DX:
						if (DEBUG) {
							printf("mov ax, dx");
						}

						registers.AX.base = registers.DX.base;
						break;
					case MOV_BX_AX:
						if (DEBUG) {
							printf("mov bx, ax");
						}

						registers.BX.base = registers.AX.base;
						break;
					case MOV_BX_BX:
						if (DEBUG) {
							printf("mov bx, bx");
						}

						registers.BX.base = registers.BX.base;
						break;
					case MOV_BX_CX:
						if (DEBUG) {
							printf("mov bx, cx");
						}

						registers.BX.base = registers.CX.base;
						break;
					case MOV_BX_DX:
						if (DEBUG) {
							printf("mov bx, dx");
						}

						registers.BX.base = registers.DX.base;
						break;
					case MOV_CX_AX:
						if (DEBUG) {
							printf("mov cx, ax");
						}

						registers.CX.base = registers.AX.base;
						break;
					case MOV_CX_BX:
						if (DEBUG) {
							printf("mov cx, bx");
						}

						registers.CX.base = registers.BX.base;
						break;
					case MOV_CX_CX:
						if (DEBUG) {
							printf("mov cx, cx");
						}

						registers.CX.base = registers.CX.base;
						break;
					case MOV_CX_DX:
						if (DEBUG) {
							printf("mov cx, dx");
						}

						registers.CX.base = registers.DX.base;
						break;
					case MOV_DX_AX:
						if (DEBUG) {
							printf("mov dx, ax");
						}

						registers.DX.base = registers.AX.base;
						break;
					case MOV_DX_BX:
						if (DEBUG) {
							printf("mov dx, bx");
						}

						registers.DX.base = registers.BX.base;
						break;
					case MOV_DX_CX:
						if (DEBUG) {
							printf("mov dx, cx");
						}

						registers.DX.base = registers.CX.base;
						
						break;
					case MOV_DX_DX:
						if (DEBUG) {
							printf("mov dx, dx");
						}

						registers.DX.base = registers.DX.base;
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

				registers.AX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov ax, %X", registers.AX);
				}
				break;
			case BX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				registers.BX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov bx, %X", registers.BX);
				}
				break;
			case CX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				registers.CX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov cx, %X", registers.CX);
				}
				break;
			case DX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				registers.DX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);

				if (DEBUG) {
					printf("mov dx, %X", registers.DX);
				}
				break;
			case ADD_8REG_REG:
				registers.IP++;

				switch (memory[registers.IP]) {
					case OP_AX_AX:
						registers.AX.low = registers.AX.low;

						if (DEBUG) {
							printf("add al, al");
						}
						break;
					case OP_AX_BX:
						registers.AX.low = registers.BX.low;
						
						if (DEBUG) {
							printf("add al, bl");
						}
						break;
					case OP_AX_CX:
						registers.AX.low = registers.CX.low;
						
						if (DEBUG) {
							printf("add al, cl");
						}
						break;
					case OP_AX_DX:
						registers.AX.low = registers.DX.low;
						
						if (DEBUG) {
							printf("add al, dl");
						}
						break;
					case OP_BX_AX:
						registers.BX.low = registers.AX.low;

						if (DEBUG) {
							printf("add bl, al");
						}
						break;
					case OP_BX_BX:
						registers.BX.low = registers.BX.low;
						
						if (DEBUG) {
							printf("add bl, bl");
						}
						break;
					case OP_BX_CX:
						registers.BX.low = registers.CX.low;
						
						if (DEBUG) {
							printf("add bl, cl");
						}
						break;
					case OP_BX_DX:
						registers.BX.low = registers.DX.low;
						
						if (DEBUG) {
							printf("add bl, dl");
						}
						break;
					case OP_CX_AX:
						registers.CX.low = registers.AX.low;

						if (DEBUG) {
							printf("add cl, al");
						}
						break;
					case OP_CX_BX:
						registers.CX.low = registers.BX.low;
						
						if (DEBUG) {
							printf("add cl, bl");
						}
						break;
					case OP_CX_CX:
						registers.CX.low = registers.CX.low;
						
						if (DEBUG) {
							printf("add cl, cl");
						}
						break;
					case OP_CX_DX:
						registers.CX.low = registers.DX.low;
						
						if (DEBUG) {
							printf("add cl, dl");
						}
						break;
					case OP_DX_AX:
						registers.DX.low = registers.AX.low;

						if (DEBUG) {
							printf("add dl, al");
						}
						break;
					case OP_DX_BX:
						registers.DX.low = registers.BX.low;
						
						if (DEBUG) {
							printf("add dl, bl");
						}
						break;
					case OP_DX_CX:
						registers.DX.low = registers.CX.low;
						
						if (DEBUG) {
							printf("add dl, cl");
						}
						break;
					case OP_DX_DX:
						registers.DX.low = registers.DX.low;
						
						if (DEBUG) {
							printf("add dl, dl");
						}
						break;
					default:
						if (DEBUG) {
							printf("Unknwon instruction!");
						}
						break;
				}
				break;
			case ADD_16REG_REG:
				registers.IP++;

				switch (memory[registers.IP]) {
					case OP_AX_AX:
						registers.AX.base += registers.AX.base;

						if (DEBUG) {
							printf("add ax, ax");
						}
						break;
					case OP_AX_BX:
						registers.AX.base += registers.BX.base;
						
						if (DEBUG) {
							printf("add ax, bx");
						}
						break;
					case OP_AX_CX:
						registers.AX.base += registers.CX.base;
						
						if (DEBUG) {
							printf("add ax, cx");
						}
						break;
					case OP_AX_DX:
						registers.AX.base += registers.DX.base;
						
						if (DEBUG) {
							printf("add ax, dx");
						}
						break;
					case OP_BX_AX:
						registers.BX.base += registers.AX.base;

						if (DEBUG) {
							printf("add bx, ax");
						}
						break;
					case OP_BX_BX:
						registers.BX.base += registers.BX.base;
						
						if (DEBUG) {
							printf("add bx, bx");
						}
						break;
					case OP_BX_CX:
						registers.BX.base += registers.CX.base;
						
						if (DEBUG) {
							printf("add bx cx");
						}
						break;
					case OP_BX_DX:
						registers.BX.base += registers.DX.base;
						
						if (DEBUG) {
							printf("add bx, dx");
						}
						break;
					case OP_CX_AX:
						registers.CX.base += registers.AX.base;

						if (DEBUG) {
							printf("add cx, ax");
						}
						break;
					case OP_CX_BX:
						registers.CX.base += registers.BX.base;
						
						if (DEBUG) {
							printf("add cx, bx");
						}
						break;
					case OP_CX_CX:
						registers.CX.base += registers.CX.base;
						
						if (DEBUG) {
							printf("add cx, cx");
						}
						break;
					case OP_CX_DX:
						registers.CX.base += registers.DX.base;
						
						if (DEBUG) {
							printf("add cx, dx");
						}
						break;
					case OP_DX_AX:
						registers.DX.base += registers.AX.base;

						if (DEBUG) {
							printf("add dx, ax");
						}
						break;
					case OP_DX_BX:
						registers.DX.base += registers.BX.base;
						
						if (DEBUG) {
							printf("add dx, bx");
						}
						break;
					case OP_DX_CX:
						registers.DX.base += registers.CX.base;
						
						if (DEBUG) {
							printf("add dx, cx");
						}
						break;
					case OP_DX_DX:
						registers.DX.base += registers.DX.base;
						
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
			case SUB_8REG_REG:
				registers.IP++;

				switch (memory[registers.IP]) {
					case OP_AX_AX:
						registers.AX.low -= registers.AX.low;

						if (DEBUG) {
							printf("sub al, al");
						}
						break;
					case OP_AX_BX:
						registers.AX.low -= registers.BX.low;
						
						if (DEBUG) {
							printf("sub al, bl");
						}
						break;
					case OP_AX_CX:
						registers.AX.low -= registers.CX.low;
						
						if (DEBUG) {
							printf("sub al, cl");
						}
						break;
					case OP_AX_DX:
						registers.AX.low -= registers.AX.low;
						
						if (DEBUG) {
							printf("sub al, dl");
						}
						break;
					case OP_BX_AX:
						registers.BX.low -= registers.AX.low;

						if (DEBUG) {
							printf("sub bl, al");
						}
						break;
					case OP_BX_BX:
						registers.BX.low -= registers.BX.low;
						
						if (DEBUG) {
							printf("sub bl, bl");
						}
						break;
					case OP_BX_CX:
						registers.BX.low -= registers.CX.low;
						
						if (DEBUG) {
							printf("sub bl, cl");
						}
						break;
					case OP_BX_DX:
						registers.BX.low -= registers.DX.low;
						
						if (DEBUG) {
							printf("sub bl, dl");
						}
						break;
					case OP_CX_AX:
						registers.CX.low -= registers.AX.low;

						if (DEBUG) {
							printf("sub cl, al");
						}
						break;
					case OP_CX_BX:
						registers.CX.low -= registers.BX.low;
						
						if (DEBUG) {
							printf("sub cl, bl");
						}
						break;
					case OP_CX_CX:
						registers.CX.low -= registers.CX.low;
						
						if (DEBUG) {
							printf("sub cl, cl");
						}
						break;
					case OP_CX_DX:
						registers.CX.low -= registers.DX.low;
						
						if (DEBUG) {
							printf("sub cl, dl");
						}
						break;
					case OP_DX_AX:
						registers.DX.low -= registers.AX.low;

						if (DEBUG) {
							printf("sub dl, al");
						}
						break;
					case OP_DX_BX:
						registers.DX.low -= registers.BX.low;
						
						if (DEBUG) {
							printf("sub dl, bl");
						}
						break;
					case OP_DX_CX:
						registers.DX.low -= registers.CX.low;
						
						if (DEBUG) {
							printf("sub dl, cl");
						}
						break;
					case OP_DX_DX:
						registers.DX.low -= registers.DX.low;
						
						if (DEBUG) {
							printf("sub dl, dl");
						}
						break;
					default:
						if (DEBUG) {
							printf("Unknwon instruction!");
						}
						break;
				}
				break;
			case SUB_16REG_REG:
				registers.IP++;

				switch (memory[registers.IP]) {
					case OP_AX_AX:
						registers.AX.base -= registers.AX.base;

						if (DEBUG) {
							printf("sub ax, ax");
						}
						break;
					case OP_AX_BX:
						registers.AX.base -= registers.BX.base;
						
						if (DEBUG) {
							printf("sub ax, bx");
						}
						break;
					case OP_AX_CX:
						registers.AX.base -= registers.CX.base;
						
						if (DEBUG) {
							printf("sub ax, cx");
						}
						break;
					case OP_AX_DX:
						registers.AX.base -= registers.DX.base;
						
						if (DEBUG) {
							printf("sub ax, dx");
						}
						break;
					case OP_BX_AX:
						registers.BX.base -= registers.AX.base;

						if (DEBUG) {
							printf("sub bx, ax");
						}
						break;
					case OP_BX_BX:
						registers.BX.base -= registers.BX.base;
						
						if (DEBUG) {
							printf("sub bx, bx");
						}
						break;
					case OP_BX_CX:
						registers.BX.base -= registers.CX.base;
						
						if (DEBUG) {
							printf("sub abx cx");
						}
						break;
					case OP_BX_DX:
						registers.BX.base -= registers.DX.base;
						
						if (DEBUG) {
							printf("sub bx, dx");
						}
						break;
					case OP_CX_AX:
						registers.CX.base -= registers.AX.base;

						if (DEBUG) {
							printf("sub cx, ax");
						}
						break;
					case OP_CX_BX:
						registers.CX.base -= registers.BX.base;
						
						if (DEBUG) {
							printf("sub cx, bx");
						}
						break;
					case OP_CX_CX:
						registers.CX.base -= registers.CX.base;
						
						if (DEBUG) {
							printf("sub cx, cx");
						}
						break;
					case OP_CX_DX:
						registers.CX.base -= registers.DX.base;
						
						if (DEBUG) {
							printf("sub cx, dx");
						}
						break;
					case OP_DX_AX:
						registers.DX.base -= registers.AX.base;

						if (DEBUG) {
							printf("sub dx, ax");
						}
						break;
					case OP_DX_BX:
						registers.DX.base -= registers.BX.base;
						
						if (DEBUG) {
							printf("sub dx, bx");
						}
						break;
					case OP_DX_CX:
						registers.DX.base -= registers.CX.base;
						
						if (DEBUG) {
							printf("sub dx, cx");
						}
						break;
					case OP_DX_DX:
						registers.DX.base -= registers.DX.base;
						
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
			case ADD_AL_VALUE:
				registers.AX.low += memory[++registers.IP];

				if (DEBUG) {
					printf("add al, %02X", memory[registers.IP]);
				}
				break;
			case ADD_8REG_VALUE:
				registers.IP++;

				switch (memory[registers.IP++]) {
					case ADD_BL:
						registers.BX.low += memory[registers.IP];
						break;
					case ADD_CL:
						registers.CX.low += memory[registers.IP];
						break;
					case ADD_DL:
						registers.DX.low += memory[registers.IP];
						break;
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
