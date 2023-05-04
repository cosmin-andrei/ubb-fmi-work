#pragma once
#include "Tranzactie.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

Tranzactie* createTranzactie(int ziua, int luna, int suma, char* tip, char* descriere) {

	Tranzactie* t = malloc(sizeof(Tranzactie));
	t->ziua = ziua;
	t->luna = luna;
	t->suma = suma;

	int nrC = (int)strlen(tip) + 1;
	t->tip = malloc(nrC * sizeof(char));
	strcpy_s(t->tip, nrC, tip);

	nrC = (int)strlen(descriere) + 1;
	t->descriere = malloc(nrC * sizeof(char));
	strcpy_s(t->descriere, nrC, descriere);

	return t;
}

void destroyTranzactie(Tranzactie* t) {

	free(t->tip);
	free(t->descriere);
	free(t);

}

Tranzactie* copyTranzactie(Tranzactie* t) {
	return createTranzactie(t->ziua, t->luna, t->suma, t->tip, t->descriere);
}

int valideazaTranzactie(Tranzactie* t) {
	if (strlen(t->descriere) == 0)
		return 0;
	// if (strcmp(t->tip, "intrare") != 0 || strcmp(t->tip, "iesire") != 0)
		// return 0;
	if (t->ziua < 1 || t->ziua > 31)
		return 0;
	if (t->luna < 1 || t->luna>12)
		return 0;
	if (t->suma <= 0)
		return 0;
	return 1;
}

void testCreateDestroy() {
	Tranzactie* t = createTranzactie(2, 12, 50, "iesire", "Plata");

	assert(t->ziua == 2);
	assert(t->luna == 12);
	assert(t->suma == 50);
	assert(strcmp(t->tip, "iesire") == 0);
	assert(strcmp(t->descriere, "Plata") == 0);

	destroyTranzactie(t);

}

void testValideaza() {
	Tranzactie* t1 = createTranzactie(35, 12, 50, "intrare", "Plata");
	assert(valideazaTranzactie(t1) == 0);

	Tranzactie* t2 = createTranzactie(1, 15, 20, "iesire", "plata");
	assert(valideazaTranzactie(t2) == 0);

	Tranzactie* t3 = createTranzactie(1, 1, 0, "iesire", "plata");
	assert(valideazaTranzactie(t3) == 0);

	Tranzactie* t4 = createTranzactie(1, 1, 10, "iesire", "");
	assert(valideazaTranzactie(t4) == 0);

	Tranzactie* t5 = createTranzactie(10, 12, 54, "intrare", "Salariu");
	assert(valideazaTranzactie(t5) == 1);

	destroyTranzactie(t1);
	destroyTranzactie(t2);
	destroyTranzactie(t3);
	destroyTranzactie(t4);
	destroyTranzactie(t5);


}

