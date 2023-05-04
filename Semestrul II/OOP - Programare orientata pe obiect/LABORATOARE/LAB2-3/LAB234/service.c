#pragma once
#include "service.h"
#include "customSort.h"
#include <assert.h>
#include <string.h>


Tranzactii createTranzactii()
{
	Tranzactii store;
	store.allTranzactii = createEmpty(destroyTranzactie);
	return store;
}
void destroyTranzactii(Tranzactii* store) {
	destroyList(store->allTranzactii);
}

int addTranzactie(Tranzactii* store, int ziua, int luna, int suma, char* tip, char* descriere) {
	Tranzactie* t = createTranzactie(ziua, luna, suma, tip, descriere);


	int successful = valideazaTranzactie(t);
	if (!successful) {
		destroyTranzactie(t);
		return 0;
	}

	add(store->allTranzactii, t);
	return 1;

}
int findTranzactie(Tranzactii* store, int ziua, int luna, char* descriere) {
	int poz_to_delete = -1;
	for (int i = 0; i < store->allTranzactii->length; i++) {
		Tranzactie* t = get(store->allTranzactii, i);
		if (t->ziua == ziua && t->luna == luna && strcmp(t->descriere, descriere) == 0) {
			poz_to_delete = i;
			break;
		}
	}
	return poz_to_delete;
}

int deleteTranzactie(Tranzactii* store, int ziua, int luna, char* descriere) {
	int poz_to_delete = findTranzactie(store, ziua, luna, descriere);
	if (poz_to_delete != -1) {

		Tranzactie* t = delete(store->allTranzactii, poz_to_delete);
		destroyTranzactie(t);
		return 1;
	}
	else
		return 0;
}
int modifyTranzactie(Tranzactii* store, int ziua, int luna, int suma, char* tip, char* descriere, char* descriereNoua) {
	int poz_to_delete = findTranzactie(store, ziua, luna, descriere);

	if (poz_to_delete != -1) {

		Tranzactie* tranzactieNoua = createTranzactie(ziua, luna, suma, tip, descriereNoua);
		Tranzactie* tranzactieReplaced = setElem(store->allTranzactii, poz_to_delete, tranzactieNoua);
		destroyTranzactie(tranzactieReplaced);
		return 1;
	}
	else
		return 0;
}

// t->suma > suma
MyList* filterTranzactiiSuma(Tranzactii* store, int suma) {
	MyList* filteredList = createEmpty(destroyTranzactie);
	for (int i = 0; i < store->allTranzactii->length; i++) {
		Tranzactie* t = get(store->allTranzactii, i);
		if (t->suma > suma)
			add(filteredList, createTranzactie(t->ziua, t->luna, t->suma, t->tip, t->descriere));
	}
	return filteredList;

}

MyList* filterTranzactiiTip(Tranzactii* store, char* tip) {
	MyList* filteredList = createEmpty(destroyTranzactie);
	for (int i = 0; i < store->allTranzactii->length; i++) {
		Tranzactie* t = get(store->allTranzactii, i);
		if (strcmp(t->tip, tip) == 0)
			add(filteredList, createTranzactie(t->ziua, t->luna, t->suma, t->tip, t->descriere));
	}
	return filteredList;
}

int cmpSuma(Tranzactie* t1, Tranzactie* t2)
{
	if (t1->suma == t2->suma)
		return 0;
	if (t1->suma > t2->suma)
		return 1;
	else
		return -1;
}

int cmpSumaR(Tranzactie* t1, Tranzactie* t2)
{
	if (t1->suma == t2->suma)
		return 0;
	if (t1->suma < t2->suma)
		return 1;
	else
		return -1;
}

int cmpZi(Tranzactie* t1, Tranzactie* t2)
{
	if (t1->ziua == t2->ziua)
		return 0;
	if (t1->ziua > t2->ziua)
		return 1;
	else
		return -1;
}

int cmpZiR(Tranzactie* t1, Tranzactie* t2)
{
	if (t1->ziua == t2->ziua)
		return 0;
	if (t1->ziua < t2->ziua)
		return 1;
	else
		return -1;
}

