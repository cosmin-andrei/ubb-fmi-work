#include "petstoreservice.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
Add a pet to the store
*/
int addPet(MyList* l, char* type, char* species, float price) {
	Pet p = createPet(type, species, price);
	int succ = valideaza(p);
	if (succ != 0) return succ;

	add(l, p);	
	return 0; // all ok
}

/*
Filter pets in the store
typeSubstring - cstring
return all pets where typeSubstring is a substring of the type
*/
MyList getAllPet(MyList* l, char* typeSubstring) {
	if (typeSubstring == NULL || strlen(typeSubstring) == 0) {
		return copyList(l);
	}
	MyList rez = createEmpty();
	for (int i = 0; i < size(l); i++) {
		Pet p = get(l, i);
		if (strstr(p.type, typeSubstring) != NULL) {
			add(&rez, p);
		}
	}
	return rez;
}


void testAddPet() {
	MyList l = createEmpty();
	//try to add invalid pets
	int error = addPet(&l, "", "b", 10);
	assert(error != 0);
	assert(size(&l) == 0);

	error = addPet(&l, "a", "", 10);
	assert(error != 0);
	assert(size(&l) == 0);

	error = addPet(&l, "a", "b", -10);
	assert(error != 0);
	assert(size(&l) == 0);

	//try to add some valid pets
	addPet(&l, "a", "b", 10);
	addPet(&l, "a2", "b2", 20);
	MyList filtered = getAllPet(&l, NULL);
	assert(size(&filtered) == 2);

	filtered = getAllPet(&l, "a2");
	assert(size(&filtered) == 1);

	filtered = getAllPet(&l, "2");
	assert(size(&filtered) == 1);

	filtered = getAllPet(&l, "a");
	assert(size(&filtered) == 2);
}