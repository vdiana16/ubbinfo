#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

//Teta(1)
int hashCode(TElem e) {
	return abs(e);
}

//Teta(1)
int Colectie::d(TElem e, int i) const{
	return (hashCode(e) % m + i * (1 + hashCode(e) % (m - 2))) % m;
}

//Teta(m)
Colectie::Colectie() {
	m = MAX;
	lg = 0;
	e = new TElem[m];
	for (int i = 0; i < m; i++) {
		e[i] = NULL_TELEM;
	}
}

//Caz favorabil: Teta(1)
// Caz mediu: Teta(1) amortizat 
//Caz defavorabil: Teta(m)
//Overall: O(1) amortizat in ipoteza dispersiei uniforme simple
void Colectie::adauga(TElem elem) {
	int i = 0;
	bool gasit = false;
	do {
		int j = d(elem, i);
		if (e[j] == NULL_TELEM || e[j] == STERS) {
			e[j] = elem;
			gasit = true;
			lg++;
		}
		else {
			i++;
		}
	} while (i < m && !gasit);
	if (i == m) {
		//depasire tabela
		//ar fi necesara redimensionarea
	}
}

//Caz favorabil: Teta(1)
// Caz mediu: Teta(1) amortizat 
//Caz defavorabil: Teta(m)
//Overall: O(1) amortizat in ipoteza dispersiei uniforme simple
bool Colectie::sterge(TElem elem) {
	int i = 0;
	bool gasit = false;
	int j;
	do {
		j = d(elem, i);
		if (e[j] == elem) {
			e[j] = STERS;
			gasit = true;
			lg--;
		}
		else {
			i++;
		}
	} while (e[j] != NULL_TELEM && i < m && gasit == false);
	return gasit;
}

// Caz favorabil : Teta(1)
// Caz mediu: Teta(1) amortizat 
//Caz defavorabil: Teta(m)
//Overall: O(1) amortizat in ipoteza dispersiei uniforme simple
bool Colectie::cauta(TElem elem) const {
	int i = 0;
	bool gasit = false;
	int j;
	do {
		j = d(elem, i);
		if (e[j] == elem) {
			gasit = true;
		}
		else {
			i++;
		}
	} while (e[j] != NULL_TELEM && i < m && gasit==false);
	return gasit;
}

//Teta(m)
int Colectie::nrAparitii(TElem elem) const {
	int i = 0;
	int contor = 0;
	int j;
	do {
		j = d(elem, i);
		if (e[j] == elem) {
			contor++;
		}
		i++;
		
	} while (e[j] != NULL_TELEM && i < m);
	return contor;
}

//Teta(1)
int Colectie::dim() const {
	return lg;
}

//Teta(1)
bool Colectie::vida() const {
	return lg == 0;
}

//Teta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


//Teta(1)
Colectie::~Colectie() {
	delete[] e;
}


