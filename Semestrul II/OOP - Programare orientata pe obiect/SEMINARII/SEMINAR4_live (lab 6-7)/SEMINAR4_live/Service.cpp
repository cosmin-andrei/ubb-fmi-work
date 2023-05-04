#pragma once
#include "Service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
using std::sort;
void SongStore::addSong(string titlu, string artist, string gen, double durata) {
	Song s1{titlu, artist, gen, durata};
	val.valideaza(s1);
	repo.store(s1);

}

vector<Song> SongStore::generalSort(bool(*maiMicF)(const Song&, const Song&)) {
	vector<Song> v{ repo.getAllSongs() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				Song aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}



vector<Song> SongStore::sortByDurata() {
	auto sortedCopy = repo.getAllSongs();
	sort(sortedCopy.begin(), sortedCopy.end(), cmpDurata);
	return sortedCopy;
}

vector<Song> SongStore::sortByArtistSong() {
	return generalSort(cmpArtistSong);
}

vector<Song> SongStore::filter(function<bool(const Song&)> fct) {
	vector<Song> filteredSongs;
	for (const auto& song : repo.getAllSongs()) {
		if (fct(song)) {
			filteredSongs.push_back(song);
		}
	}
	return filteredSongs;
}

vector<Song> SongStore::filtrareGen(string gen) {
	return filter([gen](const Song& m) {
		return m.getGen() == gen;
		});
}

vector<Song> SongStore::filtrareDurata(double durataStart, double durataEnd) {
	return filter([=](const Song& m) {
		return m.getDurata() >= durataStart && m.getDurata() <= durataEnd;
		});
}


void testAddService() {
	SongRepository testRepo;
	SongValidator testVal;
	SongStore testService{ testRepo,testVal};

	testService.addSong("Raisa", "Fly Project", "pop", 3.42);
	testService.addSong("Raisa2", "Fly Project", "pop", 3.42);
	testService.addSong("Raisa3", "Fly Project", "pop", 3.42);

	assert(testService.getAllSongs().size() == 3);
	try {
		testService.addSong("Raisa", "Fly Project", "pop", 3.42);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addSong("Pictures of Home", "Deep Purple", "rock", 1.22);
		assert(true);
	}
	catch (ValidationException&) {
		assert(false);
	}
	
	try {
		testService.addSong("", "Deep Purple", "rock", 2.24);
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages()=="Titlul trebuie sa aiba cel putin 2 caractere.\n");
	}

	
	try {
		testService.addSong("Smoke on the Water", "", "rock", 2.24);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	
	try {
		testService.addSong("High Hopes", "Pink Floyd", "rock", 2.64);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addSong("Child in Time", "Deep Purple", "rock", 16);
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}


}

void testFilterService() {
	SongRepository testRepo;
	SongValidator testVal;
	SongStore testService{ testRepo,testVal };

	testService.addSong("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.addSong("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.addSong("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.addSong("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.addSong("Padure Verde", "Via Daca", "maybe folk", 3.2);

	vector<Song> melodiiFolkRock = testService.filtrareGen("folk-rock");
	assert(melodiiFolkRock.size() == 3);
	vector<Song> melodiiHeavyMetal = testService.filtrareGen("heavy metal");
	assert(melodiiHeavyMetal.size() == 0);


	vector<Song> melodii1 = testService.filtrareDurata(2.15, 3.44);
	assert(melodii1.size() == 2);
	vector<Song> melodii2 = testService.filtrareDurata(9, 10);
	assert(melodii2.size() == 0);

}

void testSortService() {

	SongRepository testRepo;
	SongValidator testVal;
	SongStore testService{ testRepo,testVal };

	testService.addSong("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.addSong("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.addSong("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.addSong("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.addSong("Padure Verde", "Via Daca", "maybe folk", 3.2);

	vector<Song> sortedByDurata = testService.sortByDurata();
	assert(sortedByDurata[0].getTitlu() == "Padure Verde");
	assert(sortedByDurata[1].getTitlu() == "Pasarea Calandrinon");
	assert(sortedByDurata[2].getTitlu() == "Ploile Nu Vin");
	assert(sortedByDurata[5].getTitlu() == "Baba Novak");

	vector<Song> sortedByArtistSong = testService.sortByArtistSong();
	assert(sortedByArtistSong[0].getArtist() == "Alternosfera");
	assert(sortedByArtistSong[0].getTitlu() == "Fantanile");

	assert(sortedByArtistSong[2].getArtist() == "Phoenix");
	assert(sortedByArtistSong[2].getTitlu() == "Apocalipsa");

	assert(sortedByArtistSong[5].getArtist() == "Via Daca");
	assert(sortedByArtistSong[5].getTitlu() == "Padure Verde");






}
void testeService() {
	testAddService();
	testFilterService();
	testSortService();
}