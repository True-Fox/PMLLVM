// main.c
#include "headers/vm.h"

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
    return 0;
}
