#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include "my_utils.h"
#include "service.h"


void testAll() {
	testCreateDestroy();
	testValideaza();
	testCreateVector();
	testIterate();
	testListVoid();
	
	testSet();
	testCopy();
	testDelete();
	testAddService();
	testFindService();
	
	testDeleteService();
	testModifyService();
	
	testFilterService();
	testSortDurataService();
	testSortArtistService();
	testSortTitluService();
	testSortArtistTitluService();
	testUndo();

	
}

void printAllSongs(MyList* v) {
	if (v->length == 0)
		printf("Nu exista melodii.\n");
	else
	{
		printf("Melodiile curente sunt:\n");
		for (int i = 0; i < size(v); i++) {
			Melodie* m = get(v, i);
			printf("Titlu: %s | Artist: %s | Durata: %d\n", m->titlu, m->artist, m->durata);
		};
	};
}

void printMenu() {
	printf("1. Adauga melodie\n2. Actualizare melodie\n");
	printf("3. Sterge melodie\n4. Afiseaza toate melodiile de la un artist dat\n");
	printf("51. Sorteaza melodiile dupa durata\n");
	printf("52. Sorteaza melodiile dupa titlu\n");
	printf("53. Sorteaza melodiile dupa artist\n");
	printf("54. Sorteaza melodiile dupa artist si titlu\n");

	printf("6. Tipareste toate\n7. Undo\n0. Iesire\n");
}
void uiAdd(SongStore* store) {
	char titlu[30], artist[30];
	int durata;
	char temp;
	scanf_s("%c", &temp, 1);
	printf("Titlul melodiei este:");
	fgets(titlu, 30, stdin);
	printf("Artistul melodiei este:");
	fgets(artist, 30, stdin);
	printf("Durata melodiei este:");
	scanf_s("%d", &durata);
	trimTrailing(titlu);
	trimTrailing(artist);

	int successful = addMelodie(store,titlu,artist,durata);
	if (successful)
		printf("Melodie adaugata cu succes.\n");
	else
		printf("Melodie invalida.\n");

}
void uiModify(SongStore* store) {
	char titlu[30], artist[30];
	int durataNoua;
	char temp;
	scanf_s("%c", &temp, 1);
	printf("Titlul melodiei este:");
	fgets(titlu, 30, stdin);
	printf("Artistul melodiei este:");
	fgets(artist, 30, stdin);
	printf("Noua durata este:");
	scanf_s("%d", &durataNoua);

	trimTrailing(titlu);
	trimTrailing(artist);

	int successful = modifyMelodie(store, titlu, artist, durataNoua);
	if (successful)
		printf("Melodie modificata cu succes.\n");
	else
		printf("Nu exista melodie cu datele date.\n");
}
void uiDelete(SongStore* store) {
	char titlu[30], artist[30];
	char temp;
	scanf_s("%c", &temp, 1);
	printf("Titlul melodiei este:");
	fgets(titlu, 30, stdin);
	printf("Artistul melodiei este:");
	fgets(artist, 30, stdin);

	trimTrailing(titlu);
	trimTrailing(artist);
	int successful = deleteMelodie(store, titlu, artist);
	if (successful)
		printf("Melodie stearsa cu succes.\n");
	else
		printf("Nu exista melodie cu datele date.\n");
}
void uiFilter(SongStore* store) {
	char artist[30];
	char temp;
	scanf_s("%c", &temp, 1);
	printf("Artistul melodiei este:");
	fgets(artist, 30, stdin);
	trimTrailing(artist);
	MyList* filteredList = filterMelodii(store, artist);
	printAllSongs(filteredList);
	destroyList(filteredList);

}
void uiSortByDurata(SongStore* store) {


	MyList* sortedList = sortMelodiiByDurata(store);
	printAllSongs(sortedList);
	destroyList(sortedList);

	
	
}
void uiSortByTitle(SongStore* store) {
	MyList* sortedList = sortMelodiiByTitle(store);
	printAllSongs(sortedList);
	destroyList(sortedList);
}
void uiSortByArtist(SongStore* store) {
	MyList* sortedList = sortMelodiiByArtist(store);
	printAllSongs(sortedList);
	destroyList(sortedList);
}
void uiSortByArtistTitle(SongStore* store) {

	MyList* sortedList = sortMelodiiByArtistTitle(store);
	printAllSongs(sortedList);
	destroyList(sortedList);

}
void uiUndo(SongStore* s) {
	int successful = undo(s);
	if (successful)
		printf("Undo realizat cu succes.\n");
	else
		printf("Nu se mai poate face undo.\n");
}
void run() {
	SongStore store = createSongStore();
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
			uiFilter(&store);
			break;
		case 51:
			uiSortByDurata(&store);
			break;
		case 52:
			uiSortByTitle(&store);
			break;
		case 53:
			uiSortByArtist(&store);
			break;
		case 54:
			uiSortByArtistTitle(&store);
			break;
		case 6:
			printAllSongs(store.allSongs);
			break;
		case 7:
			uiUndo(&store);
			break;
		case 0:
			running = 0;
			destroySongStore(&store);
			break;
		default:
			printf("Comanda invalida!\n");

		}
	}
}
int main() {
	testAll();
	run(); 
	_CrtDumpMemoryLeaks();
}
