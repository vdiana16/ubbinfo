#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

//Teta(cp)
Multime::Multime() {
	//lista e vida
	lg = 0;
	cp = CAPACITATE;
	prim = -1;
	primLiber = 0;
	e = new TElem[cp];
	urm = new int[cp];
	//se initializeaza spatiul liber, toate pozitiile din vector sunt marcate ca fiind libere
	for (int i = 0; i < cp - 1; i++) {
		urm[i] = i + 1;
	}
	urm[cp - 1] = -1;
}

//Teta(1)
int Multime::aloca() {
	//se sterge primul element din lista spatiului liber
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

//Teta(1)
void Multime::dealoca(int i) {
	// se trece pozitia i in lista spatiului liber
	urm[i] = primLiber;
	primLiber = i;
}

//Teta(cp)
void Multime::redim() {
	int cp_aux = cp * 2;
	int* urm_aux = new int[cp_aux];
	TElem* e_aux = new TElem[cp_aux];
	for (int i = 0; i < cp; i++) {
		urm_aux[i] = urm[i];
		e_aux[i] = e[i];
	}
	for (int i = cp; i < cp_aux - 1; i++) {
		urm_aux[i] = i + 1;
	}
	urm_aux[cp_aux - 1] = -1;
	primLiber = cp;
	delete[] urm;
	delete[] e;
	this->e = e_aux;
	this->urm = urm_aux;
	this->cp = cp_aux;
}

//Teta(1)
int Multime::creeazaNod(TElem e) {
	int i = aloca();
	this->e[i] = e;
	urm[i] = prim;
	return i;
}

//caz favorabil:Teta(1)
// caz mediu:Teta(n)
//caz defavorabil:Teta(n)
//overall:O(n)
bool Multime::adauga(TElem elem) {
	if (cauta(elem) == true) {
		return false;
	}
	if (lg == cp) {
		redim();
	}
	int i = creeazaNod(elem);
	urm[i] = prim;
	prim = i;
	lg++;
	return true;
}

//caz favorabil:Teta(1)
// caz mediu:Teta(n)
//caz defavorabil:Teta(n)
//overall:O(n)
bool Multime::sterge(TElem elem) {
	int i = prim, prec = -1;
	while (i != -1 && e[i] != elem) {
		prec = i;
		i = urm[i];
	}
	if (i == -1) {
		return false;
	}
	if (prec == -1) {
		prim = urm[i];
	}
	else {
		urm[prec] = urm[i];
	}
	dealoca(i);
	lg--;
	return true;
}

//caz favorabil:Teta(1)
// caz mediu:Teta(n)
//caz defavorabil:Teta(n)
//overall:O(n)
bool Multime::cauta(TElem elem) const {
	int i = prim;
	while (i != -1) {
		if (e[i] == elem) {
			return true;
		}
		i = urm[i];
	}
	return false;
}

//Teta(1)
int Multime::dim() const {
	return lg;
}

//Teta(1)
bool Multime::vida() const {
	return lg == 0;
}

//Teta(1)
Multime::~Multime() {
	delete[] e;
	delete[] urm;
}

//Teta(1)
IteratorMultime Multime::iterator(){
	return IteratorMultime(*this);
}