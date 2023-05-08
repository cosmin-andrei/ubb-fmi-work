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

	undoSterge(DisciplinaRepository& repo, const Disciplina& disciplina) : repo{ repo }, disciplinaStearsa{ disciplina } {}
	void doUndo() override
	{
		auto it = repo.getAllDiscipline().begin();
		repo.deleteDisciplina(disciplinaStearsa.getDenumire());
	}


};


class undoUpdate : public ActiuneUndo
{
	Disciplina disciplinaModificata;
	DisciplinaRepository& repository;

public:
	undoUpdate(DisciplinaRepository& repository, const Disciplina& disciplina) : repository{ repository }, disciplinaModificata{ disciplina } {}
	void doUndo() override
	{
		repository.modify(disciplinaModificata);
	}


};