%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int currentLine;
void yyerror();

FILE* outputFile;
char* filename;

#define MAX 1000
char declarations[MAX][MAX], sourceCode[MAX][MAX], imports[MAX][MAX];
int lenDeclarations = 0, lenSourceCode = 0, lenImports = 0;

char variablesRead[MAX][MAX];
int n = 0, nr = 0;
char expressions[MAX][MAX];
int lenExpressions = 0;

bool found(char col[][MAX], int n, char* var);
void parseExpression(char* element);
void printDeclarationSegment();
void printCodeSegment();
void printImports();
%}

%union {
	char * value;
}

%token INCLUDE
%token NAMESPACE
%token ISTREAM
%token OSTREAM
%token DATA_TYPE
%token PLUS
%token MINUS
%token MUL
%token DIVIDE
%token ASSIGN
%token COMMA
%token SEMICOLON
%token LAQ
%token RAQ
%token SIN
%token SOUT
%token LPR
%token RPR
%token MAIN
%token RETURN
%token ID
%token CONST

%%

program: INCLUDE NAMESPACE DATA_TYPE MAIN LAQ declare_instruction code_block RAQ {
    printf("Program parsed successfully!\n");
}
;

declare_instruction: DATA_TYPE declaration
	;

declaration: ID SEMICOLON {
            char tmp[100];
			strcpy(tmp, " ");
			strcat(tmp, $<value>1);
			if (!found(declarations, lenDeclarations, tmp)) {
				strcpy(declarations[lenDeclarations], strcat(tmp, " times 4 db 0"));
				lenDeclarations++;
			}
        }
	| ID COMMA declaration {
            char tmp[100];
			strcpy(tmp, " ");
			strcat(tmp, $<value>1);
			if (!found(declarations, lenDeclarations, tmp)) {
				strcpy(declarations[lenDeclarations], strcat(tmp, " times 4 db 0"));
				lenDeclarations++;
			}
        }
    ;

code_block: instruction_list RETURN CONST SEMICOLON
	;

instruction_list: instruction
	| instruction instruction_list
	;

instruction: io_instruction
	| assign_instruction
	;

io_instruction: input_instruction
	| output_instruction
	;

input_instruction: ISTREAM SIN ID SEMICOLON {
        n = 0;
        strcpy(variablesRead[n], "push dword ");
        strcat(variablesRead[n], $<value>3);
        strcat(variablesRead[n], "\n\t\tpush dword format");
        strcat(variablesRead[n], "\n\t\tcall [scanf]");
        strcat(variablesRead[n], "\n\t\tadd ESP, 4 * 2\n");
        n++;
        if (!found(imports, lenImports, "scanf")) {
            strcpy(imports[lenImports], "scanf");
            lenImports++;
        }
        if (!found(declarations, lenDeclarations, "format")) {
            strcpy(declarations[lenDeclarations], " format db \"%d\", 0");
        }
        for (int i = n - 1; i >= 0; i--) {
            strcpy(sourceCode[lenSourceCode++], variablesRead[i]);
        }
    }
	;

output_instruction: OSTREAM SOUT ID SEMICOLON {
        if (!found(imports, lenImports, "printf")) {
            strcpy(imports[lenImports], "printf");
            lenImports++;
        }
        if (!found(declarations, lenDeclarations, "format")) {
            strcpy(declarations[lenDeclarations], " format db \"%d\", 0");
            lenDeclarations++;
        }
        strcpy(sourceCode[lenSourceCode], "push dword [");
        strcat(sourceCode[lenSourceCode], $<value>3);
        strcat(sourceCode[lenSourceCode++], "]");
        strcpy(sourceCode[lenSourceCode++], "push dword format");
        strcpy(sourceCode[lenSourceCode++], "call [printf]");
        strcpy(sourceCode[lenSourceCode++], "add ESP, 4 * 2\n");
    }
    | OSTREAM SOUT CONST SEMICOLON {
        if (!found(imports, lenImports, "printf")) {
            strcpy(imports[lenImports], "printf");
            lenImports++;
        }
        if (!found(declarations, lenDeclarations, "format")) {
            strcpy(declarations[lenDeclarations], " format db \"%d\", 0");
            lenDeclarations++;
        }
        strcpy(sourceCode[lenSourceCode], "push dword ");
        strcat(sourceCode[lenSourceCode++], $<value>3);
        strcpy(sourceCode[lenSourceCode++], "push dword format");
        strcpy(sourceCode[lenSourceCode++], "call [printf]");
        strcpy(sourceCode[lenSourceCode++], "add ESP, 4 * 2\n");
    }
	;

