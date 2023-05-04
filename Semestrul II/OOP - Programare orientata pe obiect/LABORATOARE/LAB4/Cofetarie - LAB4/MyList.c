#pragma once
#include "MyList.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

MyList* createEmpty(DestroyFct f) {
	MyList* v = malloc(sizeof(MyList));
	v->capacitate = 1;
	v->elems = malloc(sizeof(ElemType) * v->capacitate);
	v->length = 0;
	v->dfnc = f;
	return v;
}

void destroyList(MyList* v) {
	for (int i = 0; i < v->length; i++) {
		v->dfnc(v->elems[i]);
	}
	v->length = 0;
	free(v->elems);
	free(v);
}


ElemType get(MyList* v, int poz) {
	return v->elems[poz];
}
ElemType setElem(MyList* v, int poz, ElemType el) {
	ElemType replaced = v->elems[poz];
	v->elems[poz] = el;
	return replaced;
}


int size(MyList* v) {
	return v->length;
}

void add(MyList* v, ElemType el) {
	if (v->length >= v->capacitate) {

		int newCapacity = v->capacitate * 2;
		ElemType* aux = malloc(sizeof(ElemType) * newCapacity);
		for (int i = 0; i < v->length; i++) {
			aux[i] = v->elems[i];
		}
		free(v->elems);
		v->elems = aux;
		v->capacitate = newCapacity;
	}
	v->elems[v->length] = el;
	v->length++;
}
ElemType delete(MyList* v, int poz) {
	//more efficient way - interchange element
	//to be deleted with last element, then remove
	//the last element
	ElemType el = v->elems[poz];
	for (int i = poz; i < v->length - 1; i++) {
		v->elems[i] = v->elems[i + 1];
	}
	v->length--;
	return el;
}

MyList* copyList(MyList* v, CopyFct copyFct) {
	MyList* v_copy = createEmpty(v->dfnc);
	for (int i = 0; i < v->length; i++) {
		ElemType el = get(v, i);
		add(v_copy, copyFct(el));
	}
	return v_copy;
}

void testCreateVector() {
	MyList* v = createEmpty(destroyMaterie);
	assert(size(v) == 0);
	destroyList(v);

}
void testIterate() {
	MyList* v = createEmpty(destroyMaterie);
	Materie* m1 = createMaterie("Acadea", "Grande", 15.5);
	Materie* m2 = createMaterie("Prajitura", "UBB", 17.5);
	Materie* m3 = createMaterie("Tort", "Liceu", 26);

	add(v, m1);
	add(v, m2);
	add(v, m3);

	assert(size(v) == 3);
	Materie* m = get(v, 0);

	assert(strcmp(m->nume, "Acadea") == 0);
	assert(strcmp(m->producator, "Grande") == 0);
	assert(m->cantitate == 15.5);

	destroyList(v);

}

void testCopy() {

	MyList* v1 = createEmpty(destroyMaterie);
	add(v1, createMaterie("Acadea", "Grande", 15.5));
	add(v1, createMaterie("Prajitura", "UBB", 17.5));

	assert(size(v1) == 2);
	MyList* v2 = copyList(v1, copyMaterie);
	assert(size(v2) == 2);
	Materie* m = get(v2, 0);
	assert(strcmp(m->nume, "Acadea") == 0);
	assert(strcmp(m->producator, "Grande") == 0);
	assert(m->cantitate == 15.5);

}