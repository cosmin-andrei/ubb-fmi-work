#pragma once
#include <unordered_map>
#include "Service.h"
class ConsoleUI {
private:
	Facultate& srv;
public:
	ConsoleUI(Facultate& srv) :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;

	void printMenu();
	void printFacultyMenu();
	void uiModify();
	void uiAdd();
	void uiDelete();
	void uiFilter();
	void uiSort();
	void uiSearch();
	void uiReport();
	void printAll(const vector<Disciplina>& allDiscipline);
	void uiFaculty();
	void uiAddToFaculty();
	void uiAddRandomToFaculty();
	void uiEmptyFaculty();
	void addDefaultDiscipline();
	void run();
};