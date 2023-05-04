#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
class Song {
private:
	string titlu;
	string artist;
	string gen;
	double durata;
public:
	Song()=delete;
	Song(string titlu, string artist, string gen, double durata) :titlu{ titlu }, artist{ artist }, gen{ gen }, durata{ durata }{};
	Song(const Song& ot) :titlu{ ot.titlu }, artist{ ot.artist }, gen{ ot.gen }, durata{ ot.durata }{
		//cout << "[SONG] Copy constructor called." << endl; 
	};
	Song& operator=(const Song& ot) {
		this->artist = ot.artist;
		this->gen = ot.gen;
		this->durata = ot.durata;
		this->titlu = ot.titlu;
		return (*this);
	};
	string getTitlu() const;
	string getArtist() const;
	string getGen() const;
	double getDurata() const;

	void setTitlu(string titluNou);
	void setArtist(string artistNou);
	void setGen(string genNou);
	void setDurata(double durataNoua);
};

/*
Compara doua melodii dupa durata

@return: true daca durata melodiei m1 e mai mica decat
		durata melodiei m2, false altfel
*/
bool cmpDurata(const Song& m1, const Song& m2);

/*
Compara doua melodii dupa artist si titlul melodiei
@return: true daca artistul melodiei m1 e inainte (alfabetic) 
		 artistului melodiei m2, false altfel 
		 daca avem acelasi artist, atunci comparam titlurile melodiilor
		 */
bool cmpArtistSong(const Song& m1, const Song& m2);

void testeDomain();