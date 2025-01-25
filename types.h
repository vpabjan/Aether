#ifndef AE_TYPES_H
#define AE_TYPES_H
#include <stdint.h>
// A virtual machine instance i guess?
typedef struct vmInstance {
    uint8_t* stack;
    uint8_t* heap;
    int32_t stackSize;
    int32_t heapSize;
    int32_t stackPtr;
    uint8_t* bytecode;
    int32_t bytecodeSize;
    int32_t bytecodePtr;
} vmInstance;
#endif