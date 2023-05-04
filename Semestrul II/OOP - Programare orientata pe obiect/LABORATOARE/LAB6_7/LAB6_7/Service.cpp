#include "Service.h"
#include <assert.h>
#include <vector>
#include <algorithm>
#include <functional>

using std::sort;

void Facultate::addDisciplina(string denumire, int ore, string tip, string profesor)
{
	Disciplina d{ denumire, ore, tip, profesor };
	val.valideaza(d);
	repo.store(d);
}

void Facultate::modifyDisciplina(string denumire, int oreNou, string tipNou, string profesorNou)
{
	
	if (search(denumire).getDenumire() != denumire) throw RepoException{ "\nDisciplina nu exista\n" };


	Disciplina d{ denumire, oreNou, tipNou, profesorNou };
	val.valideaza(d);
	repo.modify(d);
	
}

const Disciplina& Facultate::search(string denumire)
{
	return repo.find(denumire);
}

void Facultate::deleteDisciplina(string denumire)
{

	if (search(denumire).getDenumire() != denumire)throw RepoException{ "\nDisciplina nu exista\n" };
	repo.deleteDisciplina(denumire);

}

vector<Disciplina> Facultate::generalSort(bool(*maiMicF)(const Disciplina&, const Disciplina&)) {
	vector<Disciplina> v{ repo.getAllDiscipline() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				Disciplina aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}

vector<Disciplina> Facultate::filter(function<bool(const Disciplina&)> fct) {
	vector<Disciplina> filteredDiscipline;
	for (const auto& disciplina : repo.getAllDiscipline()) {
		if (fct(disciplina)) {
			filteredDiscipline.push_back(disciplina);
		}
	}
	return filteredDiscipline;
}

vector<Disciplina> Facultate::filtrareOre(int ore) {
	return filter([ore](const Disciplina& d) {
		return d.getOre() == ore;
		});
}

vector<Disciplina> Facultate::filtrareProfesor(string profesor) {
	return filter([profesor](const Disciplina& d) {
		return d.getProfesor() == profesor;
		});
}

vector<Disciplina> Facultate::sortByOre() {
	return generalSort(cmpOre);
}

vector<Disciplina> Facultate::sortByDenumire() {
	return generalSort(cmpDenumire);
}

vector<Disciplina> Facultate::sortByProfesor() {
	return generalSort(cmpProfesor);
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


void testeService() {
	testAddService();
	testModifyService();
	testDeleteService();
	testFindService();
	testFilterService();
	testSortService();
}