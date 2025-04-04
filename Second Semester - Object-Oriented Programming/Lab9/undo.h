#pragma once
#ifndef UNDO_H
#define UNDO_H

#include "domain.h"
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	// destructorul e pentru  a ne asigura ca daca dau delete se apeleaza destuctorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

//clasa care mosteneste metodele clasei ActiuneUndo
class UndoAdauga : public ActiuneUndo {
	Produs produsaduagat;
	RepoAbs& rep;
public:
	UndoAdauga(RepoAbs& rep, const Produs& p) : rep{ rep }, produsaduagat{ p } {}

	void doUndo() override {
		rep.stergeProdus(produsaduagat.getId());
	}
};

class UndoSterge : public ActiuneUndo {
	Produs produsters;
	RepoAbs& rep;
public:
	UndoSterge(RepoAbs& rep, Produs& p) : rep{ rep }, produsters(p) {};
	void doUndo() override {
		rep.adaugaProdus(produsters);
	}
};

class UndoModifica : public ActiuneUndo {
	Produs produsmodficat;
	RepoAbs& rep;
public:
	UndoModifica(RepoAbs& rep, Produs& p) :rep{ rep }, produsmodficat{ p } {};
	void doUndo() override {
		rep.modificaProdus(produsmodficat);
	}
};

#endif // !UNDO_H