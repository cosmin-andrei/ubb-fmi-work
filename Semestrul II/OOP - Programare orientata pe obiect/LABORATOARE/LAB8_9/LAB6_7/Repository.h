#pragma once
#include "Disciplina.h"
#include <vector>

using std::vector;

class AbsRepo {
public:

	virtual void store(const Disciplina& p) = 0;

	virtual void delet(int poz) = 0;

	virtual void modifica(const Disciplina& d, int poz) = 0;

	virtual bool exportFisier(const string filename, const string type);

	virtual vector<Disciplina>& getAllDiscipline() = 0;

	virtual ~AbsRepo() = default;
};


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
	void deleteDisciplina(string denumire);
	void modify(Disciplina d);
	bool exists(const Disciplina& s);

};

void testRepo();