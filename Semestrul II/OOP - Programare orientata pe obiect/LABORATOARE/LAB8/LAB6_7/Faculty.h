#pragma once
#include "Disciplina.h"
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

using std::vector;
class Faculty {
private:
	vector<Disciplina> disciplineFaculty;
public:
	Faculty() = default;
	/*
	* Adauga o disciplina in Faculty
	* @param d: disciplina care se adauga (Disciplina)
	*
	* post: disciplina va fi adaugata la Faculty
	*/
	void addDisciplinaToFaculty(const Disciplina& d);
	/*
	* Elimina toate disciplinile din Faculty
	* post: Faculty este gol
	*/
	void emptyFaculty();
	/*
	* Adauga un numar random de discipline in Faculty
	*
	* @param originalDiscipline: disciplinele din care se alege (vector<Disciplina>)
	* @param howMany: cate discipline se adauga (int)
	*
	* post: disciplinele sunt adaugate in Faculty-ul curent
	*/
	void addRandomDiscipline(vector<Disciplina> originalDiscipline, int howMany);
	/*
	* Returneaza un vector care contine toate disciplinele din Faculty
	*/
	const vector<Disciplina>& getAllDisciplineFaculty();
};
