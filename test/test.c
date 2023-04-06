#include "../crc/crc8.h"
#include "../crc/crc16.h"
#include "../crc/crc32.h"
#include "../crc/crc64.h"
#include "../crc/crc_poly.h"
#include "runit/src/runit.h"

#include <string.h>

void crc8_basic(void)
{
    const char* inData = "123456789";
    uint8_t expect = 0xa2;
    runit_true(crc8_msb(inData, 9) == expect);

    const char* data = "Hello World!!!";
    expect = 0x68;
    runit_true(crc8_msb(data, strlen(data)) ==  expect);

    expect = 0x2c;
    runit_true(crc8_lsb(data, strlen(data))== expect);
}

void crc16_basic(void)
{
    const char* inData = "123456789";
    uint16_t expect = 0x31C3;

    runit_true(crc16(inData, 9) == expect);
}

void crc32_basic(void)
{
    const char* inData = "123456789";
    uint32_t expect = 0xCBF43926;

    runit_true(crc32(inData, 9) ==  expect);
}

void crc64_basic(void)
{
    const char* inData = "123456789";

    uint64_t expect = 0xe9c6d914c4b8d9caL;
    runit_true(crc64(inData, 9) == expect);
}

void crc8_poly(void)
{
    uint8_t poly = 0x31;
    uint8_t crcTab[0xFF+1] = {0};
    uint8_t expect = 0x00;
    runit_true(crc8_poly_msb(poly, 0) == expect);
    expect = 0x31;
    runit_true(crc8_poly_msb(poly, 1) ==  expect);
    expect = 0xac;
    runit_true(crc8_poly_msb(poly, 0xFF) ==  expect);


}

void crc16_poly(void)
{
    // poly = x^16 + x^12 + x^5 + 1 = 0x1021
    uint16_t poly = 0x1021;
    uint16_t crcTab[0xFF+1] = {0};
    uint16_t expect = 0x0000;
    runit_true(crc16_poly_msb(poly, 0) == expect);
    expect = 0x1021;
    runit_true(crc16_poly_msb(poly, 1)== expect);
    expect = 0x1ef0;
    runit_true(crc16_poly_msb(poly, 0xFF) ==  expect);
}

void crc32_polyt(void)
{
    uint32_t poly = 0xedb88320;
    uint32_t crcTab[0xFF+1] = {0};
    uint32_t expect = 0x00000000L;
    runit_true(crc32_poly(poly, 0) ==  expect);
    expect = 0x77073096L;
    runit_true(crc32_poly(poly, 1) ==  expect);
    expect = 0x2d02ef8dL;
    runit_true(crc32_poly(poly, 0xFF) ==  expect);
}




int main(){
    printf("rcr start unit tests\n");
    crc8_basic();
    crc16_basic();
    crc32_basic();
    crc64_basic();
    crc8_poly();
    crc16_poly();
    crc32_polyt();
    return runit_at_least_one_fail;
}

