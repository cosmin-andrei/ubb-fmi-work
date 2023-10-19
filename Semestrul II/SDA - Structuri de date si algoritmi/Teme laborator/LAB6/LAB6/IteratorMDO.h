#pragma once

#include "MDO.h"


class IteratorMDO{
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMDO(const MDO& dictionar);

	const MDO& dict; // referință către dicționarul pe care îl iterează
	int curentLista; // indicele curent al listei în care se află iteratorul
	MDO::PNod curentNod; // nodul curent al iteratorului

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();
		

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};

