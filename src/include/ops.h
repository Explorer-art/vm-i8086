#pragma once

#include <stdint.h>

void mov8(uint8_t* dst, uint8_t* src);
void mov16(uint16_t* dst, uint16_t* src);
void add8(uint8_t* dst, uint8_t* src);
void add16(uint16_t* dst, uint16_t* src);
void sub8(uint8_t* dst, uint8_t* src);
void sub16(uint16_t* dst, uint16_t* src);
void and8(uint8_t* dst, uint8_t* src);
void and16(uint16_t* dst, uint16_t* src);
void or8(uint8_t* dst, uint8_t* src);
void or16(uint16_t* dst, uint16_t* src);
void xor8(uint8_t* dst, uint8_t* src);
void xor16(uint16_t* dst, uint16_t* src);