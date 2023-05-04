#include "Song.h"
#include <assert.h>
string Song::getTitlu() const {
	return this->titlu;
}
string Song::getArtist() const {
	return this->artist;
}
string Song::getGen() const {
	return this->gen;
}
double Song::getDurata() const {
	return this->durata;
}

void Song::setArtist(string artistNou) {
	this->artist = artistNou;
}
void Song::setTitlu(string titluNou) {
	this->titlu = titluNou;
}
void Song::setGen(string genNou) {
	this->gen = genNou;
}
void Song::setDurata(double durataNoua) {
	this->durata = durataNoua;
}



bool cmpDurata(const Song& m1, const Song& m2) {
	return m1.getDurata() < m2.getDurata();
}

bool cmpArtistSong(const Song& m1, const Song& m2) {
	if (m1.getArtist() == m2.getArtist())
		return m1.getTitlu() < m2.getTitlu();
	else
		return m1.getArtist() < m2.getArtist();
}


void testGetSet() {
	Song song1{ "Pictures of Home", "Deep Purple","rock",1.22};
	assert(song1.getTitlu() == "Pictures of Home");
	assert(song1.getArtist() == "Deep Purple");
	assert(song1.getGen() == "rock");
	assert(song1.getDurata() == 1.22);

	Song song2{ "Lucky Man", "Emerson, Lake & Palmer","rock",3.44 };
	assert(song2.getTitlu() == "Lucky Man");
	assert(song2.getArtist() == "Emerson, Lake & Palmer");
	assert(song2.getGen() == "rock");
	assert(song2.getDurata() == 3.44);

	song2.setTitlu("Goodbye Blue Sky");
	song2.setArtist("Pink Floyd");
	song2.setGen("psychedelic rock");
	song2.setDurata(5.22);

	assert(song2.getTitlu() == "Goodbye Blue Sky");
	assert(song2.getArtist() == "Pink Floyd");
	assert(song2.getGen() == "psychedelic rock");
	assert(song2.getDurata() == 5.22);



}

void testeDomain() {
	testGetSet();
}