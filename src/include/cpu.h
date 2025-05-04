#pragma once

#include <stdint.h>

#define MEMORY_SIZE 1048576

typedef union {
	uint16_t base;
	struct {
		uint8_t low;
		uint8_t high;
	};
} Register;

typedef struct {
	Register ax;
	Register bx;
	Register cx;
	Register dx;
	uint16_t sp;
	uint16_t bp;
	uint16_t si;
	uint16_t di;
	uint16_t cs;
	uint16_t ds;
	uint16_t ss;
	uint16_t es;
	uint16_t ip;
	uint16_t flags;
} Registers;

extern const char* reg8_names[];
extern const char* reg16_names[];
