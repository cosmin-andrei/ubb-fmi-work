#include "UI.h"
#include<iostream>
using namespace std;
void ConsoleUI::printMenu() {
	cout << "Comenzi:" << endl;
	cout << "1. Adauga disciplina" << endl;
	cout << "2. Modifica disciplina" << endl;
	cout << "3. Sterge disciplina" << endl;
	cout << "4. Cauta disciplina" << endl;
	cout << "5. Afiseaza toate disciplinele" << endl;
	cout << "6. Filtreaza discipline" << endl;
	cout << "7. Sorteaza discipline" << endl;
	cout << "8. Faculty" << endl;
	cout << "0. Exit" << endl;

}

void ConsoleUI::printFacultyMenu() {
	cout << "MENIU FACULTY" << endl;
	cout << "1. Adauga disciplina in Faculty" << endl;
	cout << "2. Adauga discipline random in Faculty" << endl;
	cout << "3. Goleste Faculty" << endl;
	cout << "4. Afiseaza Faculty curent" << endl;
	cout << "5. Inapoi la meniul principal" << endl;
}


void ConsoleUI::uiAdd() {
	string denumire, tip, profesor;
	int ore;

	cout << "Denumirea disciplinei este:";
	getline(cin >> ws, denumire);

	cout << "Numarul de ore pe saptamana al disciplinei este:";
	cin >> ore;

	cout << "Tipul disciplinei este:";
	getline(cin >> ws, tip);

	cout << "Profesorul disciplinei este:";
	getline(cin >> ws, profesor);

	try {
		srv.addDisciplina(denumire, ore, tip, profesor);
		cout << "disciplina adaugata cu succes";
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
}

void ConsoleUI::uiModify() {
	string denumire, tip, profesor;
	int ore;

	cout << "Denumirea disciplinei este:";
	getline(cin >> ws, denumire);

	cout << "Numarul de ore nou pe saptamana al disciplinei este:";
	cin >> ore;

	cout << "Tipul nou al disciplinei este:";
	getline(cin >> ws, tip);

	cout << "Profesorul nou al disciplinei este:";
	getline(cin >> ws, profesor);

	try {
		srv.modifyDisciplina(denumire, ore, tip, profesor);
		cout << "disciplina modificata cu succes";
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}

}

void ConsoleUI::uiDelete() {
	
	string denumire;
	cout << "Denumirea disciplinei este:";
	getline(cin >> ws, denumire);

	try {
		srv.deleteDisciplina(denumire);
		cout << "disciplina stearsa cu succes";
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}

}

void ConsoleUI::uiSort() {
	cout << "Criteriul de sortare este: ";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "denumire")
		printAll(srv.sortByDenumire());
	else if (criteriu == "ore")
		printAll(srv.sortByOre());
	else if (criteriu == "profesor")
		printAll(srv.sortByProfesor());
	else
		cout << "Nu se poate sorta dupa criteriul dat";
}

void ConsoleUI::uiFilter() {
	cout << "Criteriul de filtrare este: ";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "ore") {
		cout << "Numarul de ore dupa care se filtreaza:";
		int ore;
		cin >> ore;
		printAll(srv.filtrareOre(ore));
	}
	else if (criteriu == "profesor") {
		cout << "Profesorul dupa care se filtreaza:";
		string profesor;
		cin >> profesor;
		printAll(srv.filtrareProfesor(profesor));
	}
	else
		cout << "Nu se poate filtra dupa criteriul dat";
}

void ConsoleUI::uiSearch() {
	string denumire;

	cout << "Denumirea disciplinei este:";
	getline(cin >> ws, denumire);
	
	try {
		Disciplina disciplina = srv.search(denumire);
		cout << "Denumire: " << disciplina.getDenumire() << " | Numar ore: " << disciplina.getOre() << " | Tip: " << disciplina.getTip() << " | Profesor: " << disciplina.getProfesor() << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
}


void ConsoleUI::printAll(const vector<Disciplina>& allDiscipline) {
	if (allDiscipline.size() == 0)
		cout << "Nu exista discipline." << endl;
	else
		for (const auto& disciplina : allDiscipline) {
			cout << "Denumire: " << disciplina.getDenumire() << " | Numar ore: " << disciplina.getOre() << " | Tip: " << disciplina.getTip() << " | Profesor: " << disciplina.getProfesor() << endl;
		}
}

void ConsoleUI::uiAddToFaculty() {
	string denumire;
	cout << "Denumirea disciplinei este:";
	getline(cin >> ws, denumire);

	try {
		srv.addToFaculty(denumire);
		cout << "Disciplina s-a adaugat cu succes" << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	//catch (ValidationException& ve) {
		//cout << "Disciplina nu este valida!" << endl;
		//cout << ve.getErrorMessages();
	//}
}
void ConsoleUI::uiAddRandomToFaculty() {
	int howManyToAdd;
	cout << "Cate discipline sa se adauge in Faculty?";
	cin >> howManyToAdd;


	try {
		int howManyAdded = srv.addRandomToFaculty(howManyToAdd);
		cout << "S-au adaugat " << howManyAdded << " discipline in Faculty." << endl;
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
}


void ConsoleUI::uiEmptyFaculty() {
	srv.emptyFaculty();
	cout << "S-au sters toate disciplinele din Faculty-ul curent." << endl;
}

void ConsoleUI::uiReport() {
	unordered_map<string, int> map;
	map = srv.report();
	for (const auto& x : map)
		cout << x.first << " " << x.second << endl;

}

void ConsoleUI::uiFaculty() {
	int cmd;
	addDefaultDiscipline();
	int runningFaculty = 1;
	while (runningFaculty) {
		printFacultyMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAddToFaculty();
			break;
		case 2:
			uiAddRandomToFaculty();
			break;
		case 3:
			uiEmptyFaculty();
			break;
		case 4:
			printAll(srv.getDisciplineFaculty());
			break;
		case 5:
			uiReport();
		case 6:
			runningFaculty = 0;
			break;
		default:
			break;
		}

	}
}

void ConsoleUI::addDefaultDiscipline() {
	srv.addDisciplina("Matematica", 5, "real", "Robu");
	srv.addDisciplina("Romana", 3, "uman", "Scarlat");
	srv.addDisciplina("Latina", 1, "uman", "Epure");
	srv.addDisciplina("Sport", 2, "social", "Cosmin");
	srv.addDisciplina("Educatie antreprenoriala", 2, "socio-uman", "Ghita");
	srv.addDisciplina("Chimie", 3, "real","Petrea");
	srv.addDisciplina("Fizica", 2,"real","Tanase");
	srv.addDisciplina("Biologie", 10,"uman","Ispas");

}



void ConsoleUI::run() 
{
	int running = 1;
	int cmd;
	while (running) {
		printMenu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiAdd();
			break;
		case 2:
			uiModify();
			break;
		case 3:
			uiDelete();
			break;
		case 4:
			uiSearch();
			break;
		case 5:
			printAll(srv.getAllDiscipline());
			break;
		case 6:
			uiFilter();
			break;
		case 7:
			uiSort();
			break;
		case 8:
			uiFaculty();
			break;
		case 0:
			running = 0;
			break;
		default:
			break;

		}
	}
}
