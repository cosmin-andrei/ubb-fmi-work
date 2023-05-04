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
	testCopy();
	
	
	testAddService();
	
	testModifyService();
	
	testDeleteService();
	testFindService();
	testFilterService();
	//testSortService();

}

void printAllSongs(MyList* v) {
	if (v->length == 0)
		printf("Nu exista melodii.\n");
	else
	{
		printf("Melodiile curente sunt:\n");
		for (int i = 0; i < size(v); i++) {
			Melodie m = get(v, i);
			printf("Titlu: %s | Artist: %s | Durata: %d\n", m.titlu, m.artist, m.durata);
		};
	};
}

void printMenu() {
	printf("1. Adauga melodie\n2. Actualizare melodie\n");
	printf("3. Sterge melodie\n4. Afiseaza toate melodiile de la un artist dat\n");
	printf("5. Sorteaza melodiile dupa durata\n6. Tipareste toate\n0. Iesire\n");
}
void uiAdd(MyList* v) {
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

	int successful = addMelodie(v,titlu,artist,durata);
	if (successful)
		printf("Melodie adaugata cu succes.\n");
	else
		printf("Melodie invalida.\n");

}
void uiModify(MyList* v) {
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

	int successful = modifyMelodie(v, titlu, artist, durataNoua);
	if (successful)
		printf("Melodie modificata cu succes.\n");
	else
		printf("Nu exista melodie cu datele date.\n");
}
void uiDelete(MyList* v) {
	char titlu[30], artist[30];
	char temp;
	scanf_s("%c", &temp, 1);
	printf("Titlul melodiei este:");
	fgets(titlu, 30, stdin);
	printf("Artistul melodiei este:");
	fgets(artist, 30, stdin);

	trimTrailing(titlu);
	trimTrailing(artist);
	int successful = deleteMelodie(v, titlu, artist);
	if (successful)
		printf("Melodie stearsa cu succes.\n");
	else
		printf("Nu exista melodie cu datele date.\n");
}
void uiFilter(MyList* v) {
	char artist[30];
	char temp;
	scanf_s("%c", &temp, 1);
	printf("Artistul melodiei este:");
	fgets(artist, 30, stdin);
	trimTrailing(artist);
	MyList filteredList = filterMelodii(v, artist);
	printAllSongs(&filteredList);
	destroy(&filteredList);

}
void uiSort() {

}
void run() {
	MyList songList = createEmpty();
	int running = 1;
	while (running) {
		printMenu();
		int cmd;
		printf("Comanda este:");
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 1:
			uiAdd(&songList);
			break;
		case 2:
			uiModify(&songList);
			break;
		case 3:
			uiDelete(&songList);
			break;
		case 4:
			uiFilter(&songList);
			break;
		case 6:
			printAllSongs(&songList);
			break;
		case 0:
			running = 0;
			destroy(&songList);
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
