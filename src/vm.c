// vm.c
#include "../include/vm.h"
#include "../include/instructions.h"
#include <stdio.h>

typedef void (*InstructionHandler)();

int memory[MEM_SIZE];
int registers[NUM_REG] = {0};
int stack[256] = {0};
int program[MAX_PROGRAM_SIZE] = {0};
bool running = true;

InstructionHandler instruction_table[] = {
    [HLT] = halt,
    [NOP] = nop,
    [PSH] = push,
    [POP] = pop,
    [ADD] = add,
    [SUB] = sub,
    [MUL] = mul,
    [DIV] = divide,
    [MOD] = mod,
    [AND] = and_op,
    [OR] = or_op,
    [NOT] = not_op,
    [LD] = load,
    [ST] = store,
};

int fetch() {
    return program[ip];
}

void eval( unsigned long int instr) {
    if (instr < sizeof(instruction_table) / sizeof(InstructionHandler)) {
        InstructionHandler handler = instruction_table[instr];
        if (handler) {
            handler();
        } else {
            printf("Unknown instruction: %lu\n", instr);
            running = false;
        }
    } else {
        printf("Invalid instruction code: %lu\n", instr);
        running = false;
    }
}
