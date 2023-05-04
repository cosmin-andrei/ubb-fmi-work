#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MyList.h"

typedef struct {
	MyList* allMaterii;
	MyList* undoList;
} Cofetarie;


Cofetarie createCofetarie();

void destroyCofetarie(Cofetarie* store);
int addMaterie(Cofetarie* store, char* nume, char* producator, float cantitate);
int deleteMaterie(Cofetarie* store, char* nume);
int modifyMaterie(Cofetarie* store, char* nume, char* producator_nou, float cantitate_noua);

MyList* filterMateriiCantitate(Cofetarie* store, float cantitate);
MyList* FilterByString(Cofetarie* store, char c);
MyList* sortByNume(Cofetarie* store, int way);
MyList* sortByCantitate(Cofetarie* store, int way);

int undo(Cofetarie* store);

void testAddService();
void testDeleteService();
void testModifyService();
void testFilterService();
void testSortService();
void testUndo();