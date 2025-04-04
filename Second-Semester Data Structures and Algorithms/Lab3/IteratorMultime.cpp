#include "IteratorMultime.h"
#include "Multime.h"

//Complexitate:O(h)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	prim();
}

//Complexitate:Teta(1)
TElem IteratorMultime::element() const {
	if (!valid()) {
		throw std::exception("Iteratorul nu este valid!");
	}
	return mult.element[curent];
}

//Complexitate:Teta(1)
bool IteratorMultime::valid() const {
	return curent != NULL_TELEM;
}

//Complexitate:O(h)
void IteratorMultime::urmator() {
	if (!valid()) {
		throw std::exception("Iterator invalid");
	}
	int nod = stiva.top();
	stiva.pop();
	if (mult.dreapta[nod] != NULL_TELEM) {
		nod = mult.dreapta[nod];
		while (nod != NULL_TELEM) {
			stiva.push(nod);
			nod = mult.stanga[nod];
		}
	}
	if (!stiva.empty()) {
		curent = stiva.top();
	}
	else {
		curent = NULL_TELEM;
	}
}

//Complexitate:O(h)
void IteratorMultime::prim() {
	while (!stiva.empty()) {
		stiva.pop();
	}
	curent = mult.rad;
	while (curent != NULL_TELEM) {
		stiva.push(curent);
		curent = mult.stanga[curent];
	}
	if (!stiva.empty()) {
		curent = stiva.top();
	}
	else {
		curent = NULL_TELEM;
	}
}

//Complexitate:O(kh)
void IteratorMultime::avanseazaKPasi(int k) {
	if (!valid()) {
		throw std::exception("Iteratorul nu mai este valid! ");
	}
	for (int i = 0; i < k; i++) {
		urmator();
	}
}