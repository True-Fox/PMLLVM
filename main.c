#include "include/vm.h"
#include "include/program.h"
#include <stdio.h>

const int program[] = {
    PSH, 10,
    ST, 0,
    PSH, 20,
    ST, 1, 
    LD, 0,
    LD, 1,
    ADD,
    POP,
    HLT
};


int main() {
    int count = 0;
    while (running) {
        printf("cycle %d\n", count++);
        eval(fetch());
        ip++;
    }
    return 0;
}
