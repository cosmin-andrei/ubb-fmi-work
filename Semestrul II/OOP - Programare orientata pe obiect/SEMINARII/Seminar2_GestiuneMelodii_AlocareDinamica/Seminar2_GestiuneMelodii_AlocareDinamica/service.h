#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MyList.h"

/*
* Adauga o melodie
* 
* @param v: (adresa pentru) lista in care se adauga (MyList* v)
* @param titlu: titlul melodiei care se adauga (char*)
* @param artist: artistul melodiei care se adauga (char*)
* @param durata: durata melodiei care se adauga (int)
* 
* @return: 1 daca melodia a fost adaugata cu succes, 0 altfel (int)
* post: melodia cu datele date este adaugata in lista (daca este o melodie valida)
*/
int addMelodie(MyList* v, char* titlu, char* artist, int durata);

/*
* Sterge o melodie
*
* @param v: (adresa pentru) lista din care se sterge (MyList* v)
* @param titlu: titlul melodiei care se sterge (char*)
* @param artist: artistul melodiei care se sterge (char*)
*
* @return: 1 daca melodia a fost stearsa cu succes, 0 altfel (int)
* post: melodia cu titlul titlu si artistul artist este stearsa din lista daca exista
*/
int deleteMelodie(MyList* v, char* titlu, char* artist);

/*
* Modifica o melodie
*
* @param v: (adresa pentru) lista in care se modifica (MyList* v)
* @param titlu: titlul melodiei care se modifica (char*)
* @param artist: artistul melodiei care se modifica (char*)
* @param durata: noua durata a melodiei (int)
*
* @return: 1 daca melodia a fost modificata cu succes, 0 altfel (int)
* post: melodia cu titlul titlu si artistul artist are durataNoua (daca o astfel
*		de melodie exista)
*/
int modifyMelodie(MyList* v, char* titlu, char* artist, int durataNoua);


/*
* Gaseste o melodie cu titlu si artist dat
*
* @param v: (adresa pentru) lista in care se cauta (MyList* v)
* @param titlu: titlul melodiei care se cauta (char*)
* @param artist: artistul melodiei care se cauta (char*)
*
* @return: pozitia din lista a melodiei cautate, -1 daca 
			melodia nu exista in lista (int)
*/
int findMelodie(MyList* v, char* titlu, char* artist);

/*
* Filtreaza lista de melodii dupa un artist dat
*
* @param v: (adresa pentru) lista data (MyList* v)
* @param artist: artistul dupa care se filtreaza lista (char*)

*
* @return: lista cu melodiile care au artistul artist (MyList)
*		   daca artist="" se returneaza o copie a listei originale
*/
MyList filterMelodii(MyList* v, char* artist);

/*
* Returneaza o lista sortata de melodii 
* Criteriu de sortare: durata (ascendent)
* 
* @param v: (adresa pentru) lista data (MyList* v)
* 
* @return: o lista sortata de melodii  (MyList)
*/
//MyList sortMelodii(MyList* v);

void testAddService();
void testModifyService();
void testDeleteService();
void testFindService();
void testFilterService();
//void testSortService();

