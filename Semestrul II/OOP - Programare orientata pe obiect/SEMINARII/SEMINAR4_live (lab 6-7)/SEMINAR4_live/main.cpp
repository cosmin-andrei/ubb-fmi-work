#include "UI.h"
#include <iostream>
using std::cout;
using std::endl;
void testAll() {
	testeDomain();
	cout << "Finished domain tests." << endl;
	testeRepo();
	cout << "Finished repo tests." << endl;
	testeService();
	cout << "Finished service tests." << endl;

}
void startApp() {
	SongRepository repo;
	SongValidator val;
	SongStore srv{ repo,val };
	ConsoleUI ui{ srv };

	ui.run();
}
int main() {
	testAll();
	startApp();

}