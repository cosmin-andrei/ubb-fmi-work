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
* Creeaza o noua tranzactie
*
* @param ziua: ziua tranzactiei (int)
* @param luna: luna tranzactiei (int)
* @param suma: suma tranzactiei (int)
* @param descriere: descrierea tranzactiei (char*)
*
* @return tranzactie creata (Tranzactie)
*/

Tranzactie* createTranzactie(int ziua, int luna, int suma, char* tip, char* descriere);

/*
   Creeaza o copie a tranzactiei date
*/

Tranzactie* copyTranzactie(Tranzactie* t);

/*
* Distruge melodie
*/
void destroyTranzactie(Tranzactie* t);
/*
* Valideaza tranzactia
* O tranzactie este valida daca:
 * - descrierea e diferita de ""
 * - ziua e [1,31]
 * - luna e [1,12]
 * - suma > 0
*
* @param t: tranzactie de validat (Tranzactie)
*
* @return: 1 daca tranzactia este valida, 0 daca nu
*/
int valideazaTranzactie(Tranzactie* t);

void testCreateDestroy();
void testValideaza();