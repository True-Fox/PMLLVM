// vm.h
#ifndef VM_H
#define VM_H

#define MEM_SIZE 1024

#include <stdbool.h>
#include <stdlib.h>
#include "program.h"

#define STDOUT_ADDRESS 512
#define PLACE_HOLDER 0
#define sp (registers[SP])
#define ip (registers[IP])

// Registers enumeration
typedef enum {
    A, B, C, D, E, F, IP, SP,
    NUM_REG
} REGISTERS;

// Instruction set enumeration
typedef enum {
    PSH, ADD, SUB, MUL,
    DIV, MOD, POP, SET,
    AND, OR, NOT,
    LD, ST, HLT, NOP
} INST_SET;

// Global variables
extern int registers[NUM_REG];
extern int memory[MEM_SIZE];
extern int stack[256];
extern bool running;

// Function declarations
int fetch();
void eval(unsigned long int instr);

#endif // VM_H
