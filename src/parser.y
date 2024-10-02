%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"
#include "../include/emit.h"
#include "../include/symbol_table.h"


extern int yylex();
extern int yyparse();
void yyerror(const char* s);
%}

%union {
    int num;    
    char* id;  
}

%token <id> ID
%token <num> NUMBER
%token LET ASSIGN PLUS SEMICOLON PRINT  

%type <num> expr
%type <id> statement
%type <id> program

%%

program:
    program statement SEMICOLON { $$ = $2; }
    | /* empty */ { $$ = NULL; }
    ;

statement:
    LET ID ASSIGN expr {
        // printf("ID: %s\n", $2);
        int address = lookup_var($2);
        emit(PSH, $4);
        emit(ST, address);
        $$ = $2;
    }
    | PRINT expr {  
        emit(PSH, $2);  
        emit(ST, STDOUT_ADDRESS); 
    }
    ;

expr:
    NUMBER {
        $$ = $1;
    }
    | expr PLUS expr {
        emit(PSH, $1);
        emit(PSH, $3);
        emit(ADD, PLACE_HOLDER);
        $$ = $1 + $3;
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
