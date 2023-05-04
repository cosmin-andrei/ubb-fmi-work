#include <stdio.h>
#include "service.h"


void testAll() {
    testCreateDestroy();
    testValideaza();
    testCreateVector();
    testIterate();
    testCopy();
    testAddService();
    testModifyService();
    testDeleteService();
    testFilterService();
}

void printAll(MyList* v) {
    if (v->length == 0)
        printf("Nu exista tranzactii inregistrate.\n");
    else
    {
        printf("Tranzactiile sunt:\n");
        for (int i = 0; i < size(v); i++)
        {
            Tranzactie* t = get(v, i);
            printf("Ziua: %d | Luna: %d | Suma: %d | Descriere: %s\n", t->ziua, t->luna, t->suma, t->descriere);
        }
    }
}

void printMenu() {
    printf("1. Adauga tranzactie\n2. Actualizare tranzactie\n");
    printf("3. Sterge tranzactie\n4. Tipareste tot\n");
    printf("5. Vizualizare tranzactii mai mari de X lei\n");
    printf("6. Vizualizare tranzactii de un anumit tip");
    printf("7.Vizualizare dupa suma\n8.Vizualizare dupa zi");
    printf("0. Iesire\n");
}
void uiAdd(TranzactiiStore* store) {
    int ziua, luna, suma;
    char descriere[30], tip[8];
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Ziua este:");
    scanf_s("%d", &ziua);
    printf("Luna este:");
    scanf_s("%d", &luna);
    printf("Suma este:");
    scanf_s("%d", &suma);
    printf("Tipul este:");
    scanf_s("%s", tip, 8);
    printf("Descrierea este:");
    scanf_s("%s", descriere, 30);

    int successful = addTranzactie(store, ziua, luna, suma, tip, descriere);
    if (successful)
        printf("Tranzactie adaugata cu succes.\n");
    else
        printf("Tranzactie invalida.\n");

}
void uiModify(TranzactiiStore* store) {
    int ziua, luna, suma;
    char descriere[30], descriereNoua[30], tip[8];
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Ziua este:");
    scanf_s("%d", &ziua);
    printf("Luna este:");
    scanf_s("%d", &luna);
    printf("Suma este:");
    scanf_s("%d", &suma);
    printf("Tipul este:");
    scanf_s("%s", tip, 8);
    printf("Descrierea este:");
    scanf_s("%s", descriere, 30);
    printf("Descrierea noua este:");
    scanf_s("%s", descriereNoua, 30);

    int successful = modifyTranzactie(store, ziua, luna, suma, tip, descriere, descriereNoua);
    if (successful)
        printf("Tranzactie modificata cu succes.\n");
    else
        printf("Nu exista tranzactie cu datele date.\n");
}
void uiDelete(TranzactiiStore* store) {
    int ziua, luna;
    char descriere[30];
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Ziua este:");
    scanf_s("%d", &ziua);
    printf("Luna este:");
    scanf_s("%d", &luna);
    printf("Descrierea este:");
    scanf_s("%s", descriere, 30);

    int successful = deleteTranzactie(store, ziua, luna, descriere);
    if (successful)
        printf("Tranzactie stearsa cu succes.\n");
    else
        printf("Nu exista tranzactie cu datele date.\n");
}

void uiFilterbySuma(TranzactiiStore* store) {
    int suma;
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Suma este:");
    scanf_s("%d", &suma);
    MyList* filteredList = filterTranzactiiSuma(store, suma);
    printAll(filteredList);

}

void uiFilterbyTip(TranzactiiStore* store) {
    char tip[8];
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Tipul este:");
    scanf_s("%s", tip, 8);
    MyList* filteredList = filterTranzactiiTip(store, tip);
    printAll(filteredList);

}


void uiSortBySuma(TranzactiiStore* store) {

    MyList* sortedList = sortTranzactiiBySuma(store);
    printAll(sortedList);
    destroyList(sortedList);
}

void uiSortByZi(TranzactiiStore* store) {

    MyList* sortedList = sortTranzactiiByZi(store);
    printAll(sortedList);
    destroyList(sortedList);
}


void run() {
    TranzactiiStore store = createTranzactiiStore();
    int running = 1;
    while (running) {
        printMenu();
        int cmd;
        printf("Comanda este:");
        scanf_s("%d", &cmd);
        switch (cmd) {
        case 1:
            uiAdd(&store);
            break;
        case 2:
            uiModify(&store);
            break;
        case 3:
            uiDelete(&store);
            break;
        case 4:
            printAll(store.allTranzactii);
            break;
        case 5:
            uiFilterbySuma(&store);
            break;
        case 6:
            uiFilterbyTip(&store);
            break;
        case 7:
            uiSortBySuma(&store);
            break;
        case 8:
            uiSortByZi(&store);
        case 0:
            running = 0;
            break;
            destroyTranzactiiStore(&store);
        default:
            printf("Comanda invalida!\n");

        }
    }
}
int main() {
    testAll();
    run();
}