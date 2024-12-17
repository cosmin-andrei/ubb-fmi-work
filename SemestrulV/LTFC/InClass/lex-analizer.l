%{
#include "parser.tab.h"
#include <string.h>

int valid(const char *time) {
    //scadere pt a obtine cifrele
    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int min = (time[3] - '0') * 10 + (time[4] - '0');
    return hour >= 0 && hour <= 23 && min >= 0 && min <= 59;
}

int palindrom(const char *time) {
    return time[0] == time[4] && time[1] == time[3];
}
%}

%option noyywrap

DIGIT [0-9]
TIME {DIGIT}{2}:{DIGIT}{2}

%%

{TIME} {
    if (valid(yytext)) {
        if (palindrom(yytext)) {
            return VALID_TIME;
        } else {
            return INVALID_TIME;
        }
    } else {
        return INVALID_TIME;
    }
}

%%
