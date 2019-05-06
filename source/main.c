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
    printf("Version:        $%04x\n", t->version);
    printf("maxEntries:     %d\n", t->maxEntries);
    printf("usedEntries:    %d\n", t->usedEntries);
    printf("Name:           %s\n", t->name);
    printf("\n");
    for (int i = 0; i < t->usedEntries; i++) {
        printf("Entry %02d:     %s\n", i, t->entries[i].name);
        printf("   typec64s     $%02x\n", t->entries[i].filetypec64s);
        printf("   typec1541    $%02x\n", t->entries[i].filetype1541);
        printf("   load         $%04x\n", t->entries[i].load);
        printf("   end          $%04x\n", t->entries[i].end);
        printf("   offset       $%08x\n", t->entries[i].offset);
        printf("\n");
    }

    return 0;
}