%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex(); //analiza lexicala
extern int yyparse(); //analiza sintactica
extern FILE *yyin;

extern int currentLine;

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s at line %d\n", s, currentLine);
}
%}

//tokenuri simboluri terminale
%token INT MAIN CIN WHILE COUT ELSE IF
%token IDENTIFIER CONSTANT
%token ASSIGN EQ NEQ LT GT PLUS MINUS
%token SEMICOLON LPAREN RPAREN LBRACE RBRACE
%token SHR SHL

//prec + asoc operatori
%left PLUS MINUS
%left EQ NEQ LT GT
%nonassoc IFX
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%debug

%%

//main + bloc instr
program:
    MAIN LPAREN RPAREN LBRACE stmt_list RBRACE
    ;

//gol/secv instr
stmt_list:
    /* empty */
    | stmt_list stmt
    ;


stmt:
    declaration SEMICOLON //int a
    | assignment SEMICOLON //a=12;
    | input SEMICOLON //citire
    | output SEMICOLON //afisare
    | if_stmt
    | while_stmt
    | LBRACE stmt_list RBRACE //bloc instr
    ;

declaration:
    INT IDENTIFIER
    ;

assignment:
    IDENTIFIER ASSIGN expr
    ;

expr:
    CONSTANT //const num
    | IDENTIFIER // var
    | expr PLUS expr //adunare
    | expr MINUS expr //scadenre
    | LPAREN expr RPAREN //grupare op cu paranteze
    ;

input:
    CIN SHR IDENTIFIER //op citire
    ;

output:
    COUT SHL expr //afisare
    ;


//instr if fara else
//%prec LOWER_THAN_ELSE => conflicte shift/reduce
if_stmt:
    IF LPAREN condition RPAREN stmt %prec IFX
    | IF LPAREN condition RPAREN stmt ELSE stmt
    ;

while_stmt:
    WHILE LPAREN condition RPAREN stmt
    ;

condition:
    expr EQ expr //=
    | expr NEQ expr //!=
    | expr LT expr //<
    | expr GT expr //>
    ;

%%

int currentLine = 1;
int main(int argc, char **argv) {
    yyin = fopen("input.txt", "r");

    yyparse();
    fclose(yyin);

    return 0;
}
