#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
typedef struct {
    char* nume;
    char* producator;
    float cantitate;
} Materie;


Materie* createMaterie(char* nume, char* producator, float cantitate);

Materie* copyMaterie(Materie* m);

void destroyMaterie(Materie* m);


int valideazaMaterie(Materie* m);

void testCreateDestroy();
void testValideaza();