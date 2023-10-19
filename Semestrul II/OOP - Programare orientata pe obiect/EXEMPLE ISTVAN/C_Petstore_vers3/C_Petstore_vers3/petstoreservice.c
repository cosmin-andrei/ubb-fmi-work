#include "petstoreservice.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mysort.h"
/*
Add a pet to the store
*/
int addPet(PetStore* store, char* type, char* species, float price) {
	Pet* p = createPet(type, species, price);
	MyList* toUndo = copyList(store->allPets, copyPet);
	add(store->allPets, p);
	//add to undolist
	add(store->undoList, toUndo);
	return 0; // all ok
}

/*
  Restore previous pet list
  return 0 on ok, 1 if there is no more available undo
*/
int undo(PetStore* store) {
	if (size(store->undoList) == 0) {
		return 1;//no more undo
	}
	MyList* l = removeLast(store->undoList);
	destroyList(store->allPets);
	store->allPets = l;
	return 0;
}

/*
Filter pets in the store
typeSubstring - cstring
return all pets where typeSubstring is a substring of the type
*/
MyList* getAllPet(PetStore* store, char* typeSubstring) {
	if (typeSubstring == NULL || strlen(typeSubstring) == 0) {
		return copyList(store->allPets,copyPet);
	}
	MyList* rez = createEmpty(destroyPet);
	for (int i = 0; i < size(store->allPets); i++) {
		Pet* p = get(store->allPets, i);
		if (strstr(p->type, typeSubstring) != NULL) {
			add(rez,copyPet (p));
		}
	}
	return rez;
}

int cmpType(Pet* p1, Pet* p2) {
	return strcmp(p1->type, p2->type);
}

int cmpSpe(Pet* p1, Pet* p2) {
	return strcmp(p1->species, p2->species);
}

/*
 Sort ascending by type
*/
MyList* sortByType(PetStore* store) {
	MyList* l = copyList(store->allPets,copyPet);
	sort(l, cmpType);
	return l;
}

/*
Sort ascending by species
*/
MyList* sortBySpecies(PetStore* store) {
	MyList* l = copyList(store->allPets, copyPet);
	sort(l, cmpSpe);
	return l;
}

PetStore createPetStore()
{
	PetStore rez;
	rez.allPets = createEmpty(destroyPet);
	rez.undoList = createEmpty(destroyList);
	return rez;
}

void destroyStore(PetStore * store)
{
	destroyList(store->allPets);
	destroyList(store->undoList);
}

void testAddPet() {
	PetStore store = createPetStore();
	addPet(&store, "a", "b", 10);
	addPet(&store, "a2", "b2", 20);
	MyList* filtered = getAllPet(&store, NULL);
	assert(size(filtered) == 2);
	destroyList(filtered);

	filtered = getAllPet(&store, "a2");
	assert(size(filtered) == 1);
	destroyList(filtered);

	filtered = getAllPet(&store, "2");
	assert(size(filtered) == 1);
	destroyList(filtered);

	filtered = getAllPet(&store, "a");
	assert(size(filtered) == 2);
	destroyList(filtered);

	destroyStore(&store);
}

void testSorts() {
	PetStore store = createPetStore();
	addPet(&store, "a", "c", 10);
	addPet(&store, "c", "b", 20);
	addPet(&store, "b", "a", 20);
	MyList* l = sortByType(&store);
	Pet* p = get(l, 1);
	assert(strcmp(p->type,"b") == 0);
	destroyList(l);
	l = sortBySpecies(&store);
	p = get(l, 0);
	assert(strcmp(p->species, "a") == 0);
	p = get(l, 1);
	assert(strcmp(p->species, "b") == 0);
	destroyList(l);
	destroyStore(&store);
}

void testUndo() {
	PetStore store = createPetStore();
	addPet(&store, "a", "c", 10);
	addPet(&store, "c", "b", 20);
	undo(&store);
	MyList* l = getAllPet(&store, NULL);
	assert(size(l) == 1);
	destroyList(l);

	undo(&store);
	l = getAllPet(&store, NULL);
	assert(size(l) == 0);
	destroyList(l);

	assert(undo(&store) != 0);
	assert(undo(&store) != 0);
	assert(undo(&store) != 0);

	destroyStore(&store);
}