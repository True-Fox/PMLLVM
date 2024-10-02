#include "symbol_table.h"
#include <stdio.h>
#include <string.h>

#define MAX_VARS 256
#define MAX_VAR_NAME 32

typedef struct {
    char name[MAX_VAR_NAME];
    int address;
} Variable;

Variable symbol_table[MAX_VARS];
int var_count = 0;

int lookup_var(char* var_name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(symbol_table[i].name, var_name) == 0) {
            return symbol_table[i].address;  
        }
    }

    if (var_count < MAX_VARS) {
        // printf("I am here 1\n");
        // printf("Var_name: %s", var_name);
        // printf("I am here 1.5\n");
        strcpy(symbol_table[var_count].name, var_name);
        symbol_table[var_count].address = var_count;
        // printf("I am here 2\n");
        return var_count++;  
    } else {
        printf("Error: Too many variables!\n");
        return -1;
    }
}
