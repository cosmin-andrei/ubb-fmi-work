#include "Disciplina.h"
#include <assert.h>

string Disciplina::getDenumire() const {
	return this->denumire;
}

int Disciplina::getOre() const {
	return this->ore;
}

string Disciplina::getTip() const {
	return this->tip;
}

string Disciplina::getProfesor() const {
	return this->profesor;
}


void Disciplina::setOre(int oreNou) {
	this->ore = oreNou;
}

void Disciplina::setTip(string tipNou) {
	this->tip = tipNou;
}

void Disciplina::setProfesor(string profesorNou) {
	this->profesor = profesorNou;
}

bool cmpDenumire(const Disciplina& d1, const Disciplina& d2)
{
	return d1.getDenumire() < d2.getDenumire();
}

bool cmpOre(const Disciplina& d1, const Disciplina& d2) {
	return d1.getOre() < d2.getOre();
}

bool cmpProfesor(const Disciplina& d1, const Disciplina& d2) {
	if (d1.getProfesor() == d2.getProfesor())
		return d1.getTip() < d2.getTip();
	else
		return d1.getProfesor() < d2.getProfesor();
}

void testGetSet() {
	Disciplina d1{ "matematica", 5, "reala", "Berinde" };
	assert(d1.getDenumire() == "matematica");
	assert(d1.getOre() == 5);
	assert(d1.getTip() == "reala");
	assert(d1.getProfesor() == "Berinde");

	d1.setOre(6);
	d1.setTip("test");
	d1.setProfesor("Modoi");

	assert(d1.getOre() == 6);
	assert(d1.getTip() == "test");
	assert(d1.getProfesor() == "Modoi");

}

void testeCMP() {
	Disciplina d1{ "matematica", 5, "reala", "Berinde" };
	Disciplina d2{ "romana",3,"uman","Scarlat" };
	Disciplina d3{ "altceva",5,"real","Scarlat" };

	assert(cmpDenumire(d1, d2) == true);
	assert(cmpOre(d1, d2) == false);
	assert(cmpProfesor(d2, d3) == false);
	assert(cmpProfesor(d1, d2) == true);
}

void testeDomain() {
	testGetSet();
	testeCMP();
}