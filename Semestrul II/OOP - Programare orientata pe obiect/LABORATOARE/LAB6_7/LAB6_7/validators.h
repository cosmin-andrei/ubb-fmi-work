#pragma once

#include "Disciplina.h"
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
Clasa pentru validarea disciplinelor
O disciplina este valida daca:
	are denumirea formata din mai mult de 1 caractere
	numarul de ore este mai mare de 1
	are tipul format din mai mult de 1 caractere
	are profesor format din mai mult de 1 caractere
*/
class DisciplinaValidator {

public:
	void valideaza(const Disciplina& d) {
		vector<string> errors;
		if (d.getDenumire().length() < 1)
			errors.push_back("Denumirea trebuie sa aiba cel putin 1 caractere.");
		if (d.getOre() < 1)
			errors.push_back("Disciplina trebuie sa aiba cel putin 1 ore.");
		if (d.getTip().length() < 1)
			errors.push_back("Tipul trebuie sa aiba cel putin 1 caractere.");
		if (d.getProfesor().length() < 1)
			errors.push_back("Profesorul trebuie sa aiba cel putin 1 caractere.");

		
		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};
