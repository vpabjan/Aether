#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "definitions.h"
#include "virtual/multiplatform.h"
#include "types.h"


// IF GOD DOESNT EXIST, THIS COULDNT EXIST
#define BINARY_OPERATION(vmI, operation, len) \
    do { \ 
        int a = *(int*)(vmI->stack + vmI->stackPtr - len) operation *(int*)(vmI->stack + vmI->stackPtr - 2 * len); \
        vmI->stackPtr-=2*len; \
        pushBytes(vmI->stack, &vmI->stackPtr, (uint8_t*)&a, len); \
    } while (0)



// Pushes 'length' bytes onto 'stack' copying 'length' bytes from 'bytes' and raising *'stackPtr' by 'length'
static inline void pushBytes(uint8_t* stack, int32_t* stackPtr, uint8_t* bytes, int32_t length) {
    memcpy(stack + *stackPtr, bytes, length);
    *stackPtr+=length; // NO CHECKING FOR STACK UNDERFLOWS, what are we? OSHA???
}

void runInstance(vmInstance* vmI) {
    uint8_t zero[] = {0x00, 0x00, 0x00, 0x00}; // silly hack
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
                    case binop_int32_mul:
                        BINARY_OPERATION(vmI, *, 4);
                        break;
                    case binop_int32_div:
                        if (*(int*)(vmI->stack + vmI->stackPtr - 4) != 0) {
                            BINARY_OPERATION(vmI, /, 4);
                        } else {
                            vmI->stackPtr-=8;
                            pushBytes(vmI->stack, &vmI->stackPtr, (uint8_t*)*zero, 4); // silly hack
                        }
                        break;
                }
                break;
            case dup:
                vmI->bytecodePtr++;
                int COUNTER = vmI->bytecode[vmI->bytecodePtr];
                for (int n = 0; n < COUNTER; n++) {
                    pushBytes(vmI->stack, &vmI->stackPtr, vmI->stack - n, n);
                }
                break;
            case virtual:

                break;
        }
        vmI->bytecodePtr++;
    }
}