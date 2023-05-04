#pragma once
#include "service.h"
#include "customSort.h"
#include <assert.h>
#include <string.h>


SongStore createSongStore()
{
	SongStore store;
	store.allSongs = createEmpty(destroyMelodie);
	store.undoList = createEmpty(destroyList);
	return store;
}
void destroySongStore(SongStore* store) {
	destroyList(store->allSongs);
	destroyList(store->undoList);
}
int addMelodie(SongStore* store, char* titlu, char* artist, int durata) {
	Melodie* m = createMelodie(titlu, artist, durata);
	

	int successful = valideazaMelodie(m);
	if (!successful) {
		destroyMelodie(m);
		return 0;
	}
	MyList* toUndo = copyList(store->allSongs, copyMelodie);
	add(store->allSongs, m);
	add(store->undoList, toUndo);

	return 1;

}
int findMelodie(SongStore* store, char* titlu, char* artist) {
	int poz_to_delete = -1;
	
	for (int i = 0; i < store->allSongs->length; i++) {
		Melodie* m = get(store->allSongs, i);
		if (strcmp(m->titlu, titlu) == 0 && strcmp(m->artist, artist) == 0) {
			poz_to_delete = i;
			break;
		}
	}
	return poz_to_delete;
}
int deleteMelodie(SongStore* store, char* titlu, char* artist) {
	int poz_to_delete = findMelodie(store, titlu, artist);
	if (poz_to_delete != -1) {
		MyList* toUndo = copyList(store->allSongs, copyMelodie);
		add(store->undoList, toUndo);

		Melodie* m = delete(store->allSongs, poz_to_delete);
		destroyMelodie(m);
		return 1;
	}
	else
		return 0;
}
int modifyMelodie(SongStore* store, char* titlu, char* artist, int durataNoua) {
	int poz_to_delete = findMelodie(store, titlu, artist);

	if (poz_to_delete != -1) {
		MyList* toUndo = copyList(store->allSongs, copyMelodie);
		add(store->undoList, toUndo);

		Melodie* melodieNoua = createMelodie(titlu, artist, durataNoua);
		Melodie* melodieReplaced = setElem(store->allSongs, poz_to_delete, melodieNoua);
		destroyMelodie(melodieReplaced);
		return 1;
	}
	else
		return 0;
}
MyList* filterMelodii(SongStore* store, char* artist) {
	if (strcmp(artist, "") != 0) {
		MyList* filteredList = createEmpty(destroyMelodie);
		for (int i = 0; i < store->allSongs->length; i++) {
			Melodie* m = get(store->allSongs, i);
			if (strcmp(artist, m->artist) == 0)
				add(filteredList, createMelodie(m->titlu, m->artist, m->durata));
		}
		return filteredList;
	}
	else {
		return copyList(store->allSongs, copyMelodie);
	}
	
}
int cmpDurata(Melodie* m1, Melodie* m2) {
	if (m1->durata == m2->durata)
		return 0;
	if (m1->durata > m2->durata)
		return 1;
	else
		return -1;
}
MyList* sortMelodiiByDurata(SongStore* store) {
	MyList* songList = copyList(store->allSongs, copyMelodie);
	sort(songList, cmpDurata);
	return songList;
}

int cmpTitle(Melodie* m1, Melodie* m2) {
	return strcmp(m1->titlu, m2->titlu);
}
MyList* sortMelodiiByTitle(SongStore* store) {
	MyList* songList = copyList(store->allSongs, copyMelodie);
	sort(songList, cmpTitle);
	return songList;
}

int cmpArtist(Melodie* m1, Melodie* m2) {
	return strcmp(m1->artist, m2->artist);
}
MyList* sortMelodiiByArtist(SongStore* store) {
	MyList* songList = copyList(store->allSongs, copyMelodie);
	sort(songList, cmpArtist);
	return songList;
}

int cmpArtistTitle(Melodie* m1, Melodie* m2) {
	if (strcmp(m1->artist, m2->artist) == 0) {
		return strcmp(m1->titlu, m2->titlu);
	}
	return strcmp(m1->artist, m2->artist);
}
MyList* sortMelodiiByArtistTitle(SongStore* store) {
	MyList* songList = copyList(store->allSongs, copyMelodie);
	sort(songList, cmpArtistTitle);
	return songList;
}

int undo(SongStore* store) {
	if (size(store->undoList) == 0)
		//nothing to undo
		return 0;
	MyList* v = delete(store->undoList, store->undoList->length - 1);
	destroyList(store->allSongs);
	store->allSongs = v;
	return 1;
}

