#include "include/vm.h"
#include "include/program.h"

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

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
    return 0;
}
