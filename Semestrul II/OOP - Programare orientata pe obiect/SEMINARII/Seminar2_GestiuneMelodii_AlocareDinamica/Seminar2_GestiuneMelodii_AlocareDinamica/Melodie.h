#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

typedef struct {
	char* titlu;
	char* artist;
	int durata;
} Melodie;

/*
* Creeaza o noua melodie
* 
* @param titlu: titlul melodiei (string)
* @param artist: artistul melodiei (string)
* @param durata: durata melodiei (int)
* 
* @return melodia creata (Melodie)
*/

Melodie createMelodie(char* titlu, char* artist, int durata);

/*
* Distruge melodie
*/
void destroyMelodie(Melodie* m);
/*
* Valideaza melodie
* O melodie este valida daca titlu si artist diferit de ""
* iar 0<durata<180
* @param m: melodia de validat (Melodie)
* 
* @return: 1 daca melodia este valida, 0 daca nu
*/
int valideazaMelodie(Melodie m);

/*
* Creeaza o copie a melodiei date (similar cu Python "deepcopy")
*/
Melodie copyMelodie(Melodie m);

void testCreateDestroy();
void testValideaza();
