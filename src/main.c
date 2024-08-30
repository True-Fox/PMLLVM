#include <stdio.h>
#include <stdbool.h>

#define sp (registers[SP])
#define ip (registers[IP])

typedef enum {
    A, B, C, D, E, F, IP, SP,
    NUM_REG
} REGISTERS;

int registers[NUM_REG];

int stack[256];
bool running = true;

typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} INST_SET;

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
};

int fetch() {
    return program[ip];
}

void eval(int instr) {
    switch(instr) {
        case HLT: {
            running = false;
            break;
        }
        case PSH: {
            if (sp < 255) {
                sp++;
                stack[sp] = program[++ip];
            } else {
                printf("Stack overflow!\n");
                running = false;
            }
            break;
        }
        case POP: {
            if (sp >= 0) {
                int val = stack[sp--];
                printf("Popped %d\n", val);
            } else {
                printf("Stack underflow!\n");
                running = false;
            }
            break;
        }
        case ADD: {
            if (sp >= 1) {
                int a = stack[sp--];
                int b = stack[sp--];
                int result = b + a;
                sp++;
                stack[sp] = result;
            } else {
                printf("Not enough values on stack to perform ADD\n");
                running = false;
            }
            break;
        }
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
    return 0;
}

