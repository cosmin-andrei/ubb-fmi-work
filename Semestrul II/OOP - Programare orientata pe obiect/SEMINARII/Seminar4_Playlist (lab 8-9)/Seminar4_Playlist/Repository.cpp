#include "Repository.h"
#include <assert.h>
bool SongRepository::exists(const Song& s) {
	try {
		find(s.getTitlu(), s.getArtist());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}
const Song& SongRepository::find(string titlu, string artist) {
	/*for (const Song& s : this->allSongs) {
		if (s.getTitlu() == titlu && s.getArtist() == artist) {
			return s;
		}
	}*/
	vector<Song>::iterator f = std::find_if(this->allSongs.begin(), this->allSongs.end(),
		[=](const Song& s) {
		return s.getTitlu() == titlu && s.getArtist() == artist;
		}); 

	if (f != this->allSongs.end())
		return (*f);
	else
		throw RepoException("Melodia cu titlul "+titlu+" si artistul "+artist +" nu exista in lista.\n");
}
void SongRepository::store(const Song& s) {
	if (exists(s)) {
		throw RepoException("Melodia cu titlul " + s.getTitlu() + " si artistul " + s.getArtist() + " nu exista in lista");
	}
	this->allSongs.push_back(s);
}

const vector<Song>& SongRepository::getAllSongs() {
	return this->allSongs;
}

void testAddRepo() {
	SongRepository testRepo;
	Song song1{ "Yamasha", "Alex Velea","pop",3.45 };
	testRepo.store(song1);
	assert(testRepo.getAllSongs().size() == 1);

	Song song2{ "Raisa", "Fly Project", "pop", 3.42 };
	Song song3{ "Yamasha", "Alex Velea", "rock", 4.32 };
	try {
		testRepo.store(song3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}


}
void testFindRepo() {
	SongRepository testRepo;

	Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
	Song song2{ "Highway Star","Deep Purple", "rock",2.44 };
	Song song3{ "Holy Diver","Dio", "rock", 4.45 };
	testRepo.store(song1);
	testRepo.store(song2);

	assert(testRepo.exists(song1));
	assert(!testRepo.exists(song3));

	auto foundSong = testRepo.find("Pictures of Home", "Deep Purple");
	assert(foundSong.getArtist() == "Deep Purple");
	assert(foundSong.getDurata() == 3.24);
	assert(foundSong.getGen() == "rock");


	try {
		testRepo.find("Baba O'riley", "The Who");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage()== "Melodia cu titlul Baba O'riley si artistul The Who nu exista in lista");
	}
}

void testeRepo() {
	testAddRepo();
	testFindRepo();
}