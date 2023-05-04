#pragma once
#include "service.h"
#include <assert.h>
#include <string.h>
int addMelodie(MyList* v, char* titlu, char* artist, int durata) {
	Melodie m = createMelodie(titlu, artist, durata);
	int successful = valideazaMelodie(m);
	if (!successful) {
		destroyMelodie(&m);
		return 0;
	}
	add(v, m);
	return 1;

}
int findMelodie(MyList* v, char* titlu, char* artist) {
	int poz_to_delete = -1;
	for (int i = 0; i < v->length; i++) {
		Melodie m = get(v, i);
		if (strcmp(m.titlu, titlu) == 0 && strcmp(m.artist, artist) == 0) {
			poz_to_delete = i;
			break;
		}
	}
	return poz_to_delete;
}
int deleteMelodie(MyList* v, char* titlu, char* artist) {
	int poz_to_delete = findMelodie(v, titlu, artist);
	if (poz_to_delete != -1) {
		Melodie m = delete(v, poz_to_delete);
		destroyMelodie(&m);
		return 1;
	}
	else
		return 0;
}
int modifyMelodie(MyList* v, char* titlu, char* artist, int durataNoua) {
	int poz_to_delete = findMelodie(v, titlu, artist);

	if (poz_to_delete != -1) {
		Melodie melodieNoua = createMelodie(titlu, artist, durataNoua);
		Melodie m = get(v, poz_to_delete);
		destroyMelodie(&m);
		setElem(v, poz_to_delete, melodieNoua);
		return 1;
	}
	else
		return 0;
}
MyList filterMelodii(MyList* v, char* artist) {
	
	if (strcmp(artist, "") != 0) {
		MyList filteredList = createEmpty();
		for (int i = 0; i < v->length; i++) {
			Melodie m = get(v, i);
			if (strcmp(artist, m.artist) == 0)
				add(&filteredList, createMelodie(m.titlu, m.artist, m.durata));
		}
		return filteredList;
	}
	else {
		return copyList(v);
	}
	
}
//MyList sortMelodii(MyList* v) {
//	
//}

void testAddService() {
	MyList v = createEmpty();

	int successful1 = addMelodie(&v, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&v, "", "", 56);
	assert(successful2 == 0);

	int successful3 = addMelodie(&v, "Mercedes Benz", "Janis Joplin", -6);
	assert(successful3 == 0);

	assert(size(&v) == 1);
	Melodie m = get(&v, 0);

	assert(strcmp(m.artist, "Deep Purple") == 0);
	assert(strcmp(m.titlu, "Child in Time") == 0);
	assert(m.durata == 56);
	destroy(&v);


}
void testFindService() {
	MyList v = createEmpty();

	int successful1 = addMelodie(&v, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&v, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful3 = addMelodie(&v, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(&v) == 3);
	int poz = findMelodie(&v, "Kashmir", "Led Zeppelin");

	assert(poz == 1);

	destroy(&v);
	assert(size(&v) == 0);
}
void testModifyService() {
	MyList v = createEmpty();

	int successful1 = addMelodie(&v, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&v, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful3 = addMelodie(&v, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(&v) == 3);
	int modify_success = modifyMelodie(&v, "Kashmir", "Led Zeppelin", 120);
	assert(modify_success == 1);
	int modify_success2 = modifyMelodie(&v, "Comfortably Numb", "Pink Floyd", 25);
	assert(modify_success2 == 0);
	destroy(&v);
}
void testDeleteService() {
	MyList v = createEmpty();

	int successful1 = addMelodie(&v, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&v, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful3 = addMelodie(&v, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(&v) == 3);
	int succesful_del = deleteMelodie(&v, "Kashmir", "Led Zeppelin");
	assert(succesful_del == 1);
	int succesfully_del = deleteMelodie(&v, "Comfortably Numb", "Pink Floyd");
	assert(succesfully_del == 0);
	destroy(&v);
	assert(size(&v) == 0);
}

void testFilterService() {
	MyList v = createEmpty();

	int successful1 = addMelodie(&v, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&v, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful4 = addMelodie(&v, "When The Levee Breaks", "Led Zeppelin", 58);
	assert(successful4 == 1);

	int successful3 = addMelodie(&v, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(&v) == 4);

	MyList filteredList = filterMelodii(&v, "Led Zeppelin");
	assert(size(&filteredList) == 2);
	destroy(&filteredList);

	filteredList = filterMelodii(&v, "Pink Floyd");
	assert(size(&filteredList) == 0);
	destroy(&filteredList);



	filteredList = filterMelodii(&v, "");
	assert(size(&filteredList) == 4);
	destroy(&filteredList);

	destroy(&v);

}
//void testSortService() {
//	MyList v = createEmpty();
//
//	int successful1 = addMelodie(&v, "Child in Time", "Deep Purple", 59);
//	assert(successful1 == 1);
//
//	int successful2 = addMelodie(&v, "Kashmir", "Led Zeppelin", 56);
//	assert(successful2 == 1);
//
//	int successful4 = addMelodie(&v, "When The Levee Breaks", "Led Zeppelin", 58);
//	assert(successful4 == 1);
//
//	int successful3 = addMelodie(&v, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
//	assert(successful3 == 1);
//
//	assert(size(&v) == 4);
//	MyList sortedList = sortMelodii(&v);
//	assert(get(&sortedList, 0).durata == 56);
//	assert(get(&sortedList, 1).durata == 58);
//	assert(get(&sortedList, 2).durata == 59);
//	assert(get(&sortedList, 3).durata == 76);
//
//
//	destroy(&sortedList);
//	destroy(&v);
//}