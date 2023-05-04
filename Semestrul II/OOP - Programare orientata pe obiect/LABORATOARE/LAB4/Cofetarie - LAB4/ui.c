#include <stdio.h>
#include "service.h"
#define _CRTDBG_MAP_ALLOC


void testAll() {
    testCreateDestroy();
    testValideaza();
    testCreateVector();
    testIterate();
    testCopy();
    testAddService();
    testDeleteService();
    testModifyService();
    testFilterService();
    testSortService();
    testUndo();

}

void printAll(MyList* v) {
    if (v->length == 0)
        printf("Nu exista materii inregistrate.\n");
    else
    {
        printf("Materiile sunt:\n");
        for (int i = 0; i < size(v); i++)
        {
            Materie* m = get(v, i);
            printf("Nume: %s | Producator: %s | Cantitate %f\n", m->nume, m->producator, m->cantitate);
        }
    }
}

void printMenu() {
    printf("1. Adauga materie\n2. Modifica materie\n");
    printf("3. Sterge materie\n4. Tipareste tot\n");
    printf("5. Vizualizare materii cu cantitate mai mica de X\n");
    printf("0. Iesire\n");
}
void uiAdd(Cofetarie* store) {
    char nume[30], producator[30];
    float cantitate;
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Numele este:");
    scanf_s("%s", nume, 30);
    printf("Producatorul este:");
    scanf_s("%s", producator, 30);
    printf("Cantitatea este:");
    scanf_s("%f", &cantitate);

    int successful = addMaterie(store, nume, producator, cantitate);
    if (successful)
        printf("Materie adaugata cu succes.\n");
    else
        printf("Materie invalida.\n");

}
void uiModify(Cofetarie* store) {
    char nume[30], producator_nou[30];
    float cantitate_noua;
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Numele este:");
    scanf_s("%s", nume, 30);
    printf("Producatorul nou este:");
    scanf_s("%s", producator_nou, 30);
    printf("Cantitatea noua este:");
    scanf_s("%f", &cantitate_noua);

    int successful = modifyMaterie(store, nume, producator_nou, cantitate_noua);
    if (successful)
        printf("Materie modificata cu succes.\n");
    else
        printf("Nu exista materia cu datele date.\n");
}
void uiDelete(Cofetarie* store) {
    char nume[30];
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Numele este:");
    scanf_s("%s", nume, 30);

    int successful = deleteMaterie(store, nume);
    if (successful)
        printf("Materie stearsa cu succes.\n");
    else
        printf("Nu exista materie cu datele date.\n");
}

void uiFilterbyCantitate(Cofetarie* store) {
    float cantitate;
    char temp;
    scanf_s("%c", &temp, 1);
    printf("Cantitatea este:");
    scanf_s("%f", &cantitate);
    MyList* filteredList = filterMateriiCantitate(store, cantitate);
    printAll(filteredList);

}

void FilterByC(Cofetarie* store) {
    printf("Type filter character:");
    char filterStr;
    scanf_s(" %c", &filterStr, 1);
    MyList* filteredL = FilterByString(store, filterStr);
    printAll(filteredL);
}

void uiUndo(Cofetarie* s) {
    int successful = undo(s);
    if (successful)
        printf("Undo realizat cu succes.\n");
    else
        printf("Nu se mai poate face undo.\n");
}

void run() {
    Cofetarie store = createCofetarie();
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
            printAll(store.allMaterii);
            break;
        case 5:
            uiFilterbyCantitate(&store);
            break;
        case 6:
            uiUndo(&store);
            break;
        case 0:
            running = 0;
            break;
        default:
            printf("Comanda invalida!\n");

        }
    }
}
int main() {
    testAll();
    run();
    //_CrtDumpMemoryLeaks();
}