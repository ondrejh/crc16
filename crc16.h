/**
 * crc16 module header
 *
 **/

#ifndef __CRC16_H__
#define __CRC16_H__

#include <inttypes.h>
#include <stdbool.h>

void addCRC16(uint8_t* data, uint8_t *dlen, const uint32_t pol);
bool testCRC16(uint8_t* data, uint8_t dlen, const uint32_t pol);

#endif
