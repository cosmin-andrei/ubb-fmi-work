#pragma once

#include "Song.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};
/*
Clasa pentru validarea melodiilor
O melodie este valida daca:
	are titlu format din mai mult de 2 caractere
	are artist format din mai mult de 2 caractere
	durata melodiei este intre 1 si 15;
	formatul in care se da durata este MM.SS, numarul de secunde nu trece de 59
*/
class SongValidator {

public:
	void valideaza(const Song& m) {
		vector<string> errors;
		if (m.getTitlu().length() < 2)
			errors.push_back("Titlul trebuie sa aiba cel putin 2 caractere.");
		if (m.getArtist().length() < 2)
			errors.push_back("Artistul trebuie sa aiba cel putin 2 caractere.");
		if (m.getDurata() < 1 || m.getDurata() > 15)
			errors.push_back("Durata trebuie sa fie intre 1 si 15 minute.");
		if (m.getDurata() - static_cast<int>(m.getDurata()) > 0.59)
			errors.push_back("Formatul duratei este MM.SS. Numarul de secunde nu poate depasi 59.");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};
