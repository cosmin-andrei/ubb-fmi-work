#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MyList.h"

typedef struct {
	MyList* allTranzactii;

}TranzactiiStore;

/*
* Creeaza o entitate de tip TranzactiiStore
* care contine o lista de melodii si o
* lista pentru undo
*
*/
TranzactiiStore createTranzactiiStore();

/*
* Elibereaza memoria alocata pentru un TranazctiiStore
*/
void destroyTranzactiiStore(TranzactiiStore* store);


/*
* Adauga o tranzactie
*
* @param v: (adresa pentru) lista in care se adauga (MyList* v)
* @param ziua: ziua tranzactiei care se adauga (int)
* @param luna: luna tranzactiei care se adauga (int)
* @param suma: suma tranzactiei care se adauga (int)
* @param descriere: descrierea tranzactiei care se adauga (char*)
*
* @return: 1 daca tranzactia a fost adaugata cu succes, 0 altfel (int)
* post: tranzactia cu datele date este adaugata in lista (daca este o tranzactie valida)
*/
int addTranzactie(TranzactiiStore* store, int ziua, int luna, int suma, char* tip, char* descriere);

/*
* Sterge o tranzactie
*
* @param v: (adresa pentru) lista din care se sterge (MyList* v)
* @param ziua: ziua tranzactiei care se sterge (int)
* @param luna: luna tranzactiei care se sterge (int)
* @param descriere: descrierea tranzactiei care se sterge (char*)
*
* @return: 1 daca tranzactia a fost stearsa cu succes, 0 altfel (int)
* post: tranzactia cu ziua ziua, luna luna si descrierea descriere este stearsa din lista daca exista
*/
int deleteTranzactie(TranzactiiStore* store, int ziua, int luna, char* descriere);

/*
* Modifica o tranzactie
*
* @param v: (adresa pentru) lista in care se modifica (MyList* v)
* @param ziua: ziua tranzactiei care se modifica (int)
* @param luna: luna tranzactiei care se modifica (int)
* @param descriere: descrierea tranzactiei care se modifica (char*)
* @param descriereNoua: noua descriere a tranzactiei care se modifica(char*)
*
* @return: 1 daca tranzactia a fost modificata cu succes, 0 altfel (int)
* post: tranzactia cu ziua ziua, luna luna si suma suma se modifica cu o descriereNoua (daca o astfel
*		de melodie exista)
*/
int modifyTranzactie(TranzactiiStore* store, int ziua, int luna, int suma, char* tip, char* descriere, char* descriereNoua);


MyList* filterTranzactiiSuma(TranzactiiStore* store, int suma);

MyList* filterTranzactiiTip(TranzactiiStore* store, char* tip);


MyList* sortTranzactiiBySuma(TranzactiiStore* store);

MyList* sortTranzactiiByZi(TranzactiiStore* store);


void testAddService();
void testModifyService();
void testDeleteService();
void testFilterService();
