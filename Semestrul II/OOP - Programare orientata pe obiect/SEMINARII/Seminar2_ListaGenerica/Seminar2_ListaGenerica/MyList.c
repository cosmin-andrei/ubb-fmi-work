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
		ElemType* aux = malloc(sizeof(ElemType)*newCapacity);
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
	for (int i = poz; i < v->length-1; i++) {
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
	MyList* v = createEmpty(destroyMelodie);
	assert(size(v) == 0);
	destroyList(v);

}
void testIterate() {
	MyList* v = createEmpty(destroyMelodie);
	Melodie* m1 = createMelodie("Child in Time", "Deep Purple", 56);
	Melodie* m2 = createMelodie("When the Levee Breaks", "Led Zeppelin", 78);
	Melodie* m3 = createMelodie("Whole Lotta Love", "Led Zeppelin", 100);

	add(v, m1);
	add(v, m2);
	add(v, m3);

	assert(size(v) == 3);
	Melodie* m = get(v, 0);

	assert(strcmp(m->artist, "Deep Purple")==0);
	assert(strcmp(m->titlu, "Child in Time")==0);
	assert(m->durata == 56);

	destroyList(v);

}

void testCopy() {
	MyList* v1 = createEmpty(destroyMelodie);
	add(v1, createMelodie("Animal de Prada", "Carla's Dreams", 65));
	add(v1, createMelodie("Anti CSD", "Carla's Dreams", 70));

	assert(size(v1) == 2);
	MyList* v2 = copyList(v1, copyMelodie);
	assert(size(v2) == 2);
	Melodie* m = get(v2, 0);
	assert(strcmp(m->artist, "Carla's Dreams") == 0);
	destroyList(v1);
	destroyList(v2);

}

void testDelete() {
	MyList* v1 = createEmpty(destroyMelodie);
	add(v1, createMelodie("Child in Time", "Deep Purple", 65));
	add(v1, createMelodie("Time", "Pink Floyd", 70));


	assert(size(v1) == 2);
	Melodie* m = delete(v1, 0);

	assert(strcmp(m->titlu, "Child in Time") == 0);
	assert(strcmp(m->artist, "Deep Purple") == 0);
	assert(m->durata == 65);
	destroyMelodie(m);

	assert(size(v1) == 1);
	destroyList(v1);


}
void testSet() {
	MyList* v1 = createEmpty(destroyMelodie);
	add(v1, createMelodie("Paradise City", "GunsNRoses", 100));
	assert(size(v1) == 1);
	Melodie* replaced = setElem(v1,0,  createMelodie("Baba O'riley", "The Who", 120));
	Melodie* m = get(v1, 0);
	assert(strcmp(m->titlu, "Baba O'riley") == 0);
	assert(strcmp(m->artist, "The Who") == 0);
	assert(m->durata == 120);
	destroyMelodie(replaced);
	destroyList(v1);
}
void testListVoid() {
	MyList* songList = createEmpty(destroyMelodie);
	add(songList, createMelodie("Stormbringer", "Deep Purple", 170));
	add(songList, createMelodie("Perfect Strangers", "Deep Purple", 80));

	MyList* songList2 = createEmpty(destroyMelodie);
	add(songList2, createMelodie("Shine on you Crazy Diamond", "Pink Floyd", 34));
	add(songList2, createMelodie("Learning to Fly", "Pink Floyd", 30));
	add(songList2, createMelodie("Tom Sawyer", "Rush", 57));

	MyList* undoList = createEmpty(destroyList);

	add(undoList, songList);
	assert(size(undoList) == 1);
	add(undoList, songList2);
	assert(size(undoList) == 2);
	destroyList(undoList);
}