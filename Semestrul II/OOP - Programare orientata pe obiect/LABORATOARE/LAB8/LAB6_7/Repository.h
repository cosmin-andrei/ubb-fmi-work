#pragma once
#include "Disciplina.h"
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

class DisciplinaRepository {
private:
	vector<Disciplina> allDiscipline;
public:

	DisciplinaRepository() = default;
	DisciplinaRepository(const DisciplinaRepository& ot) = delete;
	void store(const Disciplina& d);
	const vector<Disciplina> getAllDiscipline();
	const Disciplina& find(string denumire);
	void adaugaDisciplina(Disciplina d);
	void deleteDisciplina(string denumire);
	void modify(Disciplina d);
	bool exists(const Disciplina& s);

};

void testRepo();