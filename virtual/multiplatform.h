#include "../types.h"

// prints a table of the entire stack's byte values
void vmp_debug_printStack(vmInstance* vmI) {
    printf("Stack memory: \n");
    for (int n = 0; n < vmI->stackSize / 16; n++) {
        printf("%08X: ");
        for (int m = 0; m < 16; m++) {
            printf("%02x ", *(vmI->stack + n*16 + m));
        }
        printf("\n");
    }
}

// prints a table of the entire heap's byte values
void vmp_debug_printHeap(vmInstance* vmI) {
    printf("Heap memory: \n");
    for (int n = 0; n < vmI->heapSize / 16; n++) {
        printf("%08X: ");
        for (int m = 0; m < 16; m++) {
            printf("%02x ", *(vmI->heap + n*16 + m));
        }
        printf("\n");
    }
}

void vmp_intout(vmInstance* vmI) {
    printf("%d", *(int*)(vmI->stack + vmI->stackPtr - 4));
}