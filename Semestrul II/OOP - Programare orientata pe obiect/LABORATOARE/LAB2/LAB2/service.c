#pragma once
#include "service.h"
#include "customSort.h"
#include <assert.h>
#include <string.h>


TranzactiiStore createTranzactiiStore()
{
    TranzactiiStore store;
    store.allTranzactii = createEmpty(destroyTranzactie);
    return store;
}

void destroyTranzactiiStore(TranzactiiStore* store)
{
    destroyList(store->allTranzactii);
}

int addTranzactie(TranzactiiStore* store, int ziua, int luna, int suma, char* tip, char* descriere) {
    Tranzactie* t = createTranzactie(ziua, luna, suma, tip, descriere);
    int successful = valideazaTranzactie(t);
    if (!successful)
    {
        destroyTranzactie(t);
        return 0;
    }
   
    add(store->allTranzactii, t);

    return 1;
}

int findTranzactie(TranzactiiStore* store, int ziua, int luna, char* descriere) {
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

int deleteTranzactie(TranzactiiStore* store, int ziua, int luna, char* descriere)
{
    int poz_to_delete = findTranzactie(store, ziua, luna, descriere);
    if (poz_to_delete != -1) {
        
        
        Tranzactie* t = delete(store->allTranzactii, poz_to_delete);
        destroyTranzactie(t);
        return 1;
    }
    else
        return 0;
}

int modifyTranzactie(TranzactiiStore* store, int ziua, int luna, int suma, char* tip, char* descriere, char* descriereNoua) {
    int poz_to_delete = findTranzactie(store, ziua, luna, descriere);

    if (poz_to_delete != -1) {
        
        Tranzactie* tranzactieNoua = createTranzactie(ziua,luna, suma , tip, descriereNoua);
        Tranzactie* tranzactieReplaced = setElem(store->allTranzactii, poz_to_delete, tranzactieNoua);
        destroyTranzactie(tranzactieReplaced);
        return 1;
    }
    else
        return 0;
}

MyList* filterTranzactiiSuma(TranzactiiStore* store, int suma) {
    MyList* filteredList = createEmpty(destroyTranzactie);
    for (int i = 0; i < store->allTranzactii->length; i++) {
       Tranzactie* t = get(store->allTranzactii, i);
       if (t->suma > suma)
          add(filteredList, createTranzactie(t->ziua, t->luna , t->suma, t->tip, t->descriere));
        }
    return filteredList;

}

MyList* filterTranzactiiTip(TranzactiiStore* store, char* tip) {
    MyList* filteredList = createEmpty(destroyTranzactie);
    for (int i = 0; i < store->allTranzactii->length; i++) {
        Tranzactie* t = get(store->allTranzactii, i);
        if (strcmp(t->tip, tip)==0)
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

int cmpZi(Tranzactie* t1, Tranzactie* t2)
{
    if (t1->ziua == t2->ziua)
        return 0;
    if (t1->ziua > t2->ziua)
        return 1;
    else
        return -1;
}

MyList* sortTranzactiiBySuma(TranzactiiStore* store) {
    MyList* tranzactiiList = copyList(store->allTranzactii, copyTranzactie);
    sort(tranzactiiList, cmpSuma);
    return tranzactiiList;
}

MyList* sortTranzactiiByZi(TranzactiiStore* store) {
    MyList* tranzactiiList = copyList(store->allTranzactii, copyTranzactie);
    sort(tranzactiiList, cmpZi);
    return tranzactiiList;
}



void testAddService() {
    TranzactiiStore store = createTranzactiiStore();

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
    
    MyList* allTranzactii = filterTranzactiiTip(&store, "");
    assert(size(allTranzactii) == 1);
    destroyList(allTranzactii);

}

void testModifyService()
{
    TranzactiiStore store = createTranzactiiStore();

    int successful1 = addTranzactie(&store, 2, 12, 50,"intrare", "Salariu");
    assert(successful1 == 1);

    int successful2 = addTranzactie(&store, 3, 10, 56, "iesire", "Chirie");
    assert(successful2 == 1);

    int successful3 = addTranzactie(&store, 1, 9, 10,"iesire", "Mancare");
    assert(successful3 == 1);

    assert(size(store.allTranzactii) == 3);
    int modify_success = modifyTranzactie(&store, 1, 9, 10, "iesire", "Mancare", "Porumb");
    assert(modify_success == 1);
    int modify_success2 = modifyTranzactie(&store, 3, 10, 9, "", "", "Familie");
    assert(modify_success2 == 0);
    destroyTranzactiiStore(&store);
}

void testDeleteService()
{
    TranzactiiStore store = createTranzactiiStore();

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
    destroyTranzactiiStore(&store);
}


void testFilterService()
{
    TranzactiiStore store = createTranzactiiStore();
    int successful1 = addTranzactie(&store, 2, 12, 50, "iesire", "Salariu");
    assert(successful1 == 1);

    int successful2 = addTranzactie(&store, 1, 9, 50, "intrare", "Mancare");
    assert(successful2 == 1);

    int successful3 = addTranzactie(&store, 1, 10, 50, "iesire", "Scoala");
    assert(successful3 == 1);

    assert(size(store.allTranzactii) == 3);
    MyList* filteredList = filterTranzactiiSuma(&store, 10);
    assert(size(filteredList) == 2);
    
    MyList* filteredList2 = filterTranzactiiTip(&store, "intrare");
    assert(size(filteredList2) == 1);

    destroyTranzactiiStore(&store);


}