/**
 * crc16 module test programm
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <inttypes.h>

#include "crc16.h"

// max data length (including 2b CRC)
#define MAX_DLEN 128

// test crc generative polynom (default)
#define CRC_POL 0x8005

int main(int argc, char *argv[])
{
    // test data
    uint8_t dlen;
    uint8_t data[MAX_DLEN];
    uint32_t pol = CRC_POL<<8;
    bool poledit = false;
    bool checkcrc = false;

    if (argc>1)
    {
        int i;
        for (i=1;i<argc;i++)
        {
            if (strcmp(argv[i],"-c")==0) checkcrc = true;
            else if (strncmp(argv[i],"-p",2)==0) {
                if (sscanf(&argv[i][2],"%X",&pol)!=1) {
                    printf("Polynomial input error !!!\n");
                    return(-1);
                }
                pol<<=8;
                poledit=true;
            }
            else if ((strcmp(argv[i],"-d")==0)&&(i<(argc-1))) {
                dlen=0;
                for (i++;i<argc;i++)
                {
                    int dt;
                    if (sscanf(argv[i],"%02X",&dt)!=1) // XX hexa form
                    {
                        // not known data form - return error
                        printf("Data input error !!!\n");
                        return(-1);
                    }
                    data[dlen++]=dt;
                }
            }
        }
    }
    else
    {
        // no params - print usage
        printf("\nCRC16 test programm\n\n  Params:\n\n    -c .. check crc\n    -d [d0 d1 .. dN] .. data\n");
        printf("\n  Usage:\n\n    Add CRC to data polynom:\n      crc -d 78 9A BC\n\n");
        printf("    Test CRC in data polynom:\n      crc -c -d 12 34 EC BB\n\n");
        return(0);
    }

    // input printout
    uint8_t i;
    printf("Data input (hex):\n");
    for (i=0;i<dlen;i++)
        printf("%02X%s",data[i],(i!=(dlen-1))?(" "):("\n"));
    if (poledit)
        printf("Polynomial (hex): %04X\n",pol>>8);

    // result printout
    if (checkcrc==true)
    {
        // crc test function
        printf("CRC %s\r\n\n",testCRC16(data,dlen,pol)?"OK":"ERROR");
    }
    else
    {
        // add crc at the end of data array
        addCRC16(data,&dlen,pol);
        printf("Data with CRC (hex):\n");
        for (i=0;i<dlen;i++) printf("%02X%s",data[i],(i!=(dlen-1))?(" "):("\n"));
    }

    return 0;
}
