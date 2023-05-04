#include "Repository.h"
#include<assert.h>
bool DisciplinaRepository::exists(const Disciplina& d) {
	try {
		find(d.getDenumire());
		return true;
	}

	catch (RepoException) {
		return false;
	}}


const Disciplina& DisciplinaRepository::find(string denumire)
{
	for (const Disciplina& d : this->allDiscipline) {
		if (d.getDenumire() == denumire)
			return d;
	}
throw RepoException("Disciplina nu exista");}

void DisciplinaRepository::store(const Disciplina& d) {
	if (exists(d)) {
		throw RepoException("Disciplina " + d.getDenumire() + " exista deja");
	}
	this->allDiscipline.add(d);
}

void DisciplinaRepository::deleteDisciplina(string denumire) 
{
	for (int i = 0; i < allDiscipline.size(); i++) {
		if (allDiscipline.get(i).getDenumire() == denumire) {
			for (int j = i; j < allDiscipline.size(); j++)
				allDiscipline.set(allDiscipline.get(j + 1), j);
			allDiscipline.sters();
			return;
		}
	}
	throw RepoException("Disciplina nu exista");}

void DisciplinaRepository::modify(Disciplina d) {
	int ok = 0;
	for (auto& i : allDiscipline)
		if (i.getDenumire() == d.getDenumire())
		{
			ok = 1;
			i.setOre(d.getOre());
			i.setTip(d.getTip());
			i.setProfesor(d.getProfesor());
			return;
		}

	throw RepoException("Disciplina nu exista");}

const vector<Disciplina> DisciplinaRepository::getAllDiscipline() 
{
	vector<Disciplina> discipline;
	for (auto disciplina : this->allDiscipline) {
		discipline.push_back(disciplina);
	}
	return discipline;
}

void testAddRepo() {
	DisciplinaRepository testRepo;
	Disciplina d1{ "matematica", 4, "real", "Berinde"};
	testRepo.store(d1);
	assert(testRepo.getAllDiscipline().size() == 1);

	Disciplina d2{ "sisteme", 10, "materie","Vancea"};
	Disciplina d3{ "matematica", 5, "real", "Modoi"};
	try {
		testRepo.store(d3);
	}
	catch (RepoException) {
		assert(true);
	}
}

void testFindRepo() {
	DisciplinaRepository testRepo;

	Disciplina d1{ "matematica", 4, "real", "Berinde" };
	Disciplina d2{ "sisteme", 10, "materie","Vancea" };
	Disciplina d3{ "info", 5, "real", "Modoi" };
	testRepo.store(d1);
	testRepo.store(d2);

	assert(testRepo.exists(d1));
	assert(!testRepo.exists(d3));

	auto found = testRepo.find("matematica");
	assert(found.getOre() == 4);
	assert(found.getTip() == "real");
	assert(found.getProfesor() == "Berinde");

	
	try {
		testRepo.find("SDA");
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Disciplina nu exista");
	}
}

void testModifyRepo() {
	DisciplinaRepository testRepo;
	Disciplina d1{ "matematica", 4, "real", "Berinde" };
	testRepo.store(d1);
	assert(testRepo.getAllDiscipline().size() == 1);

	try {
		Disciplina d{ "SDA", 5, "filo", "Czibula" };
		testRepo.modify(d);}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Disciplina nu exista");
	}

	Disciplina dmodif{ "matematica", 5, "filo","Modoi" };
	testRepo.modify(dmodif);

	auto found = testRepo.find("matematica");
	assert(found.getOre() == 5);
	assert(found.getTip() == "filo");
	assert(found.getProfesor() == "Modoi");


}

void testDeleteRepo() {
	DisciplinaRepository testRepo;
	Disciplina d1{ "matematica", 4, "real", "Berinde" };
	testRepo.store(d1);
	assert(testRepo.getAllDiscipline().size() == 1);

	try {
		testRepo.deleteDisciplina("SDA");
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Disciplina nu exista");
	}

	testRepo.deleteDisciplina("matematica");
	assert(testRepo.getAllDiscipline().size() == 0);
}

void testRepo() {
	testAddRepo();
	testFindRepo();
	testModifyRepo();
	testDeleteRepo();
}