#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
typedef struct {
    int ziua;
    int luna;
    int suma;
    char* tip;
    char* descriere;
} Tranzactie;

/*
* Creeaza o noua melodie
*
* @param titlu: titlul melodiei (string)
* @param artist: artistul melodiei (string)
* @param durata: durata melodiei (int)
*
* @return melodia creata (Melodie)
*/

Tranzactie* createTranzactie(int ziua, int luna, int suma, char* tip, char* descriere);

/*
* Creeaza o copie a melodiei date (similar cu Python "deepcopy")
*/
Tranzactie* copyTranzactie(Tranzactie* t);

/*
* Distruge melodie
*/
void destroyTranzactie(Tranzactie* t);

/*
* Valideaza melodie
* O melodie este valida daca titlu si artist diferit de ""
* iar 0<durata<180
* @param m: melodia de validat (Melodie)
*
* @return: 1 daca melodia este valida, 0 daca nu
*/
int valideazaTranzactie(Tranzactie* t);

void testCreateDestroy();
void testValideaza();