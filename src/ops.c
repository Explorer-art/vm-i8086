#include <ops.h>

void mov8(uint8_t* dst, uint8_t* src) { *dst = *src; }
void mov16(uint16_t* dst, uint16_t* src) { *dst = *src; }
void add8(uint8_t* dst, uint8_t* src) { *dst += *src; }
void add16(uint16_t* dst, uint16_t* src) { *dst += *src; }
void sub8(uint8_t* dst, uint8_t* src) { *dst -= *src; }
void sub16(uint16_t* dst, uint16_t* src) { *dst -= *src; }
void and8(uint8_t* dst, uint8_t* src) { *dst &= *src; }
void and16(uint16_t* dst, uint16_t* src) { *dst &= *src; }
void or8(uint8_t* dst, uint8_t* src) { *dst |= *src; }
void or16(uint16_t* dst, uint16_t* src) { *dst |= *src; }
void xor8(uint8_t* dst, uint8_t* src) { *dst ^= *src; }
void xor16(uint16_t* dst, uint16_t* src) { *dst ^= *src; }