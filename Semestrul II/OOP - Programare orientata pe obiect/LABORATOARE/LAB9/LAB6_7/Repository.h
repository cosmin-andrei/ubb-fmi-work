#pragma once
#include "Disciplina.h"
#include <vector>

using std::vector; 

class AbsRepo {
public:

	virtual void store(const Disciplina& d) = 0;
	virtual void sterge(string denumire) = 0;
	virtual void modifica(const Disciplina& d) = 0;
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
	void adaugaDisciplina(Disciplina d);
	void deleteDisciplina(string denumire);
	void modify(Disciplina d);
	bool exists(const Disciplina& s);

};

class FileRepo :public DisciplinaRepository {
private:
	string filename;

	void load_from_file();

	void save_to_file();

public:
	FileRepo() = default;
	explicit FileRepo(string fn);
	//FileRepo(const FileRepo& ot) : Repo(ot) {*this=ot;};

	~FileRepo() override = default;

	void store(const Disciplina& p) override {
		DisciplinaRepository::store(p);
		save_to_file();
	}

	void sterge(string denumire) override {
		DisciplinaRepository::deleteDisciplina(denumire);
		save_to_file();
	}

	void modifica(const Disciplina& d) override {
		DisciplinaRepository::modify(d);
		save_to_file();
	}

};

void testRepo();