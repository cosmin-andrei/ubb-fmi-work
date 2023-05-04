#pragma once
#include "service.h"
#include "Sort.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

Cofetarie createCofetarie()
{
	Cofetarie store;
	store.allMaterii = createEmpty(destroyMaterie);
	store.undoList = createEmpty(destroyList);
	return store;
}
void destroyCofetarie(Cofetarie* store) {
	destroyList(store->allMaterii);
	destroyList(store->undoList);
}

int addMaterie(Cofetarie* store, char* nume, char* producator, float cantitate) {
	Materie* m = createMaterie(nume, producator, cantitate);


	int successful = valideazaMaterie(m);
	if (!successful) {
		destroyMaterie(m);
		return 0;
	}

	MyList* toUndo = copyList(store->allMaterii, copyMaterie);
	add(store->allMaterii, m);
	add(store->undoList, toUndo);
	return 1;

}
int findMaterie(Cofetarie* store, char* nume) {
	int poz_to_delete = -1;
	for (int i = 0; i < store->allMaterii->length; i++) {
		Materie* m = get(store->allMaterii, i);
		if (strcmp(m->nume, nume) == 0) {
			poz_to_delete = i;
			break;
		}
	}
	return poz_to_delete;
}

int deleteMaterie(Cofetarie* store, char* nume) {
	int poz_to_delete = findMaterie(store, nume);
	if (poz_to_delete != -1) {

		MyList* toUndo = copyList(store->allMaterii, copyMaterie);
		add(store->undoList, toUndo);

		Materie* m = delete(store->allMaterii, poz_to_delete);
		destroyMaterie(m);
		return 1; }
	else
		return 0;
}
int modifyMaterie(Cofetarie* store, char* nume, char* producator_nou, float cantitate_noua) {
	int poz_to_delete = findMaterie(store, nume);

	if (poz_to_delete != -1) {
		MyList* toUndo = copyList(store->allMaterii, copyMaterie);
		add(store->undoList, toUndo);

		Materie* materieNoua = createMaterie(nume, producator_nou, cantitate_noua);
		Materie* materieReplaced = setElem(store->allMaterii, poz_to_delete, materieNoua);
		destroyMaterie(materieReplaced);
		return 1; }
	else
		return 0;
}


MyList* filterMateriiCantitate(Cofetarie* store, float cantitate) {
	if (cantitate > 0)
	{
		MyList* filteredList = createEmpty(destroyMaterie);
		for (int i = 0; i < store->allMaterii->length; i++) {
			Materie* m = get(store->allMaterii, i);
			if (m->cantitate < cantitate)
				add(filteredList, createMaterie(m->nume, m->producator, m->cantitate));
		}
		return filteredList; }
	else
	{
		return copyList(store->allMaterii, copyMaterie);
	}
}

int cmpNume(Materie* m1, Materie* m2) {
	return strcmp(m1->nume, m2->nume);
}

int cmpCant(Materie* m1, Materie* m2) {
	if (m1->cantitate == m2->cantitate)
		return 0;
	else if (m1->cantitate > m2->cantitate) return 1;
	else
		return -1;
}

MyList* sortByNume(Cofetarie* store, int way) {
	MyList* l = copyList(store->allMaterii, copyMaterie);
	sort(l, cmpNume, way);
	return l;
}

MyList* sortByCantitate(Cofetarie* store, int way) {
	MyList* l = copyList(store->allMaterii, copyMaterie);
	sort(l, cmpCant, way);
	return l;
}


//de testat
MyList* FilterByString(Cofetarie* store, char c) {
	MyList* rez = createEmpty(destroyCofetarie);
	for (int i = 0; i < store->allMaterii->length; i++) {
		Materie* m = get(store->allMaterii, i);
		char first = m->nume[0];
		if (first-c == 0) {
			add(rez, copyMaterie(m));
		}
	}
	return rez;
}

int undo(Cofetarie* store) {
	if (size(store->undoList) == 0)
		//nothing to undo
		return 0;
	MyList* v = delete(store->undoList, store->undoList->length - 1);
	destroyList(store->allMaterii);
	store->allMaterii = v;
	return 1;
}


void testAddService() {
	Cofetarie store = createCofetarie();

	int successful1 = addMaterie(&store, "", "Grande", 15.5);
	assert(successful1 == 0);

	int successful2 = addMaterie(&store, "Acadea", "", 16);
	assert(successful2 == 0);

	int successful3 = addMaterie(&store, "Acadea", "Grande", -15.5);
	assert(successful3 == 0);

	int successful4 = addMaterie(&store, "Acadea", "Grande", 15.5);
	assert(successful4 == 1);

	MyList* allMaterii = filterMateriiCantitate(&store, 0);
	assert(size(allMaterii) == 1);

	destroyList(allMaterii);

}

