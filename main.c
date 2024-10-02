#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

extern int yyparse(); // Declaration of the parser
extern FILE *yyin;    // Input file for the lexer

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    // Start parsing
    if (yyparse() == 0) {
        printf("Parsing completed successfully.\n");
    } else {
        printf("Parsing failed.\n");
    }

    fclose(yyin);
    return 0;
}
