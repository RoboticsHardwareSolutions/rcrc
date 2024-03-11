#pragma once

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */

// LSB-first
uint8_t crc8_lsb(const char* buf, int len);

// MSB-first
uint8_t crc8_msb(const char* buf, int len);

uint16_t crc16_modbus(const char* buf, unsigned short len);

uint16_t crc16_xmodem(const char* buf, unsigned short len);

uint16_t crc16_ccitt(const char* buf, unsigned short len);

uint32_t crc32(const char* s, int len);

uint32_t crc32_in_split(uint32_t last_crc, const char* s, int len);

uint64_t crc64(const char* s, int l);

// LSB-first
uint8_t crc8_poly_lsb(uint8_t poly, uint8_t value);

// MSB-first
uint8_t crc8_poly_msb(uint8_t poly, uint8_t value);

// LSB-first
uint16_t crc16_poly_lsb(uint16_t poly, uint16_t value);

// MSB-first
uint16_t crc16_poly_msb(uint16_t poly, uint16_t value);

// LSB-first
uint32_t crc32_poly(uint32_t poly, uint16_t value);

// LSB-first
uint64_t crc64_poly(uint64_t poly, uint16_t value);

#ifdef __cplusplus
}
#endif /* __cplusplus  */
