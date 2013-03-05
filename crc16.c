/**
 * crc16 module for calculating and testing crc16 value
 *
 * functions:
 *    addCRC16 .. calculates CRC16 and adds it in the end of data array
 *    testCRC16 .. test data if its CRC16 valid (results 0)
 *
 **/

#include "crc16.h"

// calculate CRC16 and add it to the end of the data
void addCRC16(uint8_t* data, uint8_t *dlen, const uint32_t pol)
{
    uint32_t reg = 0;
    uint8_t i,j;

    for (i=0;i<*dlen;i++)
    {
        reg |= *data++;
        for (j=0;j<8;j++)
        {
            reg <<= 1;
            if ((reg&0x01000000)!=0)
                reg ^= pol;
        }
    }
    for (i=0;i<16;i++)
    {
        reg <<= 1;
        if ((reg&0x01000000)!=0)
            reg ^= pol;
    }

    reg >>= 8;
    j = (uint8_t)reg;
    reg >>= 8;
    *data++ = (uint8_t)reg;
    *data++ = j;
    *dlen+=2;
}

// test CRC16
bool testCRC16(uint8_t* data, uint8_t dlen, const uint32_t pol)
{
    uint32_t reg = 0;
    uint8_t i,j;

    for (i=0;i<dlen;i++)
    {
        reg |= *data++;
        for (j=0;j<8;j++)
        {
            reg <<= 1;
            if ((reg&0x01000000)!=0)
                reg ^= pol;
        }
    }
    if ((reg&0x00FFFFFF)!=0) return false;
    return true;
}
