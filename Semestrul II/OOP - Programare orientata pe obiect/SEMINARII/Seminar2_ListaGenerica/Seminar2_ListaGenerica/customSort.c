#pragma once
#include "customSort.h"


/**
* Sorteaza o lista data
* @param v: lista care se sorteaza
* @param cmpF: functia (relatia) dupa care se sorteaza
* 
* post: lista v este sortata
*/
void sort(MyList* v, CompareFct cmpF) {
	int i, j;
	for (i = 0; i < size(v); i++) {
		for (j = i + 1; j < size(v); j++) {
			void* p1 = get(v, i);
			void* p2 = get(v, j);
			if (cmpF(p1, p2) > 0) {
				//interschimbam
				setElem(v, i, p2);
				setElem(v, j, p1);
			}
		}
	}
}
