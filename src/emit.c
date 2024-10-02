#include "../include/emit.h"
#include "../include/vm.h"

int program_counter = 0;

void emit(int instruction, int operand) {
    if (program_counter < MAX_PROGRAM_SIZE - 1) {
        program[program_counter++] = instruction;  // Add the instruction
        program[program_counter++] = operand;      // Add the operand
    } else {
        printf("Error: Program size exceeded!\n");
        running = false;
    }
}
