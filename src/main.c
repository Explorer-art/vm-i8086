#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>
#include <i8086.h>

#define VERSION			"0.1.2"
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
			printf("0x%05X ", registers.IP);
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
					case AL_AL:
						if (DEBUG) {
							printf("mov al, al");
						}
						registers.AX.low = registers.AX.low;
						break;
					case AL_BL:
						if (DEBUG) {
							printf("mov al, bl");
						}
						registers.AX.low = registers.BX.low;
						break;
					case AL_CL:
						if (DEBUG) {
							printf("mov al, cl");
						}
						registers.AX.low = registers.CX.low;
						break;
					case AL_DL:
						if (DEBUG) {
							printf("mov al, dl");
						}
						registers.AX.low = registers.DX.low;
						break;
					case BL_AL:
						if (DEBUG) {
							printf("mov bl, al");
						}
						registers.BX.low = registers.AX.low;
						break;
					case BL_BL:
						if (DEBUG) {
							printf("mov bl, bl");
						}
						registers.BX.low = registers.BX.low;
						break;
					case BL_CL:
						if (DEBUG) {
							printf("mov bl, cl");
						}
						registers.BX.low = registers.CX.low;
						break;
					case BL_DL:
						if (DEBUG) {
							printf("mov bl, dl");
						}
						registers.BX.low = registers.DX.low;
						break;
					case CL_AL:
						if (DEBUG) {
							printf("mov cl, al");
						}
						registers.CX.low = registers.AX.low;
						break;
					case CL_BL:
						if (DEBUG) {
							printf("mov cl, bl");
						}
						registers.CX.low = registers.BX.low;
						break;
					case CL_CL:
						if (DEBUG) {
							printf("mov cl, cl");
						}
						registers.CX.low = registers.CX.low;
						break;
					case CL_DL:
						if (DEBUG) {
							printf("mov cl, dl");
						}
						registers.CX.low = registers.DX.low;
						break;
					case DL_AL:
						if (DEBUG) {
							printf("mov dl, al");
						}
						registers.DX.low = registers.AX.low;
						break;
					case DL_BL:
						if (DEBUG) {
							printf("mov dl, bl");
						}
						registers.DX.low = registers.BX.low;
						break;
					case DL_CL:
						if (DEBUG) {
							printf("mov dl, cl");
						}
						registers.DX.low = registers.CX.low;
						break;
					case DL_DL:
						if (DEBUG) {
							printf("mov dl, dl");
						}
						registers.DX.low = registers.DX.low;
						break;
					case AH_AH:
						if (DEBUG) {
							printf("mov ah, ah");
						}
						registers.AX.high = registers.AX.high;
						break;
					case AH_BH:
						if (DEBUG) {
							printf("mov ah, bh");
						}
						registers.AX.high = registers.BX.high;
						break;
					case AH_CH:
						if (DEBUG) {
							printf("mov ah, ch");
						}
						registers.AX.high = registers.CX.high;
						break;
					case AH_DH:
						if (DEBUG) {
							printf("mov ah, dh");
						}
						registers.AX.high = registers.DX.high;
						break;
					case BH_AH:
						if (DEBUG) {
							printf("mov bh, ah");
						}
						registers.BX.high = registers.AX.high;
						break;
					case BH_BH:
						if (DEBUG) {
							printf("mov bh, bh");
						}
						registers.BX.high = registers.BX.high;
						break;
					case BH_CH:
						if (DEBUG) {
							printf("mov bh, ch");
						}
						registers.BX.high = registers.CX.high;
						break;
					case BH_DH:
						if (DEBUG) {
							printf("mov bh, dh");
						}
						registers.BX.high = registers.DX.high;
						break;
					case CH_AH:
						if (DEBUG) {
							printf("mov ch, ah");
						}
						registers.CX.high = registers.AX.high;
						break;
					case CH_BH:
						if (DEBUG) {
							printf("mov ch, bh");
						}
						registers.CX.high = registers.BX.high;
						break;
					case CH_CH:
						if (DEBUG) {
							printf("mov ch, ch");
						}
						registers.CX.high = registers.CX.high;
						break;
					case CH_DH:
						if (DEBUG) {
							printf("mov ch, dh");
						}
						registers.CX.high = registers.DX.high;
						break;
					case DH_AH:
						if (DEBUG) {
							printf("mov dh, ah");
						}
						registers.DX.high = registers.AX.high;
						break;
					case DH_BH:
						if (DEBUG) {
							printf("mov dh, bh");
						}
						registers.DX.high = registers.BX.high;
						break;
					case DH_CH:
						if (DEBUG) {
							printf("mov dh, ch");
						}
						registers.DX.high = registers.CX.high;
						break;
					case DH_DH:
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
			case AL_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov al, %X", registers.AX.low);
				}

				registers.AX.low = memory[++registers.IP];

				break;
			case BL_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov bl, %X", registers.AX.low);
				}

				registers.BX.low = memory[++registers.IP];
				break;
			case CL_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov cl, %X", registers.AX.low);
				}

				registers.CX.low = memory[++registers.IP];
				break;
			case DL_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov dl, %X", registers.AX.low);
				}

				registers.DX.low = memory[++registers.IP];
				break;
			case AH_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov ah, %X", registers.AX.high);
				}

				registers.AX.high = memory[++registers.IP];
				break;
			case BH_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov bh, %X", registers.BX.high);
				}

				registers.BX.high = memory[++registers.IP];
				break;
			case CH_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov ch, %X", registers.CX.high);
				}

				registers.CX.high = memory[++registers.IP];
				break;
			case DH_REG:
				if (DEBUG) {
					printf("%02X ", memory[registers.IP + 1]);
				}

				if (DEBUG) {
					printf("mov dh, %X", registers.DX.high);
				}

				registers.DX.high = memory[++registers.IP];
				break;
			case AX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				if (DEBUG) {
					printf("mov ax, %X", registers.AX.base);
				}

				registers.AX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);
				break;
			case BX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				if (DEBUG) {
					printf("mov bx, %X", registers.BX.base);
				}

				registers.BX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);
				break;
			case CX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				if (DEBUG) {
					printf("mov cx, %X", registers.CX.base);
				}

				registers.CX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);
				break;
			case DX_REG:
				if (DEBUG) {
					printf("%02X %02X ", memory[registers.IP + 1], memory[registers.IP + 2]);
				}

				if (DEBUG) {
					printf("mov dx, %X", registers.DX.base);
				}

				registers.DX.base = memory[++registers.IP] | (memory[++registers.IP] << 8);
				break;
			case ADD_8REG_REG:
			    registers.IP++;

			    switch (memory[registers.IP]) {
			        case OP_AX_AX:
			            registers.AX.low += registers.AX.low;
			            if (DEBUG) {
			                printf("add al, al");
			            }
			            break;
			        case OP_AX_BX:
			            registers.AX.low += registers.BX.low;
			            if (DEBUG) {
			                printf("add al, bl");
			            }
			            break;
			        case OP_AX_CX:
			            registers.AX.low += registers.CX.low;
			            if (DEBUG) {
			                printf("add al, cl");
			            }
			            break;
			        case OP_AX_DX:
			            registers.AX.low += registers.DX.low;
			            if (DEBUG) {
			                printf("add al, dl");
			            }
			            break;
			        case OP_BX_AX:
			            registers.BX.low += registers.AX.low;
			            if (DEBUG) {
			                printf("add bl, al");
			            }
			            break;
			        case OP_BX_BX:
			            registers.BX.low += registers.BX.low;
			            if (DEBUG) {
			                printf("add bl, bl");
			            }
			            break;
			        case OP_BX_CX:
			            registers.BX.low += registers.CX.low;
			            if (DEBUG) {
			                printf("add bl, cl");
			            }
			            break;
			        case OP_BX_DX:
			            registers.BX.low += registers.DX.low;
			            if (DEBUG) {
			                printf("add bl, dl");
			            }
			            break;
			        case OP_CX_AX:
			            registers.CX.low += registers.AX.low;
			            if (DEBUG) {
			                printf("add cl, al");
			            }
			            break;
			        case OP_CX_BX:
			            registers.CX.low += registers.BX.low;
			            if (DEBUG) {
			                printf("add cl, bl");
			            }
			            break;
			        case OP_CX_CX:
			            registers.CX.low += registers.CX.low;
			            if (DEBUG) {
			                printf("add cl, cl");
			            }
			            break;
			        case OP_CX_DX:
			            registers.CX.low += registers.DX.low;
			            if (DEBUG) {
			                printf("add cl, dl");
			            }
			            break;
			        case OP_DX_AX:
			            registers.DX.low += registers.AX.low;
			            if (DEBUG) {
			                printf("add dl, al");
			            }
			            break;
			        case OP_DX_BX:
			            registers.DX.low += registers.BX.low;
			            if (DEBUG) {
			                printf("add dl, bl");
			            }
			            break;
			        case OP_DX_CX:
			            registers.DX.low += registers.CX.low;
			            if (DEBUG) {
			                printf("add dl, cl");
			            }
			            break;
			        case OP_DX_DX:
			            registers.DX.low += registers.DX.low;
			            if (DEBUG) {
			                printf("add dl, dl");
			            }
			            break;
			        case AH_AH:
			            registers.AX.high += registers.AX.high;
			            if (DEBUG) {
			                printf("add ah, ah");
			            }
			            break;
			        case AH_BH:
			            registers.AX.high += registers.BX.high;
			            if (DEBUG) {
			                printf("add ah, bh");
			            }
			            break;
			        case AH_CH:
			            registers.AX.high += registers.CX.high;
			            if (DEBUG) {
			                printf("add ah, ch");
			            }
			            break;
			        case AH_DH:
			            registers.AX.high += registers.DX.high;
			            if (DEBUG) {
			                printf("add ah, dh");
			            }
			            break;
			        case BH_AH:
			            registers.BX.high += registers.AX.high;
			            if (DEBUG) {
			                printf("add bh, ah");
			            }
			            break;
			        case BH_BH:
			            registers.BX.high += registers.BX.high;
			            if (DEBUG) {
			                printf("add bh, bh");
			            }
			            break;
			        case BH_CH:
			            registers.BX.high += registers.CX.high;
			            if (DEBUG) {
			                printf("add bh, ch");
			            }
			            break;
			        case BH_DH:
			            registers.BX.high += registers.DX.high;
			            if (DEBUG) {
			                printf("add bh, dh");
			            }
			            break;
			        case CH_AH:
			            registers.CX.high += registers.AX.high;
			            if (DEBUG) {
			                printf("add ch, ah");
			            }
			            break;
			        case CH_BH:
			            registers.CX.high += registers.BX.high;
			            if (DEBUG) {
			                printf("add ch, bh");
			            }
			            break;
			        case CH_CH:
			            registers.CX.high += registers.CX.high;
			            if (DEBUG) {
			                printf("add ch, ch");
			            }
			            break;
			        case CH_DH:
			            registers.CX.high += registers.DX.high;
			            if (DEBUG) {
			                printf("add ch, dh");
			            }
			            break;
			        case DH_AH:
			            registers.DX.high += registers.AX.high;
			            if (DEBUG) {
			                printf("add dh, ah");
			            }
			            break;
			        case DH_BH:
			            registers.DX.high += registers.BX.high;
			            if (DEBUG) {
			                printf("add dh, bh");
			            }
			            break;
			        case DH_CH:
			            registers.DX.high += registers.CX.high;
			            if (DEBUG) {
			                printf("add dh, ch");
			            }
			            break;
			        case DH_DH:
			            registers.DX.high += registers.DX.high;
			            if (DEBUG) {
			                printf("add dh, dh");
			            }
			            break;
			        default:
			            if (DEBUG) {
			                printf("Unknown opcode!");
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
			                printf("add bx, cx");
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
			                printf("Unknown opcode!");
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
			            registers.AX.low -= registers.DX.low;
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
			        case AH_AH:
			            registers.AX.high -= registers.AX.high;
			            if (DEBUG) {
			                printf("sub ah, ah");
			            }
			            break;
			        case AH_BH:
			            registers.AX.high -= registers.BX.high;
			            if (DEBUG) {
			                printf("sub ah, bh");
			            }
			            break;
			        case AH_CH:
			            registers.AX.high -= registers.CX.high;
			            if (DEBUG) {
			                printf("sub ah, ch");
			            }
			            break;
			        case AH_DH:
			            registers.AX.high -= registers.DX.high;
			            if (DEBUG) {
			                printf("sub ah, dh");
			            }
			            break;
			        case BH_AH:
			            registers.BX.high -= registers.AX.high;
			            if (DEBUG) {
			                printf("sub bh, ah");
			            }
			            break;
			        case BH_BH:
			            registers.BX.high -= registers.BX.high;
			            if (DEBUG) {
			                printf("sub bh, bh");
			            }
			            break;
			        case BH_CH:
			            registers.BX.high -= registers.CX.high;
			            if (DEBUG) {
			                printf("sub bh, ch");
			            }
			            break;
			        case BH_DH:
			            registers.BX.high -= registers.DX.high;
			            if (DEBUG) {
			                printf("sub bh, dh");
			            }
			            break;
			        case CH_AH:
			            registers.CX.high -= registers.AX.high;
			            if (DEBUG) {
			                printf("sub ch, ah");
			            }
			            break;
			        case CH_BH:
			            registers.CX.high -= registers.BX.high;
			            if (DEBUG) {
			                printf("sub ch, bh");
			            }
			            break;
			        case CH_CH:
			            registers.CX.high -= registers.CX.high;
			            if (DEBUG) {
			                printf("sub ch, ch");
			            }
			            break;
			        case CH_DH:
			            registers.CX.high -= registers.DX.high;
			            if (DEBUG) {
			                printf("sub ch, dh");
			            }
			            break;
			        case DH_AH:
			            registers.DX.high -= registers.AX.high;
			            if (DEBUG) {
			                printf("sub dh, ah");
			            }
			            break;
			        case DH_BH:
			            registers.DX.high -= registers.BX.high;
			            if (DEBUG) {
			                printf("sub dh, bh");
			            }
			            break;
			        case DH_CH:
			            registers.DX.high -= registers.CX.high;
			            if (DEBUG) {
			                printf("sub dh, ch");
			            }
			            break;
			        case DH_DH:
			            registers.DX.high -= registers.DX.high;
			            if (DEBUG) {
			                printf("sub dh, dh");
			            }
			            break;
			        default:
			            if (DEBUG) {
			                printf("Unknown opcode!");
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
			                printf("sub bx, cx");
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
			                printf("Unknown opcode!");
			            }
			            break;
			    }
			    break;
			case ADD_AL_VALUE:
				if (DEBUG) {
					printf("add al, %02X", memory[++registers.IP]);
				}
				registers.AX.low += memory[registers.IP];
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
					case ADD_AH:
						registers.AX.high += memory[registers.IP];
					case ADD_BH:
						registers.BX.high += memory[registers.IP];
					case ADD_CH:
						registers.CX.high += memory[registers.IP];
					case ADD_DH:
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
			case AND_8REG:
				switch (memory[++registers.IP]) {
					case AL_AL:
						if (DEBUG) {
			                printf("and al, al");
			            }
			            registers.AX.low &= registers.AX.low;
			            break;
			        case AL_BL:
			        	if (DEBUG) {
			                printf("and al, bl");
			            }
			            registers.AX.low &= registers.BX.low;
			            break;
			        case AL_CL:
			        	if (DEBUG) {
			                printf("and al, cl");
			            }
			            registers.AX.low &= registers.CX.low;
			            break;
			        case AL_DL:
			        	if (DEBUG) {
			                printf("and al, dl");
			            }
			            registers.AX.low &= registers.DX.low;
			            break;
			        case BL_AL:
			        	if (DEBUG) {
			                printf("and bl, al");
			            }
			            registers.BX.low &= registers.AX.low;
			            break;
			        case BL_BL:
			        	if (DEBUG) {
			                printf("and bl, bl");
			            }
			            registers.BX.low &= registers.BX.low;
			            break;
			        case BL_CL:
			        	if (DEBUG) {
			                printf("and bl, cl");
			            }
			            registers.BX.low &= registers.CX.low;
			            break;
			        case BL_DL:
			        	if (DEBUG) {
			                printf("and bl, dl");
			            }
			            registers.BX.low &= registers.DX.low;
			            break;
			        case CL_AL:
			        	if (DEBUG) {
			                printf("and cl, al");
			            }
			            registers.CX.low &= registers.AX.low;
			            break;
			        case CL_BL:
			        	if (DEBUG) {
			                printf("and cl, bl");
			            }
			            registers.CX.low &= registers.BX.low;
			            break;
			        case CL_CL:
			        	if (DEBUG) {
			                printf("and cl, cl");
			            }
			            registers.CX.low &= registers.CX.low;
			            break;
			        case CL_DL:
			        	if (DEBUG) {
			                printf("and cl, dl");
			            }
			            registers.CX.low &= registers.DX.low;
			            break;
			        case DL_AL:
			        	if (DEBUG) {
			                printf("and dl, al");
			            }
			            registers.DX.low &= registers.AX.low;
			            break;
			        case DL_BL:
			        	if (DEBUG) {
			                printf("and dl, bl");
			            }
			            registers.DX.low &= registers.BX.low;
			            break;
			        case DL_CL:
			        	if (DEBUG) {
			                printf("and dl, cl");
			            }
			            registers.DX.low &= registers.CX.low;
			            break;
			        case DL_DL:
			        	if (DEBUG) {
			                printf("and dl, dl");
			            }
			            registers.DX.low &= registers.DX.low;
			            break;
			        case AH_AH:
			        	if (DEBUG) {
			                printf("and ah, ah");
			            }
			            registers.AX.high &= registers.AX.high;
			            break;
			        case AH_BH:
			        	if (DEBUG) {
			                printf("and ah, bh");
			            }
			            registers.AX.high &= registers.BX.high;
			            break;
			        case AH_CH:
			        	if (DEBUG) {
			                printf("and ah, ch");
			            }
			            registers.AX.high &= registers.CX.high;
			            break;
			        case AH_DH:
			        	if (DEBUG) {
			                printf("and ah, dh");
			            }
			            registers.AX.high &= registers.DX.high;
			            break;
			        case BH_AH:
			        	if (DEBUG) {
			                printf("and bh, ah");
			            }
			            registers.BX.high &= registers.AX.high;
			            break;
			        case BH_BH:
			        	if (DEBUG) {
			                printf("and bh, bh");
			            }
			            registers.BX.high &= registers.BX.high;
			            break;
			        case BH_CH:
			        	if (DEBUG) {
			                printf("and bh, ch");
			            }
			            registers.BX.high &= registers.CX.high;
			            break;
			        case BH_DH:
			        	if (DEBUG) {
			                printf("and bh, dh");
			            }
			            registers.BX.high &= registers.DX.high;
			            break;
			        case CH_AH:
			        	if (DEBUG) {
			                printf("and ch, ah");
			            }
			            registers.CX.high &= registers.AX.high;
			            break;
			        case CH_BH:
			        	if (DEBUG) {
			                printf("and ch, bh");
			            }
			            registers.CX.high &= registers.BX.high;
			            break;
			        case CH_CH:
			        	if (DEBUG) {
			                printf("and ch, ch");
			            }
			            registers.CX.high &= registers.CX.high;
			            break;
			        case CH_DH:
			        	if (DEBUG) {
			                printf("and ch, dh");
			            }
			            registers.CX.high &= registers.DX.high;
			            break;
			        case DH_AH:
			        	if (DEBUG) {
			                printf("and dh, ah");
			            }
			            registers.DX.high &= registers.AX.high;
			            break;
			        case DH_BH:
			        	if (DEBUG) {
			                printf("and dh, bh");
			            }
			            registers.DX.high &= registers.BX.high;
			            break;
			        case DH_CH:
			        	if (DEBUG) {
			                printf("and dh, ch");
			            }
			            registers.DX.high &= registers.CX.high;
			            break;
			        case DH_DH:
			        	if (DEBUG) {
			                printf("and dh, dh");
			            }
			            registers.DX.high &= registers.DX.high;
			            break;
			        default:
			        	if (DEBUG) {
			        		printf("Unknown opcode!");
			        	}
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
					printf("Unknown opcode!");
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
