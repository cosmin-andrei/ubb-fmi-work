#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>
//bc, wc, ac = Theta(1)
IteratorColectie::IteratorColectie(const Colectie& _c) : c(_c) {
	
	//constructorul iteratorului
	//setează poziția curentă la primul element diferit de 0

	//curent1 - pozitia curenta a iteratorului in cadrul secventei de elemente egale cu curent2 din vect elems
	//curent2 - pozitia curenta a iteratorului in cadrul vectorului elems

	curent1 = 0;
	curent2 = 0;
}

//bc, wc, ac = Theta(1)
void IteratorColectie::prim() {
	
	//seteaza pozitia curenta a iteratorului la inceputul Colectiei
	curent1 = 0;
	curent2 = 0;
}

//bc, wc, ac = Theta(1)
void IteratorColectie::urmator() {
	
	//muta iteratorul la urmatorul element din Colectie
	//arunca exceptie daca se incearca depasirea limitelor Colectiei

	if (curent2 >= c.n) {
		throw std::exception("iteratorul a depasit limita");
	}
	if (curent1 + 1 < c.elems[curent2] && curent2 < c.n) //poziția următoare a iteratorului este în cadrul aceluiași bloc de elemente
		curent1 = curent1 + 1;
	else {
		curent1 = 0;
		curent2 = curent2 + 1;
	}
	while (curent1 == 0 && c.elems[curent2] == 0)
		curent2 = curent2 + 1;
	
}

//bc, wc, ac = Theta(1)
bool IteratorColectie::valid() const {
	
	// verifica daca iteratorul este valid (curent2 indica un element din Colectie)
	return curent2 < c.dimVect();
	
}

//bc, wc, ac = Theta(1)
TElem IteratorColectie::element() const {
	
	//returneaza elementul din Colectie la pozitia indicata de iterator
	//arunca exceptie daca iteratorul nu este valid

	if (!valid()) {
		throw std::exception("iteratorul nu este valid");
	}
	return c.first + curent2;
}
