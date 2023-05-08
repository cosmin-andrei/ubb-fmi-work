#pragma once
#include "Disciplina.h"
#include "Repository.h"
#include <vector>
#include <algorithm>

using std::vector;

class ActiuneUndo {

public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};

};

class undoAdauga : public ActiuneUndo
{
	Disciplina disciplinaAdaugata;
	DisciplinaRepository& repo;

public:
	undoAdauga(DisciplinaRepository& repo, const Disciplina& d) : repo{ repo }, disciplinaAdaugata{ d } {}
	void doUndo() override
	{
		repo.deleteDisciplina(disciplinaAdaugata.getDenumire());
	}

};


class undoSterge : public ActiuneUndo
{
	Disciplina disciplinaStearsa;
	DisciplinaRepository& repo;

public:

	undoSterge(DisciplinaRepository& repo, const Disciplina& disciplina, const string denumire) : repo{ repo }, disciplinaStearsa{ disciplina } {}
	void doUndo() override
	{
		auto it = repo.getAllDiscipline().begin();
		repo.(it, disciplinaStearsa);
	}


};


class undoUpdate : public ActiuneUndo
{
	Disciplina disciplinaModificata;
	AbsRepo* repository;
	int poz;

public:
	undoUpdate(AbsRepo* repository, const Disciplina& disciplina, const int p) : repository{ repository }, disciplinaModificata{ disciplina }, poz{ p } {}
	void doUndo() override
	{
		repository->modifica(disciplinaModificata, poz);
	}


};