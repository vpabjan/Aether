#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "definitions.h"


// IF GOD DOESNT EXIST, THIS COULDNT EXIST
#define BINARY_OPERATION(vmI, operation, len) \
    do { \ 
        int a = *(int*)(vmI->stack + vmI->stackPtr - len) operation *(int*)(vmI->stack + vmI->stackPtr - 2 * len); \
        vmI->stackPtr-=len; \
        pushBytes(vmI->stack, &vmI->stackPtr, (uint8_t*)&a, len); \
    } while (0)

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
};

// Pushes 'length' bytes onto 'stack' copying 'length' bytes from 'bytes' and raising *'stackPtr' by 'length'
static inline void pushBytes(uint8_t* stack, int32_t* stackPtr, uint8_t* bytes, int32_t length) {
    memcpy(stack + *stackPtr, bytes, length);
    *stackPtr+=length;
}

void runInstance(vmInstance* vmI) {
    while (vmI->bytecodePtr < vmI->bytecodeSize) {
        uint8_t opcode = vmI->bytecode[vmI->bytecodePtr];
        switch (opcode) {
            case push32:
                vmI->bytecodePtr++;
                pushBytes(vmI->stack, &vmI->stackPtr, vmI->bytecode + vmI->bytecodePtr, 4);
                //memcpy(&vmI->stack[vmI->stackPtr], &vmI->bytecode[vmI->bytecodePtr], 4);
                //vmI->stackPtr+=4;
                vmI->bytecodePtr+=4;
                break;
            case binop:
                switch (vmI->bytecode[(++vmI->bytecodePtr)]) {
                    case binop_int32_add:
                        BINARY_OPERATION(vmI, +, 4);
                        break;
                    case binop_int32_sub:
                        BINARY_OPERATION(vmI, -, 4);
                        break;
                }
                break;
        }
        vmI->bytecodePtr++;
    }
}