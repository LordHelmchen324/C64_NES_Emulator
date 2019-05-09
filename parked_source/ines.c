#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

#include "ines.h"

iNES* loadiNES(char* path) {
    uint8_t* buffer = fileToBuffer(path);
    if (buffer == NULL) return NULL;
    int bc = 0;

    iNES* ines = (iNES*) malloc(sizeof(iNES));

    // Header
    uint8_t* header = buffer;
    memcpy(ines->signature, header, 4);
    ines->prgsize = header[4];
    ines->chrsize = header[5];
    ines->mirroring = header[6] & 0b00000001;
    ines->hasprgram = (header[6] & 0b00000010) >> 1;
    ines->hastrainer = (header[6] & 0b00000100) >> 2;
    ines->ignoremirroring = (header[6] & 0b00001000) >> 3;
    ines->mapper = (header[7] & 0b11110000) | ((header[6] & 0b11110000) >> 4);
    ines->isvsunisystem = header[7] & 0b00000001;
    ines->haspc10 = (header[7] & 0b00000010) >> 1;
    ines->isnes2 = (header[7] & 0b00000100) >> 2;
    bc += 16;

    // Trainer
    if (ines->hastrainer) {
        ines->trainer = (uint8_t*) malloc(512);
        memcpy(ines->trainer, &buffer[bc], 512);
        bc += 512;
    } else
        ines->trainer = NULL;
    
    // PRG ROM
    ines->prg = (uint8_t*) malloc(ines->prgsize * 16384);
    memcpy(ines->prg, &buffer[bc], ines->prgsize * 16384);
    bc += ines->prgsize;

    // CHR ROM
    if (ines->chrsize > 0) {
        ines->chr = (uint8_t*) malloc(ines->chrsize * 8192);
        memcpy(ines->chr, &buffer[bc], ines->chrsize * 8192);
        bc += ines->chrsize;
    } else
        ines->chr = NULL;

    // PlayChoice INST-ROM and PROM
    ines->pcir = NULL;
    ines->pcpr = NULL;

    free(buffer);

    return ines;
}

void printiNESInfo(iNES* ines) {
    printf("\n");

    printf("########################################\n");
    printf("signature:       %s\n", ines->signature);
    printf("prgsize:         %u * 16384 = %u\n", ines->prgsize, ines->prgsize * 16384);
    printf("chrsize:         %u * 8192 = %u\n", ines->chrsize, ines->chrsize * 8192);
    printf("mirroring:       %u\n", ines->mirroring);
    printf("hasprgram:       %u\n", ines->hasprgram);
    printf("hastrainer:      %u\n", ines->hastrainer);
    printf("ignoremirroring: %u\n", ines->ignoremirroring);
    printf("mapper:          $%02x\n", ines->mapper);
    printf("isvsunisystem:   %u\n", ines->isvsunisystem);
    printf("haspc10:         %u\n", ines->haspc10);
    printf("isnes2:          %u\n", ines->isnes2);
    printf("prg:            ");
    for (int i = 0; i < 5; i++)
        printf(" $%02x", ines->prg[i]);
    printf(" ...\n");
    printf("chr:            ");
    if (ines->chr != 0) {
        for (int i = 0; i < 5; i++)
            printf(" $%02x", ines->chr[i]);
        printf(" ...\n");
    } else
        printf(" NULL\n");
    
    printf("########################################\n");

    printf("\n");
}