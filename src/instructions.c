// Instructions.c
#include "../include/vm.h"
#include <stdio.h>

void halt() {
    running = false;
}

void nop(){
    ip++;
}


void push() {
    if (sp < 255) {
        sp++;
        stack[sp] = program[++ip];
    } else {
        printf("Stack overflow!\n");
        running = false;
    }
}

void pop() {
    if (sp >= 0) {
        int val = stack[sp--];
        printf("Popped %d\n", val);
    } else {
        printf("Stack underflow!\n");
        running = false;
    }
}

void add() {
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
}

void sub() {
    if (sp >= 1) {
        int a = stack[sp--];
        int b = stack[sp--];
        int result = b - a;
        sp++;
        stack[sp] = result;
    } else {
        printf("Not enough values on stack to perform SUB\n");
        running = false;
    }
}

void mul() {
    if (sp >= 1) {
        int a = stack[sp--];
        int b = stack[sp--];
        int result = b * a;
        sp++;
        stack[sp] = result;
    } else {
        printf("Not enough values on stack to perform MUL\n");
    }
}

void divide() {
    if (sp >= 1) {
        int a = stack[sp--];
        int b = stack[sp--];
        if (a == 0) {
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
}

void mod() {
    if (sp >= 1) {
        int a = stack[sp--];
        int b = stack[sp--];
        int result = b % a;
        sp++;
        stack[sp] = result;
    } else {
        printf("Not enough values on stack to perform MOD\n");
    }
}

void and_op() {
    if (sp >= 1) {
        int a = stack[sp--];
        int b = stack[sp--];
        int result = a & b;
        sp++;
        stack[sp] = result;
    } else {
        printf("Not enough values on stack to perform AND\n");
        running = false;
    }
}

void or_op() {
    if (sp >= 1) {
        int a = stack[sp--];
        int b = stack[sp--];
        int result = a | b;
        sp++;
        stack[sp] = result;
    } else {
        printf("Not enough values on stack to perform OR\n");
        running = false;
    }
}

void not_op() {
    if (sp >= 0) {
        int a = stack[sp--]; 
        sp++;
        stack[sp] = ~a;
    } else {
        printf("Not enough values on stack to perform NOT\n");
        running = false;
    }
}

void load(){
    int address = program[++ip];
    if(address >= 0 && address < MEM_SIZE){
        int value = memory[address];
        sp++;
        stack[sp] = value;
    }else{
        printf("Memory out of bounds!\n");
        running = false;
    }
}

void store(){
    int address = program[++ip];
    if(address>=0 && address < MEM_SIZE){
        int value = stack[sp--];
        memory[address] = value;

        if (address == STDOUT_ADDRESS){
            printf("Output: %d\n", value);
        }

    }else{
        printf("Memory Write Error\n");
        running = false;
    }
}