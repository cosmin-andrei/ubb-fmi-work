#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
    private:

		struct Nod {
			TElem e;
			Nod* urm;

			Nod(TElem elem, Nod* urmator)
				: e(elem), urm(urmator) {}
		};

		static const int MAX = 9973; // dimensiunea initiala a tabelei de dispersie
		std::vector<Nod*> l; // vectorul de liste pentru tabela de dispersie
		int m; // dimensiunea tabelei de dispersie
		Relatie rel; // relatia de ordine a cheilor
		typedef Nod* PNod;


		int d(TCheie c) const {
			return std::hash<TCheie>{}(c) % m; // functia de dispersie
		}

    public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

	int adaugaInexistente(MDO& mdo);

};
