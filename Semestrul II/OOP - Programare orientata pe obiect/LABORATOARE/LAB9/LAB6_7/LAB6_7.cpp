#include <iostream>
#include "UI.h"

using std::cout;
using std::endl;

void testAll()
{
	testeDomain();
	testRepo();
	testeService();
	cout << "teste rulate cu succes." << endl;
}

void startApp() {
	DisciplinaRepository repo;
	DisciplinaValidator val;
	Facultate srv{ repo, val };
	ConsoleUI ui{ srv };

	ui.run();
}

int main() {
	testAll();
	startApp();
}