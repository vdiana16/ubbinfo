#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

class Nod;

typedef Nod* PNod;

class Nod {
private:
	TElement e;
	PNod urm;

public:
	friend class LO;

	//constructor 
	Nod(TElement e, PNod urm);

	TElement element();

	PNod urmator();
};

class LO {
private:
	friend class Iterator;
private:
	/* aici e reprezentarea */
	//prim este adresa primului element
	PNod prim;
	Relatie rel;
	int lg;
public:
	// constructor
	LO(Relatie r);

	// returnare dimensiune
	int dim() const;

	// verifica daca LO e vida
	bool vida() const;

	// returnare element
	//arunca exceptie daca i nu e valid
	TElement element(int i) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	void adauga(TElement e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
	TElement sterge(int i);

	// cauta element si returneaza prima pozitie pe care apare (sau -1)
	int cauta(TElement e) const;

	// returnare iterator
	Iterator iterator();

	//sterge intre pozitii
	void stergeintre(int p1, int p2);

	//destructor
	~LO();

};
