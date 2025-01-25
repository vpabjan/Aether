#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "types.h"
#include "aevm.h"




int main(int agrc, char* argv[]) {
    vmInstance* hi = malloc(sizeof(vmInstance));
    // Placeholder
    uint8_t testing[] = {0x60, 0x00, 0x00, 0x00, 0x04, 0x60, 0x00, 0x00, 0x00, 0x05, 0x64, 0x60};
    if (!hi) {
        printf("Couldn't allocate memory for vmInstance.");
        exit(EXIT_FAILURE);
    }
    hi->bytecode = testing;
    hi->stackSize = 64;
    hi->heapSize = 64;
    hi->stackPtr = 0;
    hi->stack = (uint8_t*)malloc(hi->stackSize);
    if (!hi->stack) {
        printf("Couldn't allocate %d bytes for stack.", hi->stackSize);
        exit(EXIT_FAILURE);
    }
    if (!hi->heap) {
        printf("Couldn't allocate %d bytes for heap", hi->heapSize);
        exit(EXIT_FAILURE);
    }
EXIT:
    free(hi->stack);
    free(hi->heap);
    free(hi);
    return 0;
}