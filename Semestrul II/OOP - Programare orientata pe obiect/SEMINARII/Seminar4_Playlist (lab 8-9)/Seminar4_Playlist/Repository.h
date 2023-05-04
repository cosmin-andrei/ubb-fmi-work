#pragma once
#include "Song.h"
#include <vector>
using std::vector;
/*
Clasa de exceptii specifice Repo
*/
class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class SongRepository {
private:
	vector<Song> allSongs;
public:
	
	SongRepository() = default;
	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Repository
	//(in aplicatie avem 1 singur Repo)
	SongRepository(const SongRepository& ot) = delete;
	/*
	Adauga o melodie in lista
	@param s: melodia care se adauga (Song)
	@return -
	post: melodia va fi adaugata in lista

	@throws: RepoException daca o melodie cu acelasi titlu si acelasi artist
			 exista deja 
	*/
	void store(const Song& s);
	/*
	Returneaza o lista cu toate melodiile
	@return: lista cu melodiile (vector of Song objects)
	*/
	const vector<Song>& getAllSongs();
	
	/*
	Cauta o melodie cu titlul si artistul dat

	@param titlu: titlul dupa care se cauta
	@param artist: artistul dupa care se cauta 
	@returns: entitatea Song cu titlul si artistul dat (daca aceasta exista)
	@throws: RepoException daca nu exista melodie cu titlul si artistul dat*/
	const Song& find(string titlu, string artist);

	/*
	Verifica daca o melodie data exista in lista
	
	@param s: melodia care se cauta in lista
	@return: true daca melodia exista, false altfel
	*/
	bool exists(const Song& s);

};

void testeRepo();