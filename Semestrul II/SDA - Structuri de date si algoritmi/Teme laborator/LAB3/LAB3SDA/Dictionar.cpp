//TAD Dicționar –reprezentare sub forma unei LDI cu perechi (cheie, valoare).

#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"
#include <vector>

//BC = WC = AC = Theta(1)
//Overall= Theta(1)
Dictionar::Dictionar() {
	//initiaza primul si ultimul element
	this->prim = NULL; // pointerul de inceput al LDI
	this->ultim = NULL; // pointerul de final al LDI
	this->dimensiune = 0; //dimensiunea dictionarului
}

//BC=Theta(1)
//WC,AC=Theta(n)
//Overall=Theta(n)
Dictionar::~Dictionar() {
	//elibereaza toate nodurile alocate dinamic din dictionar
	//reseteaza dimensiunea la 0
	Node* curent = this->prim;
	while (curent != NULL) {
		Node* urmator = curent->urmator;
		delete curent;
		curent = urmator;
	}
	this->dimensiune = 0;
}

//BC = Theta(1)
//WC = AC = Theta(n)
// overall Theta(n)
TValoare Dictionar::adauga(TCheie c, TValoare v) {
	//adauga o pereche cheie-valoare in dictionar
	//actualizeaza valoarea existenta pt o cheie data
	Node* curent = this->prim; //initializam un pointer la inceputul listei
	
	//parcurgem lista pentru a verifica daca cheia exista deja
	while (curent != NULL) {
		if (curent->key.first == c) { //daca cheia exista, actualizam valoarea
			TValoare valoare_veche = curent->key.second;
			curent->key.second = v;
			return valoare_veche;
		}
		curent = curent->urmator;
	}

	//daca cheia nu exista in dictionar, cream o noua pereche (cheie-valoare)
	Node* nou = new Node;
	nou->key = std::make_pair(c, v);
	nou->anterior = NULL;
	nou->urmator = NULL;

	//adaugam perechea la sf listei
	if (this->prim == NULL) { //daca lista este vida, prima pereche va fi si ultima
		this->prim = nou;
		this->ultim = nou;
	}
	else { // altfel, adaugam la finalul listei
		this->ultim->urmator = nou;
		nou->anterior = this->ultim;
		this->ultim = nou;
	}

	//crestem dimensiunea dictionarului
	this->dimensiune++;
	return NULL_TVALOARE;
}

//BC=Theta(1)
//WC=AC=Theta(n)
TValoare Dictionar::cauta(TCheie c) const {
	//cauta o cheie si returneaza valoarea asociata 
	//(daca dictionarul contine cheia) sau null
	Node* curent = this->prim; //nodul curent = primul nod al LDI
	//se parcurge lista dublu inlantuita pana cand se gaseste cheia cautata sau se ajunge la finalul listei
	while (curent != NULL) {
		//daca cheia din nodul curent este cheia cautata/se ajunge la finalul listei
		if (curent->key.first == c) {
			return curent->key.second;
		}
		curent = curent->urmator;
	}
	return NULL_TVALOARE;
}

//BC=Theta(1)
//WC=AC=Theta(n)
TValoare Dictionar::sterge(TCheie c) {
	//verifica daca dictionarul este gol
	if (this->prim == NULL) {
		return NULL_TVALOARE;
	}

	//initializam nodul curent cu primul pentru a parcurge LDI
	Node* curent = this->prim;

	//cautam nodul cu cheia c in LDI 
	while (curent != NULL && curent->key.first != c) {
		curent = curent->urmator;
	}
	//daca nu exita un nod cu cheia c in dictionar, returnam NULL
	if (curent == NULL) {
		return NULL_TVALOARE;
	}
	//daca exista un singur nod in dictionar, il stergem
	if (curent == this->prim && curent == this->ultim) {
		this->prim = NULL;
		this->ultim = NULL;
	}
	//daca nodul cu cheia c este primul nod din dictionar, actualizam primul nod si setam anteriorul la null
	else if (curent == this->prim) {
		this->prim = curent->urmator;
		this->prim->anterior = nullptr;
	}
	//daca nodul cu cheia c este ultimul nod din dictionar, actualiza ultimul nod si setam urmatorul null
	else if (curent == this->ultim) {
		this->ultim = curent->anterior;
		this->ultim->urmator = nullptr;
	}
	//daca nodul cu cheia c este din dictionar, actualizam nodurile adiacente
	else {
		curent->anterior->urmator = curent->urmator;
		curent->urmator->anterior = curent->anterior;
	}

	//salvam valoarea nodului sters si eliberam memoria ocupata
	TValoare val_stearsa = curent->key.second;
	delete curent;
	
	//actualizam dimensiunea si returnam valoarea stearsa
	this->dimensiune--;
	return val_stearsa;
}

// returneaza valoarea care apare cel mai frecvent în dicționar. Dacă mai multe valori apar cel mai frecvent, se returnează una (oricare) dintre ele.
// Dacă dicționarul este vid, operațiea returnează NULL_TVALOARE

//BC= Theta(1), WC=AC=Theta(n)
TValoare Dictionar::ceaMaiFrecventaValoare() {

	Node* curent = this->prim;
	if (curent == NULL)
		return NULL_TVALOARE;
	
	int prim = INT_MIN, ultim = INT_MAX, element, countMax=0;
	int* arr = new int(dimensiune * 2);
	while (curent != NULL)
	{
		if (prim == INT_MIN && ultim == INT_MAX)
		{
			prim = ultim = curent->key.second;
			arr[curent->key.second]=1;
		}
		else if (prim > curent->key.second)
		{
			for (int i = curent->key.second + 1; i <= prim; i++)
				arr[i] = 0;
			arr[curent->key.second] = 1;
			prim = curent->key.second;
		}
		else if (ultim < curent->key.second)
		{
			for (int i = ultim + 1; i <= curent->key.second; i++)
				arr[i] = 0;
			arr[curent->key.second] = 1;
			ultim = curent->key.second;
		}
		else
		{
			arr[curent->key.second]++;
		}

		curent = curent->urmator;
	}

	for(int i=prim; i<=ultim; i++)
		if (countMax < arr[i])
		{
			countMax = arr[i];
			element = i;
		}

	return element;

}

//BC=Theta(1)
//WC=AC=Theta(n)
int Dictionar::dim() const {
	int dim = 0;
	Node* curent = this->prim; //pointam spre primul nod din LDI
	//parcurgem LDI
	while (curent != NULL) {
		dim++;
		curent = curent->urmator;
	}
	return dim;
}

//BC=WC=AC=Theta(1)
bool Dictionar::vid() const{
	return prim == NULL;
}

//BC=WC=AC=Theta(1)
IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


