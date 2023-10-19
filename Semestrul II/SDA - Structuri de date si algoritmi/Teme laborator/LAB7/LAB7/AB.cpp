#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

//Constructor default
//Theta(1)
AB::AB() {
	/* de adaugat */
	this->radacina = nullptr;
}


//copiaza constructorul
//Theta(1)
AB::AB(const AB& ab) {
	/* de adaugat */
	this->radacina = copiazaNoduri(ab.radacina);
}

//constructor cu un singur element
//Theta(1)
AB::AB(TElem e){
	/* de adaugat */
	this->radacina = new Nod(e);
}


//constructor cu subarbori stg dr
//Theta(n+m)
AB::AB(const AB& st, TElem e, const AB& dr){
    	/* de adaugat */
	this->radacina = new Nod(e);
	this->radacina->st = copiazaNoduri(st.radacina);
	this->radacina->dr = copiazaNoduri(dr.radacina);
}


//adauga un subarbore stang
//Theta(n+m)
void AB::adaugaSubSt(const AB& st){
 	/* de adaugat */
	radacina->st = copiazaNoduri(st.radacina);
}

//adauga un subarbore drept
//Theta(n+m)
void AB::adaugaSubDr(const AB& dr){
	/* de adaugat */
	if (this->radacina == NULL) {
		throw exception();
	}

	this->radacina->dr= copiazaNoduri(dr.radacina);

}

//returneaza valoarea elem radacina
//Theta(1)
TElem AB::element() const{
 	/* de adaugat */
	if (vid()) {
		throw exception();
	}
	return radacina->valoare;
}

//returneaza subaroberele stang
//Theta(n+m)
AB AB::stang() const{
	if (vid()) {
		throw exception();
	}
	AB subArboreStang;
	//creeaza o copie a nodului specific si a decedentilor sai
	subArboreStang.radacina = copiazaNoduri(this->radacina->st);
	return subArboreStang;
}

//returneaza arborele drept
//Theta(n+m)
AB AB::drept() const{
	/* de adaugat */
	if (vid()) {
		throw exception();
	}
	AB subArboreDrept;
	subArboreDrept.radacina = copiazaNoduri(this->radacina->dr);
	return subArboreDrept;
}

//destructor
//theta(n)
AB::~AB() {
	elibereazaNoduri(radacina);
}

//Theta(1)
bool AB::vid() const{
	return this->radacina == nullptr;
}


//Theta(1)
IteratorAB* AB::iterator(string s) const {
	if (s=="preordine")
		return new IteratorPreordine(*this);
	if (s=="inordine")
		return new IteratorInordine(*this);
	if (s=="postordine")
		return new IteratorPostordine(*this);
	if (s=="latime")
		return new IteratorLatime(*this);
	return nullptr;
};

//creeaza o copie a unui nod ?i a descenden?ilor acestuia
//Theta(n)
Nod* AB::copiazaNoduri(const Nod* nod) const {
	if (nod == nullptr) {
		return nullptr;
	}
	Nod* copie = new Nod(nod->valoare);
	copie->st = copiazaNoduri(nod->st);
	copie->dr = copiazaNoduri(nod->dr);
	return copie;
}


//elibereaza memorie pentru nod si descendentii sai
//Theta(n)
void AB::elibereazaNoduri(Nod* nod) {
	if (nod == nullptr) {
		return;
	}
	elibereazaNoduri(nod->st);
	elibereazaNoduri(nod->dr);
	delete nod;
}