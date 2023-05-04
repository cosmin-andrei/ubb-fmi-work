#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Melodie.h"

typedef Melodie ElemType;
typedef struct  {
	ElemType* elems;
	int length;
	int capacitate;
} MyList;

/*
* Creeaza o lista goala
* 
* @return: lista creata (MyList)
*/
MyList createEmpty();

/*
* Distruge lista data si elementele sale
* 
* @param v: (adresa pentru) lista de distrus (MyList*)
* post: memoria alocata pentru lista si elementele sale este eliberata
*/
void destroy(MyList* v);

/*
* Returneaza elementul de pe pozitia poz din lista data
* 
* @param v: (adresa pentru) lista data (MyList*)
* @param poz: pozitia din lista (int)
* pre: poz valid (0<poz<v->length)
* 
* @return: elementul de pe pozitia poz din lista data (ElemType)
*/
ElemType get(MyList* v, int poz);

/*
* Pune elementul el pe pozitia poz din lista v
* 
* @param: (adresa pentru) lista data (MyList*)
* @param poz: pozitia din lista (int)
* @ElemType el: elementul care va fi pus pe pozitia data din lista
* 
* @return: elementul inlocuit/elementul care a fost anterior pe pozitia
			poz(daca exista) (ElemType)
*/
ElemType setElem(MyList* v, int poz, ElemType el);

/*
* Returneaza numarul de elemente in lista
* 
* @param: (adresa pentru) lista data (MyList*)
* 
* @return: numarul de elemente din lista (int)
*/
int size(MyList* v);

/*
* Adauga un element in lista
* 
* @param v: (adresa pentru) lista data (MyList*)
* @param el: elementul care se adauga in lista
* 
* post: elementul va fi adaugat in lista
*/
void add(MyList* v, ElemType el);

/*
* Sterge un element din lista
*
* @param v: (adresa pentru) lista data (MyList*)
* @param poz: pozitia de pe care se sterge din lista
*
* @return: elementul sters din lista (ElemType)
* post: elementul a fost sters din lista
*/
ElemType delete(MyList* v, int poz);

/*
* Face o copie a listei date (similar cu Python deepcopy)
* 
* @param v: (adresa pentru) lista care se copiaza (MyList*)
* 
* @return: copie a listei date (MyList)
*/
MyList copyList(MyList* v);

void testCreateVector();
void testIterate();
void testCopy();


