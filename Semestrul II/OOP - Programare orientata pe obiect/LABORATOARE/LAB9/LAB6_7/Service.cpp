#include "Service.h"
#include "Faculty.h"
#include <assert.h>
#include <algorithm>
#include <functional>


void Facultate::addDisciplina(string denumire, int ore, string tip, string profesor)
{
	Disciplina d{ denumire, ore, tip, profesor };
	val.valideaza(d);
	repo.store(d);
	undoActiuni.push_back(new undoAdauga{ repo, d });
}

void Facultate::modifyDisciplina(string denumire, int oreNou, string tipNou, string profesorNou)
{
	
	if (search(denumire).getDenumire() != denumire) throw RepoException{ "\nDisciplina nu exista\n" };


	Disciplina d{ denumire, oreNou, tipNou, profesorNou };
	val.valideaza(d);
	repo.modify(d);
	undoActiuni.push_back(new undoUpdate{ repo, d });
	
}

const Disciplina& Facultate::search(string denumire)
{
	return repo.find(denumire);
}

void Facultate::deleteDisciplina(string denumire)
{

	if (search(denumire).getDenumire() != denumire)throw RepoException{ "\nDisciplina nu exista\n" };
	repo.deleteDisciplina(denumire);
	undoActiuni.push_back(new undoSterge{ repo, repo.find(denumire) });

}


vector<Disciplina> Facultate::filtrareOre(int ore) {
	
	const vector<Disciplina>& allDiscipline = getAllDiscipline();
	vector<Disciplina> filteredDiscipline;
	std::copy_if(allDiscipline.begin(), allDiscipline.end(), back_inserter(filteredDiscipline),
		[ore](const Disciplina& d) {
			return d.getOre() == ore;
		});

	return filteredDiscipline;
}

vector<Disciplina> Facultate::filtrareProfesor(string profesor) {
	
	const vector<Disciplina>& allDiscipline = getAllDiscipline();
	vector<Disciplina> filteredDiscipline;
	std::copy_if(allDiscipline.begin(), allDiscipline.end(), back_inserter(filteredDiscipline),
		[profesor](const Disciplina& d) {
			return d.getProfesor() == profesor;
		});

	return filteredDiscipline;
}

vector<Disciplina> Facultate::filtrareTip(string tip) {
	const vector<Disciplina>& allDiscipline = getAllDiscipline();
	vector<Disciplina> filteredDiscipline;
	std::copy_if(allDiscipline.begin(), allDiscipline.end(), back_inserter(filteredDiscipline),
		[tip](const Disciplina& d) {
			return d.getTip() == tip;
		});

	return filteredDiscipline;
}

vector<Disciplina> Facultate::sortByOre() {
	vector<Disciplina> sortedCopy{ repo.getAllDiscipline() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpOre);
	return sortedCopy;
}

vector<Disciplina> Facultate::sortByDenumire() {
	vector<Disciplina> sortedCopy{ repo.getAllDiscipline() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpDenumire);
	return sortedCopy;
}

vector<Disciplina> Facultate::sortByProfesor() {
	vector<Disciplina> sortedCopy{ repo.getAllDiscipline() };
	sort(sortedCopy.begin(), sortedCopy.end(), cmpProfesor);
	return sortedCopy;
}


void testAddService() {
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	Facultate testService{testRepo,testVal};

	testService.addDisciplina("matematica",5,"real","Berinde");
	testService.addDisciplina("romana", 2, "filolo", "Scarla");
	testService.addDisciplina("SDA", 10, "real", "Czibula");

	assert(testService.getAllDiscipline().size() == 3);
	try {
		testService.addDisciplina("matematica", 10, "n", "Modoi");
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addDisciplina("", 5, "rock", "Alin");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Denumirea trebuie sa aiba cel putin 1 caractere.\n");
	}

	try {
		testService.addDisciplina("Anmr", 0, "rock", "Alin");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Disciplina trebuie sa aiba cel putin 1 ore.\n");
	}

	try {
		testService.addDisciplina("ewgfr", 5, "", "Alin");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Tipul trebuie sa aiba cel putin 1 caractere.\n");
	}

	try {
		testService.addDisciplina("dsagf", 5, "rock", "");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Profesorul trebuie sa aiba cel putin 1 caractere.\n");
	}



}

