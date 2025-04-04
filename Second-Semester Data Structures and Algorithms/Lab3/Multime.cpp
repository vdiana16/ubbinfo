#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

//Complexitate:Teta(cap)
Multime::Multime() {
	this->rad = NULL_TELEM;
	this->lg = 0;
	this->primLiber = 0;
	this->cap = CAPACITATE;
	this->element = new TElem[cap];
	this->stanga = new int[cap];
	this->dreapta = new int[cap];
	initSpatiuLiber();
}

//Teta(cap)
void Multime::initSpatiuLiber() {
	for (int i = 0; i < CAPACITATE; i++) {
		stanga[i] = i + 1;
	}
	stanga[cap - 1] = NULL_TELEM;
}

//Complexitate:Teta(1) amortizat
int Multime::aloca() {
	//se sterge primul element din lista spatiului liber
	if (primLiber == NULL_TELEM) {
		redimensionare();
	}
	int i = primLiber;
	primLiber=stanga[primLiber];
	return i;
}

//Complexitate:Teta(1)
void Multime::dealoca(int i) {
	// se trece pozitia i in lista spatiului liber
	stanga[i] = primLiber;
	primLiber = i;
}

//Complexitate:Teta(cap)
void Multime::redimensionare() {
	int capNoua = cap * 2;
	TElem* elementeaux = new TElem[capNoua];
	int* stangaux = new int[capNoua];
	int* dreaptaux = new int[capNoua];

	for (int i = 0; i < cap; i++) {
		elementeaux[i] = element[i];
		stangaux[i] = stanga[i];
		dreaptaux[i] = dreapta[i];
	}

	for (int i = cap; i < capNoua; i++) {
		elementeaux[i] = NULL_TELEM;
		dreaptaux[i] = NULL_TELEM;
		stangaux[i] = i + 1;
	}

	stangaux[capNoua - 1] = NULL_TELEM;

	delete[] element;
	delete[] stanga;
	delete[] dreapta;

	primLiber = cap;
	cap = capNoua;
	element = elementeaux;
	stanga = stangaux;
	dreapta = dreaptaux;
}


//Caz favorabil: Teta(1)
// Caz defavorabil: Teta(h)
// Caz mediu: Teta(h)
//O(h)
bool Multime::adauga(TElem e) {
	if (rad == NULL_TELEM) {
		rad = aloca();
		element[rad] = e;
		stanga[rad] = NULL_TELEM;
		dreapta[rad] = NULL_TELEM;
		lg++;
		return true;
	}

	int curent = rad;
	int parinte = NULL_TELEM;
	while (curent != NULL_TELEM) {
		if (element[curent] == e) {
			return false;
		}
		parinte = curent;
		if (rel(e, element[curent])) {
			curent = stanga[curent];
		}
		else {
			curent = dreapta[curent];
		}
	}

	int nou = aloca();
	element[nou] = e;
	stanga[nou] = NULL_TELEM;
	dreapta[nou] = NULL_TELEM;

	if (rel(e, element[parinte])) {
		stanga[parinte] = nou;
	}
	else {
		dreapta[parinte] = nou;
	}
	lg++;
	return true;
}

// Complexitate:O(h)
int Multime::minim(int p) {
	while (stanga[p] != NULL_TELEM) {
		p = stanga[p];
	}
	return p;
}

//Caz favorabil: Teta(1)
// Caz defavorabil: Teta(h)
// Caz mediu: Teta(h)
// Complexitate:O(h)
bool Multime::sterge(TElem e) {
	int curent = rad;
	int parinte = NULL_TELEM;
	while (curent != NULL_TELEM && element[curent] != e) {
		parinte = curent;
		if (rel(e, element[curent])) {
			curent = stanga[curent];
		}
		else {
			curent = dreapta[curent];
		}
	}

	if (curent == NULL_TELEM) {
		return false;
	}
	
	//daca nodul are cel mult un copil nodul de sters e nodul curent
	int nodDeSters;
	if (stanga[curent] == NULL_TELEM || dreapta[curent] == NULL_TELEM) {
		nodDeSters = curent;
	}
	else {
		nodDeSters = minim(dreapta[curent]);
		int c = rad;
		while (element[c] != element[nodDeSters]) {
			parinte = c;
			if (rel(element[nodDeSters], element[c]))
				c = stanga[c];
			else c = dreapta[c];
		}
	}

	//determin copilul nodului de sters
	int copil;
	if (stanga[nodDeSters] != NULL_TELEM) {
		copil = stanga[nodDeSters];
	}
	else {
		copil = dreapta[nodDeSters];
	}

	//rearanjez arborele dupa stergere
	if (copil != NULL_TELEM) {
		if (nodDeSters == rad) {
			rad = copil;
		}
		else {
			if (stanga[parinte] == nodDeSters) {
				stanga[parinte] = copil;
			}
			else {
				dreapta[parinte] = copil;
			}
		}
	}
	else if (nodDeSters == rad) {
		rad = NULL_TELEM;
	}
	else {
		if (stanga[parinte] == nodDeSters) {
			stanga[parinte] = NULL_TELEM;
		}
		else {
			dreapta[parinte] = NULL_TELEM;
		}
	}

	if (nodDeSters != curent) {
		element[curent] = element[nodDeSters];
	}

	dealoca(nodDeSters);
	lg--;
	return true;
}
//Caz favorabil: Teta(1)
// Caz defavorabil: Teta(h)
// Caz mediu: Teta(h)
// Complexitate:O(h)
bool Multime::cauta(TElem elem) const {
	int curent = rad;
	while (curent != NULL_TELEM) {
		if (element[curent] == elem) {
			return true;
		}
		if (rel(elem, element[curent])) {
			curent = stanga[curent];
		}
		else {
			curent = dreapta[curent];
		}
	}
	return false;
}

//Complexitate:Teta(1)
int Multime::dim() const {
	return lg;
}


//Complexitate:Teta(1)
bool Multime::vida() const {
	return lg==0;
}

//Complexitate:Teta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

//Complexitate:Teta(1)
Multime::~Multime() {
	delete[] element;
	delete[] stanga;
	delete[] dreapta;
}