assign_instruction: ID ASSIGN operation SEMICOLON {
        char tmp[MAX];
        strcpy(tmp, $<value>3);
        char* token = strtok(tmp, " ");
        while (token != NULL) {
            strcpy(expressions[lenExpressions], token);
            lenExpressions++;
            token = strtok(NULL, " ");
        }
        parseExpression($<value>1);
    }
	;

operation: any
	| any operator operation {
        char tmp[MAX];
        strcpy(tmp, $<value>1);
        strcat(tmp, " ");
        strcat(tmp, $<value>2);
        strcat(tmp, " ");
        strcat(tmp, $<value>3);
        $<value>$ = strdup(tmp);
    }
	;

operator: PLUS
	| MINUS
	| MUL
	| DIVIDE
	;

any: ID
	| CONST
	;

%%

int main(int argc, char* argv[]) {
	FILE* f = NULL;
    if (argc > 1) {
        f = fopen(argv[1], "r");
    }
	if (!f) {
		perror("Could not open file! Switching to console...\n");
		yyin = stdin;
	} else {
		yyin = f;
	}
    strcpy(imports[lenImports++], "exit");
	while (!feof(yyin)) {
		yyparse();
	}
	printf("The file is sintactically correct!\n");
    outputFile = fopen("asmCode.asm", "w+");
    fprintf(outputFile, "bits 32\nglobal start\n\n");
    printImports();
    fprintf(outputFile, "segment data use32 class=data\n");
    printDeclarationSegment();
    fprintf(outputFile, "\nsegment code use32 class=code\n\tstart:\n");
    strcpy(sourceCode[lenSourceCode++], "push dword 0");
    strcpy(sourceCode[lenSourceCode++], "call [exit]");
    printCodeSegment();
	return 0;
}

void yyerror(const char* s) {
	extern char* yytext;
	printf("Error for symbol %s on line: %d\n", yytext, currentLine);
	exit(1);
}

