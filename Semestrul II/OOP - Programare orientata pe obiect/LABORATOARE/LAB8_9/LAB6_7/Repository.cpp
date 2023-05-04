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

	vector<Disciplina>::const_iterator f = std::find_if(this->allDiscipline.begin(), this->allDiscipline.end(),
		[=](const Disciplina& d) {
			return d.getDenumire() == denumire;
		});

	if (f != this->allDiscipline.end())
		return (*f);
	else
		throw RepoException("Disciplina nu exista");
}

void DisciplinaRepository::store(const Disciplina& d) {
	if (exists(d)) {
		throw RepoException("Disciplina " + d.getDenumire() + " exista deja");
	}
	this->allDiscipline.push_back(d);
}

void DisciplinaRepository::deleteDisciplina(string denumire) 
{
	auto it = std::find_if(allDiscipline.begin(), allDiscipline.end(), [&](const Disciplina& disciplina) {
		return disciplina.getDenumire() == denumire;
		});
	if (it == allDiscipline.end()) {
		throw RepoException("Disciplina nu exista");
	}
	allDiscipline.erase(it);
}

void DisciplinaRepository::modify(Disciplina d) {
	/*int ok = 0;
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
	*/
	auto it = std::find_if(allDiscipline.begin(), allDiscipline.end(),
		[&d](const Disciplina& disc) { return disc.getDenumire() == d.getDenumire(); });

		if (it != allDiscipline.end()) {
			(*it).setOre(d.getOre());
			(*it).setTip(d.getTip());
			(*it).setProfesor(d.getProfesor());
			return;
		}
		else {
			throw RepoException("Disciplina nu exista");
		}
	}






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