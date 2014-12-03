/**
 * modbus crc16 calculation
 *
 * This is based on example from the Modbus specification supplied by
 * the Modbus Organisation (www.modbus.org).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "crc16.h"

#define DATALEN_MAX 256

int main(int argc, char *argv[])
{
    uint8_t puchMsg[DATALEN_MAX];
    uint8_t usDataLen = 0;

    int i;
    for (i=1;i<argc;i++) {
        // test data length
        if (usDataLen>=DATALEN_MAX) {
            perror("Maximum data length exceed !!!\n");
            return -1;
        }
        // next byte input
        if (sscanf(argv[i],"%02X",(unsigned int *)&puchMsg[usDataLen++])!=1) {
            perror("Data input error !!!\n");
            return -1;
        }
    }

    // if no data show help
    if (usDataLen==0) {
        printf("Modbus CRC calculation program\n\n");
        printf("  Author:   ondrejh.ck@email.cz\n");
        printf("  Compiled: %s %s\n\n",__TIME__,__DATE__);
        printf("  Usage:    crc16 12 34 45 XX ..\n");
        printf("  Return:   0 .. success, 1 .. input error\n");
        printf("  Output:   16 bit CRC (hex)\n\n");
        return -1;
    }

    uint16_t crc = CRC16(puchMsg,usDataLen);
    printf("%04X\n",crc);
    return 0;
}
