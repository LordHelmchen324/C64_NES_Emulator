#include <stdio.h>
#include <stdlib.h>
#include "t64.h"

int main(int argc, char* argv[]) {
    T64Tape* t = loadT64Tape(argv[1]);
    if (t == NULL) {
        printf("ERROR: Could not load file %s\n", argv[1]);
        exit(1);
    }

    printf("Signature:      %s\n", t->signature);
    printf("Version:        %04x\n", t->version);
    printf("maxEntries:     %d\n", t->maxEntries);
    printf("usedEntries:    %d\n", t->usedEntries);
    printf("Name:           %s\n", t->name);

    return 0;
}