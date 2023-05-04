#pragma once

#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie,TValoare> TElem;

//un nod dintr-o LDI
struct Node {
	TElem key; //valoarea stocata
	Node* urmator; //urmatorul nod
	Node* anterior; //nodul anterior
};

class Dictionar {
	friend class IteratorDictionar;

	private:
		
		Node* prim;
		Node* ultim;
		int dimensiune;

	public:

	// constructorul implicit al dictionarului
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	TValoare ceaMaiFrecventaValoare();

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	int dim() const;

	//verifica daca dictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe dictionar
	IteratorDictionar iterator() const;
	

	// destructorul dictionarului	
	~Dictionar();

};