void parseExpression(char* element) {
    char tempResult[MAX][MAX];  //rezultate intermediare
    int tempLen = 0;

    strcpy(tempResult[tempLen++], expressions[0]);

    // * si /
    for (int i = 1; i < lenExpressions - 1; i += 2) {
        if (strcmp(expressions[i], "*") == 0 || strcmp(expressions[i], "/") == 0) {
            if (isdigit(expressions[i-1][0])) {
                strcpy(sourceCode[lenSourceCode], "mov EAX, ");
                strcat(sourceCode[lenSourceCode++], expressions[i-1]);
            } else {
                strcpy(sourceCode[lenSourceCode], "mov EAX, dword [");
                strcat(sourceCode[lenSourceCode], expressions[i-1]);
                strcat(sourceCode[lenSourceCode++], "]");
            }

            if (strcmp(expressions[i], "*") == 0) {
                if (isdigit(expressions[i+1][0])) {
                    strcpy(sourceCode[lenSourceCode], "mov EBX, ");
                    strcat(sourceCode[lenSourceCode++], expressions[i+1]);
                    strcpy(sourceCode[lenSourceCode++], "imul EAX, EBX");
                } else {
                    strcpy(sourceCode[lenSourceCode], "imul EAX, dword [");
                    strcat(sourceCode[lenSourceCode], expressions[i+1]);
                    strcat(sourceCode[lenSourceCode++], "]");
                }
            } else { // pentru divizare
                if (isdigit(expressions[i+1][0])) {
                    strcpy(sourceCode[lenSourceCode], "mov EBX, ");
                    strcat(sourceCode[lenSourceCode++], expressions[i+1]);
                } else {
                    strcpy(sourceCode[lenSourceCode], "mov EBX, dword [");
                    strcat(sourceCode[lenSourceCode], expressions[i+1]);
                    strcat(sourceCode[lenSourceCode++], "]");
                }
                strcpy(sourceCode[lenSourceCode++], "cdq");
                strcpy(sourceCode[lenSourceCode++], "idiv EBX");
            }

            // rezultat in variabila temporara
            char tempVar[20];
            sprintf(tempVar, "temp%d", tempLen);
            strcpy(sourceCode[lenSourceCode], "mov dword [");
            strcat(sourceCode[lenSourceCode], tempVar);
            strcat(sourceCode[lenSourceCode++], "], EAX");

            // var temporara in declaratii
            if (!found(declarations, lenDeclarations, tempVar)) {
                strcpy(declarations[lenDeclarations], " ");
                strcat(declarations[lenDeclarations], tempVar);
                strcat(declarations[lenDeclarations], " times 4 db 0");
                lenDeclarations++;
            }

            strcpy(tempResult[tempLen-1], tempVar);
        } else {
            strcpy(tempResult[tempLen++], expressions[i]);
            strcpy(tempResult[tempLen++], expressions[i+1]);
        }
    }

    // evaluez adunarile si scaderile
    if (isdigit(tempResult[0][0])) {
        strcpy(sourceCode[lenSourceCode], "mov EAX, ");
        strcat(sourceCode[lenSourceCode++], tempResult[0]);
    } else {
        strcpy(sourceCode[lenSourceCode], "mov EAX, dword [");
        strcat(sourceCode[lenSourceCode], tempResult[0]);
        strcat(sourceCode[lenSourceCode++], "]");
    }

    for (int i = 1; i < tempLen - 1; i += 2) {
        if (strcmp(tempResult[i], "+") == 0) {
            if (isdigit(tempResult[i+1][0])) {
                strcpy(sourceCode[lenSourceCode], "add EAX, ");
                strcat(sourceCode[lenSourceCode++], tempResult[i+1]);
            } else {
                strcpy(sourceCode[lenSourceCode], "add EAX, dword [");
                strcat(sourceCode[lenSourceCode], tempResult[i+1]);
                strcat(sourceCode[lenSourceCode++], "]");
            }
        } else if (strcmp(tempResult[i], "-") == 0) {
            if (isdigit(tempResult[i+1][0])) {
                strcpy(sourceCode[lenSourceCode], "sub EAX, ");
                strcat(sourceCode[lenSourceCode++], tempResult[i+1]);
            } else {
                strcpy(sourceCode[lenSourceCode], "sub EAX, dword [");
                strcat(sourceCode[lenSourceCode], tempResult[i+1]);
                strcat(sourceCode[lenSourceCode++], "]");
            }
        }
    }

    strcpy(sourceCode[lenSourceCode], "mov dword [");
    strcat(sourceCode[lenSourceCode], element);
    strcat(sourceCode[lenSourceCode++], "], EAX");
    lenExpressions = 0;
}


bool found(char col[][MAX], int n, char* var) {
	char tmp[MAX];
	strcpy(tmp, var);
	strcat(tmp, " ");
	for (int i = 0; i < n; i++) {
		if (strstr(col[i], tmp) != NULL) {
			return true;
		}
	}
	return false;
}

void printImports() {
	for (int i = 0; i < lenImports; i++) {
		fprintf(outputFile, "extern %s\nimport %s msvcrt.dll\n\n", imports[i], imports[i]);
	}
}

void printDeclarationSegment() {
	for (int i = 0; i < lenDeclarations; i++) {
		fprintf(outputFile, "\t%s\n", declarations[i]);
	}
}

void printCodeSegment() {
	for (int i = 0; i < lenSourceCode; i++) {
		fprintf(outputFile, "\t\t%s\n", sourceCode[i]);
	}
}
