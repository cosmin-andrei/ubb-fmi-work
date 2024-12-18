﻿#pragma once
#include "Repository.h"
#include "validators.h"
#include <functional>

using std::function;
class Facultate {
private:
	DisciplinaRepository& repo;
	DisciplinaValidator& val;

	/*
	Filtreaza */

	vector<Disciplina> filter(function<bool(const Disciplina&)> fct);

	/*
	* Functie de sortare proprie
	*
	* @param maiMicF: functia de comparare folosita pentru sortare
	*
	* @return: lista de melodii sortata dupa criteriul dat (vector cu elemente de
	*			tip Song)
	*/
	vector<Disciplina> generalSort(bool(*maiMicF)(const Disciplina&, const Disciplina&));



public:
	Facultate(DisciplinaRepository& disciplinaRepo, DisciplinaValidator& disciplinaVal) :repo{ disciplinaRepo }, val{ disciplinaVal } {};

	//constructor de copiere
	Facultate(const Facultate& ot) = delete;

	/*
	Adauga o disciplina cu numele nume, numărul de ore ore, tipul tip și cadrul didactic profesor
	*@param nume: numele disciplinei care se adauga (string)
	*@param ore: numarul de ore pe saptamana al disciplinei care se adauga (int)
	*@param tip: tipul disciplinei care se adauga (string)
	*@param profesor: profesorul disciplinei care se adauga (string)
	*
	* @throws:
	*	RepoException daca mai exista disciplina cu numele dat
	*/

	void addDisciplina(string denumire, int ore, string tip, string profesor);

	/*
	* Modificam o disciplina cu identificator unic nume
	* @param nume: numele materiei unic identificabile (string)
	* @param oreNou: numarul de ore nou (int)
	* @param tipNou: tipul nou al disciplinei (string)
	* @param profesorNou: profesorul nou asignat disciplinei (string)
	* 
	* @throws
	*	RepoExepction daca disciplina nu exista
	*/

	void modifyDisciplina(string denumire, int oreNou, string tipNou, string profesorNou);

	/*
	* Sterge o disciplina existenta
	* @param nume: numele disciplinei unic identificabile (string)
	*
	* @throws
	*	RepoException daca disciplina nu exista
	*/
	
	void deleteDisciplina(string denumire);

	const Disciplina& search(string denumire);

	/*
	Returneaza un vector cu toate disciplinele disponibile

	@return: lista cu toate disciplinele disponibile (vector cu obiecte de tip Song)
	*/

	const vector <Disciplina> getAllDiscipline() {
		return this->repo.getAllDiscipline();
	}

	vector<Disciplina> filtrareOre(int Ore);

	
	vector<Disciplina> filtrareProfesor(string profesor);

	
	vector<Disciplina> sortByOre();

	
	vector<Disciplina> sortByDenumire();

	vector<Disciplina> sortByProfesor();


};
void testeService();