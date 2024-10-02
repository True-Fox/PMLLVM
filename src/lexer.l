%{
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/utils.h"
#include "y.tab.h"

extern YYSTYPE yylval;
%}

%%

"let"           { return LET; }
"print"         { return PRINT; }
[a-zA-Z][a-zA-Z0-9]*  { 
        if(yytext==NULL){
            // printf("Yytext is NULL\n");
            exit(1);
        }
        // printf("%s\n",yytext);
        yylval.id = my_strdup(yytext); 
        // printf("yylval=%s\n", yylval.id);
        return ID; 
    } 
[0-9]+          { yylval.num = atoi(yytext); return NUMBER; }
"="             { return ASSIGN; }
"+"             { return PLUS; }
";"             { return SEMICOLON; }

[ \t\n]+        ;  // Ignore whitespace

.               { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
