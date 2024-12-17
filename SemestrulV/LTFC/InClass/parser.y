%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex(); //analiza lexicala
extern int yyparse(); //analiza sintactica
extern FILE *yyin;

void yyerror(const char *s) {
    fprintf(stderr, "Eroare: %s\n", s);
}
%}

%token VALID_TIME INVALID_TIME

%%

program:
    valid_time
    | invalid_time
    ;

valid_time:
    VALID_TIME {
        printf("valid + palindrom");
    }
    ;

invalid_time:
    INVALID_TIME {
        printf("invalid / nepalindrom");
    }
    ;

%%

int main(int argc, char **argv) {
    yyin = fopen("input.txt", "r");

    yyparse();
    fclose(yyin);

    return 0;
}
