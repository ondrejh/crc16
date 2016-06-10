/**
 * crc16 module for calculating and testing crc16 value
 *
 * functions:
 *    addCRC16 .. calculates CRC16 and adds it in the end of data array
 *    testCRC16 .. test data if its CRC16 valid (results 0)
 *
 **/

#include "crc16.h"
#include <stdio.h>

// calculate CRC16 and add it to the end of the data
void addCRC16(uint8_t* data, uint8_t *dlen, const uint32_t pol)
{
    uint16_t reg = 0xFFFF;
    int i;

    for (i=0;i<*dlen;i++) {
        //uint8_t b = *data++;
        uint32_t crc_new = ((reg>>8)&0xFF)|(reg<<8);
        crc_new ^= *data++;
        crc_new ^= (crc_new&0xFF)>>4;
        crc_new ^= crc_new<<12;
        crc_new ^= (crc_new&0xFF)<<5;
        reg = crc_new;

        /*uint8_t ctr,temp;
        uint8_t in = *data++;

        for (ctr=8;ctr>0;--ctr) {
            temp = in ^ (uint8_t)reg;
            reg >>= 1;
            if (temp&0x01)
                reg^=0x1021;
            in >>= 1;
            printf("%3d: 0x%04X\n\r",cnt++,reg&0xFFFF);
        }*/
        //reg |= *data++;
        /*uint8_t b = *data++;
        for (j=0;j<8;j++)
        {
            reg <<= 1;
            if (b&0x80)
                reg|=0x1;
            b <<= 1;
            if ((reg&0x8000)!=0)
                reg ^= pol;*/
            //printf("%3d: 0x%04X\n\r",cnt++,reg&0xFFFF);
        //}
    }
    //reg ^= pol;
    /*for (i=0;i<8;i++)
    {
        reg <<= 1;
        if ((reg&0x8000)!=0)
            reg ^= pol;
        printf("%3d: 0x%04X\n\r",cnt++,reg&0xFFFF);
    }

    //reg >>= 8;*/

    *data++ = (uint8_t)reg;
    reg >>= 8;
    *data++ = (uint8_t)reg;
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