void testAddService() {
	SongStore store = createSongStore();
	int successful1 = addMelodie(&store, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&store, "", "", 56);
	assert(successful2 == 0);

	int successful3 = addMelodie(&store, "Mercedes Benz", "Janis Joplin", -6);
	assert(successful3==0);

	MyList* allSongs = filterMelodii(&store, "");
	assert(size(allSongs) == 1);
	destroyList(allSongs);

	destroySongStore(&store);


}
void testFindService() {
	SongStore store = createSongStore();

	int successful1 = addMelodie(&store, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&store, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful3 = addMelodie(&store, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(store.allSongs) == 3);
	int poz = findMelodie(&store, "Kashmir", "Led Zeppelin");

	assert(poz==1);
	
	destroySongStore(&store);
	
}
void testModifyService() {
	SongStore store = createSongStore();

	int successful1 = addMelodie(&store, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&store, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful3 = addMelodie(&store, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(store.allSongs) == 3);
	int modify_success = modifyMelodie(&store, "Kashmir", "Led Zeppelin", 120);
	assert(modify_success==1);
	int modify_success2 = modifyMelodie(&store, "Comfortably Numb", "Pink Floyd", 25);
	assert(modify_success2 == 0);
	destroySongStore(&store);
}
void testDeleteService() {
	SongStore store = createSongStore();


	int successful1 = addMelodie(&store, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&store, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful3 = addMelodie(&store, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(store.allSongs) == 3);
	int succesful_del = deleteMelodie(&store, "Kashmir", "Led Zeppelin");
	assert(succesful_del == 1);
	int succesfully_del = deleteMelodie(&store, "Comfortably Numb", "Pink Floyd");
	assert(succesfully_del == 0);
	destroySongStore(&store);
}

void testFilterService() {
	SongStore store = createSongStore();

	int successful1 = addMelodie(&store, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&store, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful4 = addMelodie(&store, "When The Levee Breaks", "Led Zeppelin", 58);
	assert(successful4 == 1);

	int successful3 = addMelodie(&store, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(store.allSongs) == 4);

	MyList* filteredList = filterMelodii(&store, "Led Zeppelin");
	assert(size(filteredList) == 2);
	destroyList(filteredList);

	filteredList = filterMelodii(&store, "Pink Floyd");
	assert(size(filteredList) == 0);
	destroyList(filteredList);



	filteredList = filterMelodii(&store, "");
	assert(size(filteredList) == 4);
	destroyList(filteredList);

	destroySongStore(&store);
}
void testSortDurataService() {
	SongStore store = createSongStore();

	int successful1 = addMelodie(&store, "Child in Time", "Deep Purple", 56);
	assert(successful1 == 1);

	int successful2 = addMelodie(&store, "Kashmir", "Led Zeppelin", 56);
	assert(successful2 == 1);

	int successful4 = addMelodie(&store, "When The Levee Breaks", "Led Zeppelin", 58);
	assert(successful4 == 1);

	int successful3 = addMelodie(&store, "(Don't fear) The Reaper", "Blue Oyster Cult", 76);
	assert(successful3 == 1);

	assert(size(store.allSongs) == 4);
	MyList* sortedList = sortMelodiiByDurata(&store);
	Melodie* m0 = get(sortedList, 0);
	Melodie* m1 = get(sortedList, 1);
	Melodie* m2 = get(sortedList, 2);
	Melodie* m3 = get(sortedList, 3);

	assert(m0->durata == 56);
	assert(m1->durata == 56);
	assert(m2->durata == 58);
	assert(m3->durata == 76);


	destroyList(sortedList);
	destroySongStore(&store);

}

void populateSongList(SongStore* store) {
	int successful1 = addMelodie(store, "Child in Time", "Deep Purple", 59);
	assert(successful1 == 1);
	int successful2 = addMelodie(store, "Perfect Strangers", "Deep Purple", 20);
	assert(successful2 == 1);
	int successful3 = addMelodie(store, "Stormbringer", "Deep Purple", 83);
	assert(successful3 == 1);
	int successful4 = addMelodie(store, "Good Times Bad Times", "Led Zeppelin", 25);
	assert(successful4 == 1);
	int successful5 = addMelodie(store, "Ramble on", "Led Zeppelin", 28);
	assert(successful5 == 1);
	int successful6 = addMelodie(store, "High Hopes", "Pink Floyd", 51);
	assert(successful6 == 1);
	int successful7 = addMelodie(store, "Another Brick in the Wall", "Pink Floyd", 52);
	assert(successful7 == 1);
	int successful8 = addMelodie(store, "Money", "Pink Floyd", 63);
	assert(successful8 == 1);
	int successful9 = addMelodie(store, "Learning To Fly", "Pink Floyd", 82);
	assert(successful9 == 1);
	int successful10 = addMelodie(store, "Thunderstruck", "AC/DC", 102);
	assert(successful10 == 1);
}

void testSortArtistService() {
	SongStore store = createSongStore();

	populateSongList(&store);
	assert(size(store.allSongs) == 10);

	MyList* sortedList = sortMelodiiByArtist(&store);
	Melodie* m0 = get(sortedList, 0);
	Melodie* m4 = get(sortedList, 3);
	Melodie* m5 = get(sortedList, 5);
	Melodie* m9 = get(sortedList, 9);

	assert(strcmp(m0->artist, "AC/DC") == 0);
	assert(strcmp(m4->artist, "Deep Purple") == 0);
	assert(strcmp(m5->artist, "Led Zeppelin") == 0);
	assert(strcmp(m9->artist, "Pink Floyd") == 0);


	destroyList(sortedList);
	destroySongStore(&store);

}
void testSortTitluService() {
	SongStore store = createSongStore();

	populateSongList(&store);
	assert(size(store.allSongs) == 10);

	MyList* sortedList = sortMelodiiByTitle(&store);
	Melodie* m0 = get(sortedList, 0);
	Melodie* m1 = get(sortedList, 1);
	Melodie* m2 = get(sortedList, 2);
	Melodie* m3 = get(sortedList, 3);
	Melodie* m4 = get(sortedList, 4);
	Melodie* m5 = get(sortedList, 5);
	Melodie* m6 = get(sortedList, 6);
	Melodie* m7 = get(sortedList, 7);
	Melodie* m8 = get(sortedList, 8);
	Melodie* m9 = get(sortedList, 9);

	assert(strcmp(m0->titlu, "Another Brick in the Wall") == 0);
	assert(strcmp(m1->titlu, "Child in Time") == 0);
	assert(strcmp(m2->titlu, "Good Times Bad Times") == 0);
	assert(strcmp(m3->titlu, "High Hopes") == 0);
	assert(strcmp(m4->titlu, "Learning To Fly") == 0);
	assert(strcmp(m5->titlu, "Money") == 0);
	assert(strcmp(m6->titlu, "Perfect Strangers") == 0);
	assert(strcmp(m7->titlu, "Ramble on") == 0);
	assert(strcmp(m8->titlu, "Stormbringer") == 0);
	assert(strcmp(m9->titlu, "Thunderstruck") == 0);


	destroyList(sortedList);
	destroySongStore(&store);

}
void testSortArtistTitluService() {
	SongStore store = createSongStore();

	populateSongList(&store);
	assert(size(store.allSongs) == 10);

	MyList* sortedList = sortMelodiiByArtistTitle(&store);
	Melodie* m0 = get(sortedList, 0);
	Melodie* m1 = get(sortedList, 1);
	Melodie* m2 = get(sortedList, 2);
	
	Melodie* m5 = get(sortedList, 5);
	
	Melodie* m9 = get(sortedList, 9);

	assert(strcmp(m0->artist, "AC/DC") == 0);
	assert(strcmp(m0->titlu, "Thunderstruck") == 0);

	assert(strcmp(m1->artist, "Deep Purple") == 0);
	assert(strcmp(m1->titlu, "Child in Time") == 0);

	assert(strcmp(m2->artist, "Deep Purple") == 0);
	assert(strcmp(m2->titlu, "Perfect Strangers") == 0);

	assert(strcmp(m5->artist, "Led Zeppelin") == 0);
	assert(strcmp(m5->titlu, "Ramble on") == 0);

	assert(strcmp(m9->artist, "Pink Floyd") == 0);
	assert(strcmp(m9->titlu, "Money") == 0);

	destroyList(sortedList);
	destroySongStore(&store);

}

void testUndo() {
	SongStore store = createSongStore();
	assert(addMelodie(&store, "Don't Stop Believing", "Journey", 59)==1);
	assert(modifyMelodie(&store, "Don't Stop Believing", "Journey", 89) == 1);
	assert(deleteMelodie(&store, "Don't Stop Believing", "Journey") == 1);

	//undo delete
	undo(&store);

	MyList* crtSongList = filterMelodii(&store, "");
	assert(size(crtSongList) == 1);
	Melodie* m = get(crtSongList, 0);
	assert(m->durata == 89);
	destroyList(crtSongList);

	//undo modify
	undo(&store);

	crtSongList = filterMelodii(&store, "");
	assert(size(crtSongList) == 1);
	Melodie* m1 = get(crtSongList, 0);
	assert(m1->durata == 59);
	destroyList(crtSongList);

	//undo add
	undo(&store);
	crtSongList = filterMelodii(&store, "");
	assert(size(crtSongList) == 0);
	destroyList(crtSongList);


	int moreUndo = undo(&store);
	assert(moreUndo == 0);
	destroySongStore(&store);




}