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
    ElemType replacedElement = v->elems[poz];
    v->elems[poz] = el;
    return replacedElement;
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
    MyList* v = createEmpty(destroyTranzactie);
    assert(size(v) == 0);
    destroyList(v);

}

void testIterate() {
    MyList* v = createEmpty(destroyTranzactie);
    Tranzactie* t1 = createTranzactie(2, 12, 50, "intrare", "Plata");
    Tranzactie* t2 = createTranzactie(10, 12, 50, "iesire","Chirie");
    Tranzactie* t3 = createTranzactie(3, 10, 100, "iesire","Alimente");

    add(v, t1);
    add(v, t2);
    add(v, t3);

    assert(size(v) == 3);
    Tranzactie* t = get(v, 0);

    assert(t->ziua == 2);
    assert(t->luna == 12);
    assert(t->suma == 50);
    assert(strcmp(t->tip, "intrare") == 0);
    assert(strcmp(t->descriere, "Plata") == 0);

    destroyList(v);


}

void testCopy() {
    MyList* v1 = createEmpty(destroyTranzactie);
    Tranzactie* createTranzactie();
    add(v1, createTranzactie(2, 12, 50, "intrare", "Plata"));
    add(v1, createTranzactie(10, 12, 50, "iesire", "Chirie"));

    assert(size(v1) == 2);
    MyList* v2 = copyList(v1, copyTranzactie);
    assert(size(v2) == 2);
    Tranzactie* t = get(v2, 0);
    assert(t->ziua == 2);
    assert(t->luna == 12);
    assert(t->suma == 50);
    assert(strcmp(t->tip,"intrare")==0);
    assert(strcmp(t->descriere, "Plata") == 0);

}