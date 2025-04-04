#include "Iterator.h"
#include "LO.h"

#include <iostream>
#include <exception>
using namespace std;


//Teta(1)
Nod::Nod(TElement e, PNod urm) {
	this->e = e;
	this->urm = urm;
}

//Teta(1)
TElement Nod::element() {
	return e;
}

//Teta(1)
PNod Nod::urmator() {
	return urm;
}

//Teta(1)
LO::LO(Relatie r) {
	this->rel = r;
	this->prim = nullptr;
	this->lg = 0;
}

//Teta(1)
int LO::dim() const {
	return lg;
}

//Teta(1)
bool LO::vida() const {
	if (prim != nullptr) {
		return false;
	}
	return true;
}

// Caz favorabil: O(1)
// Caz mediu: O(n)
// Caz defavorabil: O(n)
// Overall: O(n)
// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const{
	if (i < 0 || i >= lg) {
		throw exception("Index invalid");
	}
	int poz = i;
	PNod p = prim;
	while (i > 0) {
		p = p->urm;
		i--;
	}
	return p->e;
}

// Caz favorabil: O(1)
// Caz mediu: O(n)
// Caz defavorabil: O(n)
// Overall: O(n)
// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	if (i < 0 || i >= lg) {
		throw exception();
	}
	TElement aux;
	if (i == 0) {
		aux = prim->e;
		prim = prim->urm;
	}
	else {
		PNod p = prim;
		int poz = 0;
		while (poz < i - 1) {
			p = p->urm;
			poz++;
		}
		PNod temp = p->urm;
		aux = temp->e;
		p->urm = temp->urm;
		delete temp;
	}
	lg--;
	return aux;
}

// Caz favorabil: O(1)
// Caz mediu: O(n)
// Caz defavorabil: O(n)
// Overall: O(n)
// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	PNod p = this->prim;
	int i = 0;
	while ((p != nullptr) && (p->e != e)) {
		p = p->urm;
		i++;
	}
	if (p == nullptr) {
		return -1;
	}
	return i;
}

// Caz favorabil: O(1)
// Caz mediu: O(n)
// Caz defavorabil: O(n)
// Overall: O(n)
// adaugare element in LO
void LO::adauga(TElement e) {
	PNod nou = new Nod(e, nullptr);
	//daca lista e vida se adauga primul element
	if (prim == nullptr) {
		prim = nou;
	}
	else {
		if (rel(e, prim->e))
		{
			nou->urm = prim;
			prim = nou;
		}
		else {
			PNod p = this->prim;
			while (p->urm != NULL && (!rel(e, p->urm->e))) {
				p = p->urm;
			}
			if (p->urm == NULL)
				p->urm = nou;
			else {
				nou->urm = p->urm;
				p->urm = nou;
			}
		}
	}
	lg++;
}

// Teta(1)
// returnare iterator
Iterator LO::iterator(){
	return Iterator(*this);
}

//Teta(n)
//destructor
LO::~LO() {
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urm;
		delete p;
	}
}

//O(contor*n) dar va fi O(n), ignorand factorul contor
void LO::stergeintre(int p1, int p2) {
	int lg = dim();
	if (vida()) {
		throw exception("Lista e vida!");
	}
	if (p1 > p2) {
		throw exception("Pozitii incorecte!");
	}
	if (p1 < 0 || p1 >= dim() || p2 < 0 || p2 >= dim()) {
		throw exception("Pozitii incorecte!");
	}
	int i = 0;
	PNod p = this->prim;
	while (p != nullptr) {
		if (p1 == i) {
			int contor = p2 - p1 + 1;
			while (contor != 0) {
				sterge(i);
				contor--;
			}
			break;
		}
		p = p->urm;
		i++;
	}
}