//
//  main.c
//  DVB204TO188
//
//  Created by Roland PILOTTE on 14/12/11.
//  Copyright (c) 2011 Pilotte.eu. 
//  All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int32_t NumberOfPackets=0;

struct DVB_packet
{
    char Header;
    char Payload[187];
};

struct ReedSolomon
{
    char CRC[16];
};

int main (int argc, const char * argv[])
{
    FILE* inputfile= NULL;
    FILE* outputfile= NULL;
    struct DVB_packet CurrentPacket;
    struct ReedSolomon CurrentCRC;
    if (argc!=3)
    {
        printf("You need to specify 2 arguments \n");
        printf("DVB204TO188 input_file output_file\n");
        return 2;
    }
    inputfile = fopen (argv[1], "rb");
    if (inputfile == NULL)
    {
        printf("Impossible to open %s \n", argv[1]);
        return 1;
    }
    else
    {
        //printf("File %s opened \n", argv[1]);
        outputfile = fopen (argv[2], "wb+");
        while (feof(inputfile) == 0)
        {
            fread(&CurrentPacket, 188, 1, inputfile);
            //numberofreadbytes += 188;
            fread(&CurrentCRC, 16, 1, inputfile);
            //numberofreadbytes += 16;
            //numberofreadbytes=0;
            NumberOfPackets++;
            printf ("*");
            if (CurrentPacket.Header!=0x47)
            {
                printf("Sync byte not found in 204 format at packet %d.\n", NumberOfPackets);
                printf("Aborting\n");
                return 3;
            }
            fwrite(&CurrentPacket, 188, 1, outputfile);
        }
        //printf("Number of read bytes %d\n", numberofreadbytes);
        printf ("\n");
        printf ("%d Packets Processed successfully \n", NumberOfPackets);
        fclose (inputfile);
        fclose (outputfile);
        return 0;
    }
}

