#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

//initializeaza iteratorul dat ca argument
//BC=WC=AC=Theta(1)
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	curent = dict.prim;
}

//seteaza iteratorul pe prima pozitie a dictionarului
//BC=WC=AC=Theta(1)
void IteratorDictionar::prim() {
	curent = dict.prim;
}

//seteaza iteratorul pe pozitia urmatoare din dictionar
//BC=WC=AC=Theta(1)
void IteratorDictionar::urmator() {
	if (!valid()) {
		throw std::exception("iteratorul nu e valid");
	}
	else
		curent = curent->urmator;
}

//returneaza elementul curent
//BC=WC=AC=Theta(1)
TElem IteratorDictionar::element() const{
	if (!valid()) {
		throw std::exception("element invalid");
	}
	return curent->key;
}

//verifica daca iteratorul e valid
//BC=WC=AC=Theta
bool IteratorDictionar::valid() const {
	return curent != NULL;
}

