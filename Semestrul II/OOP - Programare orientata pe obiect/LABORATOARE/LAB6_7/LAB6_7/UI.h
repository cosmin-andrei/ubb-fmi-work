#pragma once
#include "Service.h"
class ConsoleUI {
private:
	Facultate& srv;
public:
	ConsoleUI(Facultate& srv) :srv{ srv } {};
	ConsoleUI(const ConsoleUI& ot) = delete;

	void printMenu();
	void uiAdd();
	void uiModify();
	void uiDelete();
	void uiFilter();
	void uiSort();
	void uiSearch();
	void printAll(const vector<Disciplina>& allDiscipline);
	void run();
};