void testModifyService() {
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	Facultate testService{ testRepo, testVal };

	testService.addDisciplina("matematica", 5, "real", "Berinde");
	assert(testService.getAllDiscipline().size() == 1);


	testService.modifyDisciplina("matematica", 10, "n", "Modoi");

	auto found = testService.search("matematica");
	assert(found.getOre() == 10);
	assert(found.getTip() == "n");
	assert(found.getProfesor() == "Modoi");

	try {
		testService.modifyDisciplina("SDA", 10, "n", "Modoi");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testDeleteService() {
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	Facultate testService{ testRepo, testVal };

	testService.addDisciplina("matematica", 5, "real", "Berinde");
	assert(testService.getAllDiscipline().size() == 1);


	try {
		testService.deleteDisciplina("SDA");
	}
	catch (RepoException&) {
		assert(true);
	}


	testService.deleteDisciplina("matematica");
	assert(testService.getAllDiscipline().size() == 0);
	
}

void testFindService() {
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	Facultate testService{ testRepo,testVal };

	testService.addDisciplina("matematica", 5, "real", "Berinde");
	assert(testService.getAllDiscipline().size() == 1);

	auto found = testService.search("matematica");
	assert(found.getOre() == 5);
	assert(found.getTip() == "real");
	assert(found.getProfesor() == "Berinde");

	try {
		testService.search("SDA");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testFilterService() {
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	Facultate testService{ testRepo, testVal };

	testService.addDisciplina("matematica", 2, "real", "Berinde");
	testService.addDisciplina("romana", 2, "filolo", "Scarla");
	testService.addDisciplina("SDA", 10, "real", "Czibula");

	vector<Disciplina> Discipline3 = testService.filtrareOre(2);
	assert(Discipline3.size() == 2);
	vector<Disciplina> Discipline0 = testService.filtrareOre(5);
	assert(Discipline0.size() == 0);


	vector<Disciplina> disciplineProf = testService.filtrareProfesor("Berinde");
	assert(disciplineProf.size() == 1);
	vector<Disciplina> disciplineProf0 = testService.filtrareProfesor("Andrei");
	assert(disciplineProf0.size() == 0);

}

void testSortService() {

	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	Facultate testService{ testRepo, testVal };

	testService.addDisciplina("matematica", 5, "real", "Berinde");
	testService.addDisciplina("analiza", 2, "filolo", "Scarla");
	testService.addDisciplina("SDA", 10, "real", "Scarla");

	vector<Disciplina> sortedByDenumire = testService.sortByDenumire();
	//cout << sortedByDenumire[1].getDenumire();
	assert(sortedByDenumire[0].getDenumire() == "SDA");
	//assert(sortedByDenumire[1].getDenumire() == "matematica");
	//assert(sortedByDenumire[2].getDenumire() == "SDA");

	vector<Disciplina> sortedByOre = testService.sortByOre();
	assert(sortedByOre[0].getDenumire() == "analiza");
	assert(sortedByOre[1].getDenumire() == "matematica");
	assert(sortedByOre[2].getDenumire() == "SDA");

	vector<Disciplina> sortedByProfesor = testService.sortByProfesor();
	assert(sortedByProfesor[0].getDenumire() == "matematica");
	assert(sortedByProfesor[1].getDenumire() == "analiza");
	assert(sortedByProfesor[2].getDenumire() == "SDA");
}

void testUndo()
{
	DisciplinaRepository testRepo;
	DisciplinaValidator testVal;
	Facultate testService{ testRepo,testVal };

	testService.addDisciplina("seba", 212, "da", "fsega");
	testService.modifyDisciplina("seba", 22, "ay", "ubb");
	testService.deleteDisciplina("seba");
	assert(testService.getAllDiscipline().size() == 0);
	testService.undo();
	assert(testService.getAllDiscipline().size() == 1);
	testService.undo();
	const Disciplina disciplina = testRepo.find("seba");
	assert(disciplina.getOre() == 212);
	testService.undo();
	assert(testService.getAllDiscipline().size() == 0);
	assert(testService.undo() == -1);

}

void testeService() {
	testAddService();
	testModifyService();
	testDeleteService();
	testFindService();
	testFilterService();
	testSortService();
	testUndo();
}