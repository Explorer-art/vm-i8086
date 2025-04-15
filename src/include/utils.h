#pragma once

#include <stdint.h>
#include <cpu.h>

#define BUFFER_SIZE 1024

void read(uint8_t* mem, FILE* fp, size_t file_length);
void registers_dump(const char* filename, Registers* registers);
void memory_dump(const char* filename, uint8_t* memory);
