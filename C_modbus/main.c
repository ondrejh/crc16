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
#include <stdbool.h>
#include <string.h>

#include "crc16.h"

#define DATALEN_MAX 256

int main(int argc, char *argv[])
{
    uint8_t puchMsg[DATALEN_MAX];
    uint8_t usDataLen = 0;
    bool crc_check = false;

    int i;
    for (i=1;i<argc;i++) {
        // test "check" command
        if (strcmp(argv[i],"-c")==0)
            crc_check = true;
        // test data length
        else if (usDataLen>=DATALEN_MAX) {
            perror("ERROR: Maximum data length exceed !!!\n");
            return -1;
        }
        // next byte input
        else if (sscanf(argv[i],"%02X",(unsigned int *)&puchMsg[usDataLen++])!=1) {
            perror("ERROR: Data input error !!!\n");
            return -1;
        }
    }

    if (crc_check&&(usDataLen<2)) {
        perror("ERROR: too short message to check crc !!!\n");
        return -1;
    }

    // if no data show help
    if (usDataLen==0) {
        printf("Modbus CRC calculation program\n\n");
        printf("  Author:   ondrejh.ck@email.cz\n");
        printf("  Compiled: %s %s\n\n",__TIME__,__DATE__);
        printf("  Usage:    crc16 12 34 45 XX .. to calculate crc\n");
        printf("            crc16 -c 12 34 56 .. to check crc\n");
        printf("  Return:   0 .. success, -1 .. input error\n");
        printf("  Output:   16 bit CRC (hex), PASS or FAIL (str)\n\n");
        return -1;
    }

    uint16_t crc;
    if (crc_check) {
        crc = CRC16(puchMsg,usDataLen-2);
        printf((((crc>>8)==puchMsg[usDataLen-2])&&((crc&0xFF)==puchMsg[usDataLen-1]))?"PASS\n":"FAIL\n");
    } else {
        crc = CRC16(puchMsg,usDataLen);
        printf("%04X\n",crc);
    }
    return 0;
}
