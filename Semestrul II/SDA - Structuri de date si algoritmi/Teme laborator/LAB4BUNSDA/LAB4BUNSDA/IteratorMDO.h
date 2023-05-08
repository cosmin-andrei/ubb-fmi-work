#pragma once

#include "MDO.h"
#include <exception>

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMDO {
	friend class MDO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMDO(const MDO& d);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;

	/* aici e reprezentarea specifica a iteratorului */
	// indexul curent din tablou
	int curentIndex;
	// nodul curent din lanțul dinamic asociat indexului curent
	Node* curent;
public:

	// repozitioneaza iteratorul la inceputul containerului
	void prim();

	// muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	// verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	// returneaza valoarea elementului din container referit de iterator
	// arunca exceptie daca iteratorul nu e valid
	TElem element() const;
};
