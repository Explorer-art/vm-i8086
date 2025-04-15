#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <utils.h>

void read(uint8_t *mem, FILE *fp, size_t file_length) {
	uint8_t buffer[BUFFER_SIZE];
	uint8_t *mem_ptr = mem;
	int bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
		memcpy(mem_ptr, buffer, bytes_read);
		mem_ptr += bytes_read;
	}
}

void registers_dump(const char* filename, Registers* registers) {
	FILE* fp = fopen(filename, "w");

	if (fp == NULL) {
		printf("Erorr opening file %s\n", filename);
		exit(1);
	}

	fprintf(fp, "AL:0x%X\nBL:0x%X\nCL:0x%X\nDL:0x%X\n", registers->ax.low, registers->bx.low, registers->cx.low, registers->dx.low);
	fprintf(fp, "AH:0x%X\nBH:0x%X\nCH:0x%X\nDH:0x%X\n", registers->ax.high, registers->bx.high, registers->cx.high, registers->dx.high);
	fprintf(fp, "AX:0x%X\nBX:0x%X\nCX:0x%X\nDX:0x%X\n", registers->ax.base, registers->bx.base, registers->cx.base, registers->dx.base);

	fclose(fp);
}

void memory_dump(const char *filename, uint8_t* memory) {
	FILE *fp = fopen(filename, "wb");

	if (fp == NULL) {
		printf("Error opening file %s\n", filename);
		exit(1);
	}

	fwrite(memory, 1, MEMORY_SIZE, fp);

	fclose(fp);
}