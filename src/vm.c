// vm.c
#include "../headers/vm.h"
#include <stdio.h>

int registers[NUM_REG] = {0};
int stack[256] = {0};
bool running = true;

const int program[] = {
    PSH, 8,
    PSH, 3,
    ADD,
    PSH, 2,
    MUL,
    PSH, 4,
    MOD,
    PSH, 1,
    AND,
    NOT,
    PSH, 3,
    OR,
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
        case NOP:{
            ip++;
            break;
        } //NOP
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
        case SUB:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = b - a;
                sp++;
                stack[sp] = result;
            } else {
                printf("Not enough values on stack to perform SUB\n");
                running = false;
            }
            break;
        }
        case MUL:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = b * a;
                sp++;
                stack[sp] = result;
            } else {
                printf("Not enough values on stack to perform MUL\n");
            }
            break;
        }
        case DIV:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                if(a == 0){
                    printf("Division by zero\n");
                    running = false;
                } else {  
                    int result = b / a;
                    sp++;
                    stack[sp] = result;
                }
            } else {
                printf("Not enough values on stack to perform DIV\n");
            }
            break;
        }
        case MOD:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = b % a;
                sp++;
                stack[sp] = result;
            } else {
                printf("Not enough values on stack to perform MOD\n");
            }
            break;
        }
        case AND:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = a & b;
                sp++;
                stack[sp] = result;
            } else {
                printf("Not enough values to perform AND\n");
                running = false;
            }
            break;
        }
        case OR:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = a | b;
                sp++;
                stack[sp] = result;
            } else {
                printf("Not enough values on stack to perform OR\n");
                running = false;
            }
            break;
        }
        case NOT:{
            if(sp >= 0){
                int a = stack[sp--];
                int result = !a;
                sp++;
                stack[sp] = result;
            } else {
                printf("Not enough values on stack to perform NOT\n");
                running = false;
            }
            break;
        }
    }
}
