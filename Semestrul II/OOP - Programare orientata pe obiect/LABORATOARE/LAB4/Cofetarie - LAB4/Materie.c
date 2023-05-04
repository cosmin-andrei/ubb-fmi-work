#pragma once
#include "Materie.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

Materie* createMaterie(char* nume, char* producator, float cantitate) {

	Materie* m = malloc(sizeof(Materie));

	int nrC = (int)strlen(nume) + 1;
	m->nume = malloc(nrC * sizeof(char));
	strcpy_s(m->nume, nrC, nume);

	nrC = (int)strlen(producator) + 1;
	m->producator = malloc(nrC * sizeof(char));
	strcpy_s(m->producator, nrC, producator);

	m->cantitate = cantitate;
	return m;
}

void destroyMaterie(Materie* m) {

	free(m->nume);
	free(m->producator);
	free(m);

}

Materie* copyMaterie(Materie* m) {
	return createMaterie(m->nume, m->producator, m->cantitate);
}

int valideazaMaterie(Materie* m) {
	if (strlen(m->nume) == 0 || strlen(m->producator) == 0)
		return 0;
	if (m->cantitate < 0.0)
		return 0;
	return 1;
}

void testCreateDestroy() {
	Materie* m = createMaterie("Acadea", "ubb", 50);

	assert(strcmp(m->nume, "Acadea") == 0);
	assert(strcmp(m->producator, "ubb") == 0);
	assert(m->cantitate == 50);

	destroyMaterie(m);

}

void testValideaza() {
	Materie* m1 = createMaterie("", "Grande", 15.5);
	assert(valideazaMaterie(m1) == 0);

	Materie* m2 = createMaterie("Prajitura", "", 17.5);
	assert(valideazaMaterie(m2) == 0);

	Materie* m3 = createMaterie("Acadea", "Grande", -10);
	assert(valideazaMaterie(m3) == 0);

	Materie* m4 = createMaterie("Acadea", "Grande", 15.5);
	assert(valideazaMaterie(m4) == 1);

	destroyMaterie(m1);
	destroyMaterie(m2);
	destroyMaterie(m3);
	destroyMaterie(m4);

}