MyList* sortTranzactiiBySumaR(Tranzactii* store)
{
	MyList* tranzactiiList = copyList(store->allTranzactii, copyTranzactie);
	sort(tranzactiiList, cmpSumaR);
	return tranzactiiList;
}

MyList* sortTranzactiiByZiR(Tranzactii* store) {
	MyList* tranzactiiList = copyList(store->allTranzactii, copyTranzactie);
	sort(tranzactiiList, cmpZiR);
	return tranzactiiList;
}

MyList* sortTranzactiiBySuma(Tranzactii* store)
{
	MyList* tranzactiiList = copyList(store->allTranzactii, copyTranzactie);
	sort(tranzactiiList, cmpSuma);
	return tranzactiiList;
}

MyList* sortTranzactiiByZi(Tranzactii* store) {
	MyList* tranzactiiList = copyList(store->allTranzactii, copyTranzactie);
	sort(tranzactiiList, cmpZi);
	return tranzactiiList;
}

MyList* filterTranzactii(Tranzactii* store, char* descriere) {
	if (strcmp(descriere, "") != 0) {
		MyList* filteredList = createEmpty(destroyTranzactie);
		for (int i = 0; i < store->allTranzactii->length; i++) {
			Tranzactie* t = get(store->allTranzactii, i);
			if (strcmp(descriere, t->descriere) == 0)
				add(filteredList, createTranzactie(t->ziua, t->luna, t->suma, t->tip, t->descriere));
		}
		return filteredList;}
	else {
		return copyList(store->allTranzactii, copyTranzactie);
	}

}

void testAddService() {
	Tranzactii store = createTranzactii();

	int successful1 = addTranzactie(&store, 2, 12, 50, "iesire", "Salariu");
	assert(successful1 == 1);

	int successful2 = addTranzactie(&store, -1, 12, 50, "intrare", "Salariu");
	assert(successful2 == 0);

	int successful3 = addTranzactie(&store, 1, 15, 50, "iesire", "Salariu");
	assert(successful3 == 0);

	int successful4 = addTranzactie(&store, 1, 15, 0, "intrare", "Salariu");
	assert(successful4 == 0);

	int successful5 = addTranzactie(&store, 1, 15, 50, "intrare", "");
	assert(successful5 == 0);

	MyList* allTranzactii = filterTranzactii(&store, "");
	assert(size(allTranzactii) == 1);
	destroyList(allTranzactii);

}

void testModifyService()
{
	Tranzactii store = createTranzactii();

	int successful1 = addTranzactie(&store, 2, 12, 50, "intrare", "Salariu");
	assert(successful1 == 1);

	int successful2 = addTranzactie(&store, 3, 10, 56, "iesire", "Chirie");
	assert(successful2 == 1);

	int successful3 = addTranzactie(&store, 1, 9, 10, "iesire", "Mancare");
	assert(successful3 == 1);

	assert(size(store.allTranzactii) == 3);
	int modify_success = modifyTranzactie(&store, 1, 9, 10, "iesire", "Mancare", "Porumb");
	assert(modify_success == 1);
	int modify_success2 = modifyTranzactie(&store, 3, 10, 9, "", "", "Familie");
	assert(modify_success2 == 0);
	destroyTranzactii(&store);
}

void testDeleteService()
{
	Tranzactii store = createTranzactii();

	int successful1 = addTranzactie(&store, 2, 12, 50, "iesire", "Salariu");
	assert(successful1 == 1);

	int successful2 = addTranzactie(&store, 1, 9, 50, "intrare", "Mancare");
	assert(successful2 == 1);

	int successful3 = addTranzactie(&store, 1, 10, 50, "iesire", "Scoala");
	assert(successful3 == 1);

	assert(size(store.allTranzactii) == 3);
	int succesful_del = deleteTranzactie(&store, 1, 9, "Mancare");
	assert(succesful_del == 1);
	int succesfully_del = deleteTranzactie(&store, 3, 10, "Scoala");
	assert(succesfully_del == 0);
	//destroyTranzactiiStore(&store);
}


