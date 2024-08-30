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
    PSH, ADD,
    SUB, MUL,
    DIV, MOD,
    POP, SET,
    AND, OR,
    NOT,
    HLT
} INST_SET;

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
        //Machine Control Instructions
        case HLT: {
            running = false;
            break;
        }
        //Stack Instructions
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
        //Arithmetic Instructions
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
        }// ADD
        case SUB:{
            if(sp>=1){
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
        }// SUB
        case MUL:{
                if(sp>=1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = b * a;
                sp++;
                stack[sp] = result;
                } else {
                printf("Not enough values on stack to perform MUL\n");
                }
                break;
        }// MUL 
        case DIV:{
                if(sp>=1){
                int a = stack[sp--];
                int b = stack[sp--];
                if(a==0){
                    printf("Division by zero\n");
                    running = false;
                }else{  
                    int result = b/a;
                    sp++;
                    stack[sp] = result;
                }              
                } else {
                printf("Not enough values on stack to perform DIV\n");
                }
                break;
        }//DIV
        case MOD:{
                if(sp>=1){
                    int a = stack[sp--];
                    int b = stack[sp--];
                    int result = b%a;
                    sp++;
                    stack[sp] = result;
                } else {
                    printf("Not enough values on stack to perform MOD\n");
                }
                break;
        }//MOD
        //Logical Instructions
        case AND:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = a&b;
                sp++;
                stack[sp] = result;
            }else{
                printf("Not enough values to perform AND\n");
                running = false;
            }
            break;
        }//AND
        case OR:{
            if(sp >= 1){
                int a = stack[sp--];
                int b = stack[sp--];
                int result = a|b;
                sp++;
                stack[sp] = result;
            }else{
                printf("Not enough values on stack to perform OR\n");
                running = false;
            }
            break;
        }//OR
        case NOT:{
            if(sp>=1){
                int a = stack[sp--];
                int result = !a;
                sp++;
                stack[sp] = result;
            }else{
                printf("Not enough values on stack to perform NOT");
                running = false;
            }
            break;
        }
    } // SWITCH
} //EVAL

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
    return 0;
}

