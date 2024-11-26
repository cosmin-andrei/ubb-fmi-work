%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//cuvant, cod atom, index TS
typedef struct {
    char atom[100];
    int codAtom;
    int codTS;
} FIP_Entry;

// entry, index
typedef struct {
    char entry[100];
    int index;
} TS_Entry;

#define MAX_ENTRIES 1000

FIP_Entry fip[MAX_ENTRIES];
TS_Entry ts_ID[MAX_ENTRIES];
TS_Entry ts_CONST[MAX_ENTRIES];

int fip_count = 0; //no. of entries in FIP
int ts_id_count = 0; // no. of entries in TS_ID
int ts_const_count = 0; // no. of entries in TS_CONST
extern int currentLine; // line of file

// add to TS
// return index in TS/ cel curent daca e deja in TS
int add_to_ts(TS_Entry *ts, int *count, const char *atom) {

   // check if atom is already in TS
    for (int i = 0; i < *count; i++) {
        if (strcmp(ts[i].entry, atom) == 0) {
            return i; // deja in ts
        }
    }

    //add atom
    strcpy(ts[*count].entry, atom);
    ts[*count].index = *count;
    (*count)++;
    return *count - 1;

}

// add to FIP
void add_to_fip(const char *atom, int codAtom, int codTS) {
    fip[fip_count].codAtom = codAtom;
    fip[fip_count].codTS = codTS;
    fip_count++;
}

void write_fip_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < fip_count; i++) {
        fprintf(file, "%s %d %d\n", fip[i].atom, fip[i].codAtom, fip[i].codTS);
    }
    fclose(file);
}

void write_ts_to_file(const char *id_file, const char *const_file) {
    FILE *id_f = fopen(id_file, "w");
    FILE *const_f = fopen(const_file, "w");

    for (int i = 0; i < ts_id_count; i++) {
        fprintf(id_f, "%d %s\n", ts_ID[i].index, ts_ID[i].entry);
    }

    for (int i = 0; i < ts_const_count; i++) {
        fprintf(const_f, "%d %s\n", ts_CONST[i].index, ts_CONST[i].entry);
    }

    fclose(id_f);
    fclose(const_f);
}
%}

%option noyywrap

DIGIT           [0-9]
LETTER          [a-zA-Z_]
ID              {LETTER}({LETTER}|{DIGIT})*
/*start with a letter, followed by letters or digits*/
CONST           {DIGIT}+(\.{DIGIT}+)?
/*integer or float*/
KEYWORD         int|main|cin|while|cout|else|if
OPERATOR        "=="|"!="|">"|"<"|"-"|"+"|"="
SEPARATOR       [;{}(),]|>>|<<

%%

"int"          { add_to_fip(yytext, 0, -1); }
"main"         { add_to_fip(yytext, 1, -1); }
"cin"          { add_to_fip(yytext, 2, -1); }
"while"        { add_to_fip(yytext, 3, -1); }
"cout"         { add_to_fip(yytext, 4, -1); }
"else"         { add_to_fip(yytext, 5, -1); }
"if"           { add_to_fip(yytext, 6, -1); }
"cattimp"      { add_to_fip(yytext, 21, -1); }
"sfcattimp"    { add_to_fip(yytext, 22, -1); }

{ID} {
    int index = add_to_ts(ts_ID, &ts_id_count, yytext);
    add_to_fip(yytext, 0, index);
}

{CONST} {
    int index = add_to_ts(ts_CONST, &ts_const_count, yytext);
    add_to_fip(yytext, 1, index);
}


"!="          { add_to_fip(yytext, 12, -1); }
"-"           { add_to_fip(yytext, 15, -1); }
"+"           { add_to_fip(yytext, 16, -1); }
"=="          { add_to_fip(yytext, 17, -1); }
">"           { add_to_fip(yytext, 18, -1); }
"<"           { add_to_fip(yytext, 19, -1); }
"="           { add_to_fip(yytext, 20, -1); }

"("           { add_to_fip(yytext, 7, -1); }
")"           { add_to_fip(yytext, 8, -1); }
"{"           { add_to_fip(yytext, 9, -1); }
"}"           { add_to_fip(yytext, 10, -1); }
";"           { add_to_fip(yytext, 11, -1); }
">>"          { add_to_fip(yytext, 13, -1); }
"<<"          { add_to_fip(yytext, 14, -1); }

\n { currentLine++; }

[ \t]+ {}

. {
    printf("eroare: '%s' linia %d\n", yytext, currentLine);
}

%%
