#pragma once
#include "UI.h"
#include <iostream>
using namespace std;
void ConsoleUI::printMenu() {
	cout << "Comenzi disponibile:" << endl;
	cout << "1. Adauga melodie" << endl;
	cout << "2. Filtreaza melodii" << endl;
	cout << "3. Sorteaza melodii" << endl;
	cout << "4. Afiseaza toate melodiile" << endl;
	cout << "5. Exit" << endl;
}

void ConsoleUI::uiAdd() {
	string titlu, artist, gen;
	double durata;
	cout << "Titlul melodiei este:";
	getline(cin >> ws, titlu);

	cout << "Artistul melodiei este:";
	getline(cin >> ws, artist);
	cout << "Genul melodiei este:";
	getline(cin >> ws, gen);

	cout << "Durata melodiei (numar real, intre 0.5 si 15, format MM.SS) este:";
	cin >> durata;
	try {
		srv.addSong(titlu, artist,gen, durata);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Melodia nu este valida!" << endl;
		cout << ve.getErrorMessages();
	}

}

void ConsoleUI::uiSort() {
	cout << "Criteriul de sortare este (durata/artist+titlu):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "durata")
		printSongs(srv.sortByDurata());
	else if (criteriu == "artist+titlu")
		printSongs(srv.sortByArtistSong());
	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;

}

void ConsoleUI::uiFilter() {
	cout << "Criteriul de filtrare este (gen/durata):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "gen") {
		cout << "Genul pentru care se afiseaza melodiile:" << endl;
		string searchedGenre;
		cin >> searchedGenre;
		printSongs(srv.filtrareGen(searchedGenre));
	}
	else if (criteriu == "durata") {
		double durataStart, durataEnd;
		cout << "Limita inferioara a duratei:" << endl;
		cin >> durataStart;
		cout << "Limita superioara a duratei:" << endl;
		cin >> durataEnd;

		printSongs(srv.filtrareDurata(durataStart,durataEnd));
	}

	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;
}

void ConsoleUI::printSongs(const vector<Song>& allSongs) {
	
	if (allSongs.size() == 0)
		cout << "Nu exista melodii." << endl;
	else
		for (const auto& song : allSongs) {
			cout << "Titlu: " << song.getTitlu() << " | Artist: " << song.getArtist() << " | Gen: "<<song.getGen()<<" | Durata: " << song.getDurata() << endl;
		}
}


void ConsoleUI::addDefaultSongs() {
	srv.addSong("Pictures of Home", "Deep Purple", "rock", 5.3);
	srv.addSong("Penny Lane", "The Beatles", "indie rock",3.32);
	srv.addSong("Strawberry Fields Forever", "The Beatles", "indie rock",3.48);
	srv.addSong("While my Guitar Gently Weeps", "The Beatles", "indie rock", 4.21);
	srv.addSong("Fata verde", "Phoenix", "rock", 4.31);
	srv.addSong("Vasiliscul si Aspida", "Phoenix", "folk-rock", 7.20);
	srv.addSong("Sat dupa sat", "Robin and the Backstabbers", "alternative rock", 2.51);
	srv.addSong("Linistea", "Om la luna", "acoustic", 5.11);
	
}
void ConsoleUI::run() {
	int running = 1;
	int cmd;
	addDefaultSongs();
	while (running) {
		printMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAdd();
			break;
		case 2:
			uiFilter();
			break;
		case 3:
			uiSort();
			break;
	
		case 4:
			printSongs(srv.getAllSongs());
			break;
		case 5:
			running = 0;
			break;
		default:
			break;
		}

	}
}