void testFilterService()
{
	Tranzactii store = createTranzactii();
	int successful1 = addTranzactie(&store, 2, 12, 30, "iesire", "Salariu");
	assert(successful1 == 1);

	int successful2 = addTranzactie(&store, 1, 9, 50, "intrare", "Mancare");
	assert(successful2 == 1);

	int successful3 = addTranzactie(&store, 1, 10, 50, "iesire", "Scoala");
	assert(successful3 == 1);


	assert(size(store.allTranzactii) == 3);
	MyList* filteredList = filterTranzactiiSuma(&store, 40);
	assert(size(filteredList) == 2);


	MyList* filteredList2 = filterTranzactiiTip(&store, "intrare");
	assert(size(filteredList2) == 1);


	MyList* filteredList3 = filterTranzactii(&store, "Salariu");
	assert(size(filteredList3) == 1);

	destroyTranzactii(&store);
}

void testCmpService()
{
	Tranzactie* t1 = createTranzactie(2, 12, 30, "iesire", "Salariu");
	Tranzactie* t2 = createTranzactie(1, 9, 50, "intrare", "Mancare");
	Tranzactie* t3 = createTranzactie(10, 12, 60, "iesire", "Sala");
	Tranzactie* t4 = createTranzactie(1, 12, 50, "iesire", "chirie");

	assert(cmpSuma(t1, t2) == -1);
	assert(cmpSumaR(t1, t2) == 1);
	assert(cmpSuma(t3, t4) == 1);
	assert(cmpSumaR(t3, t4) == -1);
	assert(cmpSuma(t2, t4) == 0);
	assert(cmpSumaR(t2, t4) == 0);

	assert(cmpZi(t1, t2) == 1);
	assert(cmpZiR(t1, t2) == -1);
	assert(cmpZi(t2, t4) == 0);
	assert(cmpZiR(t2, t4) == 0);
	assert(cmpZi(t4, t3) == -1);
	assert(cmpZiR(t4, t3) == 1);

}

void testSortService()
{
	Tranzactii store = createTranzactii();
	int successful1 = addTranzactie(&store, 2, 12, 30, "iesire", "Salariu");
	assert(successful1 == 1);

	int successful2 = addTranzactie(&store, 1, 9, 60, "intrare", "Mancare");
	assert(successful2 == 1);

	int successful3 = addTranzactie(&store, 5, 10, 50, "iesire", "Scoala");
	assert(successful3 == 1);

	//descrescator
	MyList* l = sortTranzactiiByZiR(&store);
	Tranzactie* t1 = get(l, 0);
	Tranzactie* t2 = get(l, 1);
	Tranzactie* t3 = get(l, 2);
	assert(strcmp(t2->descriere, "Salariu") == 0);
	assert(strcmp(t3->descriere, "Mancare") == 0);
	assert(strcmp(t1->descriere, "Scoala") == 0);

	//descrescator
	l = sortTranzactiiByZi(&store);
	t1 = get(l, 0);
	t2 = get(l, 1);
	t3 = get(l, 2);
	assert(strcmp(t2->descriere, "Salariu") == 0);
	assert(strcmp(t1->descriere, "Mancare") == 0);
	assert(strcmp(t3->descriere, "Scoala") == 0);


	//crescator
	l = sortTranzactiiBySumaR(&store);
	t1 = get(l, 0);
	t2 = get(l, 1);
	t3 = get(l, 2);
	assert(strcmp(t3->descriere, "Salariu") == 0);
	assert(strcmp(t1->descriere, "Mancare") == 0);
	assert(strcmp(t2->descriere, "Scoala") == 0);

	//descrescator
	l = sortTranzactiiBySuma(&store);
	t1 = get(l, 0);
	t2 = get(l, 1);
	t3 = get(l, 2);
	assert(strcmp(t1->descriere, "Salariu") == 0);
	assert(strcmp(t3->descriere, "Mancare") == 0);
	assert(strcmp(t2->descriere, "Scoala") == 0);


}