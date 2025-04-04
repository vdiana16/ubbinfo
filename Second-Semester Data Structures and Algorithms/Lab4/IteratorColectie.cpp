#include "IteratorColectie.h"
#include "Colectie.h"


//Caz favorabil Teta(1)
//Caz mediu Teta(m)
//Caz defavorabil Teta(m)
//Overall:O(m)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	curent = 0;
	deplasare();
}


//Caz favorabil Teta(1)
//Caz mediu Teta(m)
//Caz defavorabil Teta(m)
//Overall:O(m)
void IteratorColectie::prim() {
	//se determina prima locatie ocupata
	curent = 0;
	deplasare();
}


//Caz favorabil Teta(1)
//Caz mediu Teta(m)
//Caz defavorabil Teta(m)
//Overall:O(m)
void IteratorColectie::urmator() {
	curent++;
	deplasare();
}

//Teta(1)
bool IteratorColectie::valid() const {
	return(curent < col.m);
}

//Teta(1)
TElem IteratorColectie::element() const {
	if (!valid()) {
		throw std::exception("Iterator invalid");
	}
	return col.e[curent];
}

//Caz favorabil Teta(1)
//Caz mediu Teta(m)
//Caz defavorabil Teta(m)
//Overall:O(m)
void IteratorColectie::deplasare() {
	while ((curent < col.m) && col.e[curent] == NULL_TELEM) {
		curent++;
	}
}


//Complexitatea:O(m)
void IteratorColectie::avanseazaKPasi(int k) {
	if (!valid()) {
		throw std::exception("Iteratorul invalid!");
	}
	for (int i = 0; i < k; i++) {
		urmator();
		if (!valid()) {
			throw std::exception("Iteratorul invalid!");
		}
	}
}
