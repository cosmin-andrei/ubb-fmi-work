#pragma once
#include<string>
#include<iostream>
using std::string;
using std::cout;
using std::endl;

class Disciplina {
private:
	string denumire;
	int ore;
	string tip;
	string profesor;

public:
	Disciplina()=default;
	Disciplina(string denumire, int ore, string tip, string profesor): denumire{ denumire }, ore{ ore }, tip{ tip }, profesor{ profesor } {};
	Disciplina(const Disciplina& ot) :denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, profesor{ ot.profesor } {}
	string getDenumire() const;
	int getOre() const;
	string getTip() const;
	string getProfesor() const;

	void setOre(int oreNou);
	void setTip(string tipNou);
	void setProfesor(string profesorNou);
};

bool cmpOre(const Disciplina& d1, const Disciplina& d2);

bool cmpDenumire(const Disciplina& d1, const Disciplina& d2);

bool cmpProfesor(const Disciplina& d1, const Disciplina& d2);

void testeDomain();