void testModifyService()
{
	Cofetarie store = createCofetarie();

	int successful1 = addMaterie(&store, "Bomboana", "Grande", 15);
	assert(successful1 == 1);

	int successful2 = addMaterie(&store, "Acadea", "Sisi", 16);
	assert(successful2 == 1);

	int successful4 = addMaterie(&store, "Prajitura", "ubb", 17);
	assert(successful4 == 1);

	assert(size(store.allMaterii) == 3);
	int modify_success = modifyMaterie(&store, "Bomboana", "Podgorita", 20);
	assert(modify_success == 1);
	int modify_success2 = modifyMaterie(&store, "Albina", "", -10);
	assert(modify_success2 == 0);
	destroyCofetarie(&store);
}

void testDeleteService()
{
	Cofetarie store = createCofetarie();

	int successful1 = addMaterie(&store, "Bomboana", "Grande", 15.5);
	assert(successful1 == 1);

	int successful2 = addMaterie(&store, "Acadea", "Sisi", 15.5);
	assert(successful2 == 1);

	int successful4 = addMaterie(&store, "Prajitura", "ubb", 15.5);
	assert(successful4 == 1);

	assert(size(store.allMaterii) == 3);
	int succesful_del = deleteMaterie(&store, "Acadea");
	assert(succesful_del == 1);
	int succesfully_del = deleteMaterie(&store, "Scoala");
	assert(succesfully_del == 0);
	
}


void testFilterService()
{
	Cofetarie store = createCofetarie();

	int successful1 = addMaterie(&store, "Bomboana", "Grande", 25);
	assert(successful1 == 1);

	int successful2 = addMaterie(&store, "Acadea", "Sisi", 15.5);
	assert(successful2 == 1);

	int successful4 = addMaterie(&store, "Prajitura", "ubb", 10);
	assert(successful4 == 1);


	assert(size(store.allMaterii) == 3);
	MyList* filteredList = filterMateriiCantitate(&store, 20);
	assert(size(filteredList) == 2);

	MyList* filteredList2 = FilterByString(&store, 'A');
	assert(size(filteredList2) == 1);

	destroyCofetarie(&store);
}

void testSortService() {
	Cofetarie store = createCofetarie();
	addMaterie(&store, "acadea", "c", 10);
	addMaterie(&store, "cer", "b", 20);
	addMaterie(&store, "bun", "a", 20);

	int way = 1;
	MyList* l = sortByNume(&store, way);
	Materie* m = get(l, 1);
	assert(strcmp(m->nume, "bun") == 0);
	destroyList(l);

	l = sortByCantitate(&store, way);
	m = get(l, 0);
	Materie* m1 = get(l, 1);
	assert(strcmp(m->producator, "c") == 0);
	assert(strcmp(m1->producator, "b") == 0);

	way = 2;
	MyList* l2 = sortByNume(&store, way);
	Materie* m2 = get(l2, 2);
	assert(strcmp(m2->nume, "acadea") == 0);

	destroyList(l);
//	destroyList(l2);
	destroyCofetarie(&store);
}

void testUndo()
{
	Cofetarie store = createCofetarie();
	assert(addMaterie(&store, "Bomboana", "Grande", 25) == 1);
	assert(modifyMaterie(&store, "Bomboana", "Podgorita", 20) == 1);
	assert(deleteMaterie(&store, "Bomboana") == 1);

	//undo delete
	undo(&store);

	MyList* ListMaterii = filterMateriiCantitate(&store, 0);
	assert(size(ListMaterii) == 1);
	Materie* m = get(ListMaterii, 0);
	assert(strcmp(m->producator,"Podgorita")==0);
	destroyList(ListMaterii);

	//undo modify
	undo(&store);

	MyList* ListMaterii2 = filterMateriiCantitate(&store, 0);
	assert(size(ListMaterii2) == 1);
	m = get(ListMaterii2, 0);
	assert(strcmp(m->producator, "Grande") == 0);
	destroyList(ListMaterii2);

	//undo add
	undo(&store);
	ListMaterii = filterMateriiCantitate(&store, 0);
	assert(size(ListMaterii) == 0);
	destroyList(ListMaterii);


	int moreUndo = undo(&store);
	assert(moreUndo == 0);
	destroyCofetarie(&store);
}