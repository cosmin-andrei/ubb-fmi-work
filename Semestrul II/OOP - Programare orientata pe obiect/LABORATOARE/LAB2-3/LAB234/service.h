#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MyList.h"

typedef struct {
	MyList* allTranzactii;
	MyList* undoList;
}Tranzactii;


Tranzactii createTranzactii();
/*
* Elibereaza memoria alocata pentru un SongStore
*/
void destroyTranzactii(Tranzactii* store);
int addTranzactie(Tranzactii* store, int ziua, int luna, int suma, char* tip, char* descriere);
int deleteTranzactie(Tranzactii* store, int ziua, int luna, char* descriere);
int modifyTranzactie(Tranzactii* store, int ziua, int luna, int suma, char* tip, char* descriere, char* descriereNoua);


MyList* filterTranzactiiSuma(Tranzactii* store, int suma);

MyList* filterTranzactiiTip(Tranzactii* store, char* tip);


MyList* sortTranzactiiBySuma(Tranzactii* store);

MyList* sortTranzactiiByZi(Tranzactii* store);

MyList* sortTranzactiiBySumaR(Tranzactii* store);

MyList* sortTranzactiiByZiR(Tranzactii* store);


void testAddService();
void testDeleteService();
void testModifyService();
void testFilterService();
void testCmpService();
void testSortService();
