// vm.h
#ifndef VM_H
#define VM_H

#include <stdbool.h>
#include "program.h"

#define sp (registers[SP])
#define ip (registers[IP])

// Registers enumeration
typedef enum {
    A, B, C, D, E, F, IP, SP,
    NUM_REG
} REGISTERS;

// Instruction set enumeration
typedef enum {
    PSH, ADD,
    SUB, MUL,
    DIV, MOD,
    POP, SET,
    AND, OR,
    NOT, 
    HLT, NOP
} INST_SET;

// Global variables
extern int registers[NUM_REG];
extern int stack[256];
extern bool running;

// Function declarations
int fetch();
void eval(int instr);

#endif // VM_H
