#ifndef  SORT_H_
#define SORT_H_

#include "MyList.h"

/*
* Tipul de functie pentru compararea a doua elemente
* returneaza 0 daca sunt egale, 1 daca el1>el2, -1 altfel
*/
typedef int (*CompareFct)(void* el1, void* el2);
void sort(MyList* v, CompareFct cmpF, int way);

#endif // ! CUSTOMSORT_H_
