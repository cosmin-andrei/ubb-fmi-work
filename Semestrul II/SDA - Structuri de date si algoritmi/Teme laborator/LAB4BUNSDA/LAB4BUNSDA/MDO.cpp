#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {

	this->count = 0;
	this->urmator = NULL;
	this->anterior = NULL;
	this->rel = r;
	this->tabel = new Lista * [capacitate];
	for (int i = 0; i < capacitate; i++) {
		tabel[i] = nullptr;
	}
}


void MDO::adauga(TCheie c, TValoare v) {
	int pozitie = hash(c);
	Lista* lista = tabel[pozitie];
	if (lista == nullptr) {
		lista = new Lista();
		tabel[pozitie] = lista;
	}
	Nod* nod = lista->cauta(c);
	if (nod == nullptr) {
		nod = new Nod(c, v, nullptr);
		lista->adauga(nod);
		count++;
	}
	else {
		nod->valoare.push_back(v);
	}
}

vector<TValoare> MDO::cauta(TCheie c) const {
	int pozitie = hash(c);
	Lista* lista = tabel[pozitie];
	if (lista == nullptr) {
		vector<TValoare> values;
		return values;
	}
	else {
		Nod* nod = lista->cauta(c);
		if (nod == nullptr) {
			vector<TValoare> values;
			return values;
		}
		else {
			return nod->valoare;
		}
	}
}

bool MDO::sterge(TCheie c, TValoare v) {
	int pozitie = hash(c);
	Lista* lista = tabel[pozitie];
	if (lista == nullptr) {
		return false;
	}
	else {
		Nod* nod = lista->cauta(c);
		if (nod == nullptr) {
			return false;
		}
		else {
			bool sters = nod->valoare.erase(v);
			if (nod->valoare.empty()) {
				lista->sterge(nod);
				count--;
			}
			return sters;
		}
	}
}


int MDO::dim() const {
	return count;
}

bool MDO::vid() const {
	return count == 0;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	for (int i = 0; i < capacitate; i++) {
		Lista* lista = tabel[i];
		if (lista != nullptr) {
			delete lista;
		}
	}
	delete[] tabel;
}

int MDO::hash(TCheie c) const {
	return abs(c) % capacitate;
}

MDO::Lista::Lista() {
	this->head = nullptr;
	this->tail = nullptr;
}

void MDO::Lista::adauga(Nod* nod) {
	if (head == nullptr) {
		head = nod;
		tail = nod;
	}
	else {
		tail->urmator = nod;
		nod->anterior = tail;
		tail = nod;
	}
}

void MDO::Lista::sterge(Nod* nod) {
	if (nod == head && nod == tail
