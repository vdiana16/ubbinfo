#include "Matrice.h"

#include <exception>

using namespace std;

//Teta(1)
Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0) {
		throw "Matricea nu poate avea un numar de linii sau de coloane negativ sau nul!";
	}
	this->nrlin = m;
	this->nrcol = n;
}

//Teta(1)
int Matrice::nrLinii() const {
	return this->nrlin;
}

//Teta(1)
int Matrice::nrColoane() const {
	return this->nrcol;
}


//Caz favorabil: teta(1) cand elementul se afla la mijloc
//Caz defavorabil: teta(lo2n) cand elementul se afla pe prima pozitie sau pe ultima
//Caz mediu: teta(log2n)
//O(log2n)
TElem Matrice::element(int i, int j) const {
	if (i < 0 || i >= this->nrLinii() || j < 0 || j >= nrColoane()) {
		throw exception();
		return NULL_TELEMENT;
	}
	int st = 0, dr = this->lin.getlg() - 1, mij;
	while (st <= dr) {
		mij = st + (dr - st) / 2;
		if (this->lin.v[mij] == i && this->col.v[mij] == j) {
			return this->val.v[mij];
		}
		else if (this->lin.v[mij] < i || (this->lin.v[mij] == i && this->col.v[mij] < j)) {
			st = mij + 1;
		}
		else {
			dr = mij - 1;
		}
	}
	return NULL_TELEMENT;
}

//Caz favorabil: teta(1) cand elementul se afla la mijloc
//Caz defavorabil: teta(n) cand elementul se afla pe prima pozitie sau pe ultima
//Caz mediu: teta(n)
//O(n)
TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || i >= this->nrLinii() || j < 0 || j >= nrColoane()) {
		throw exception();
		return NULL_TELEMENT;
	}
	int st = 0, dr = this->lin.getlg() - 1, mij;
	while (st <= dr) {
		mij = st + (dr - st) / 2;
		if (this->lin.v[mij] == i && this->col.v[mij] == j) {
			TElem aux;
			aux = this->val.v[mij];
			this->val.v[mij] = e;
			return aux;
		}
		else if (this->lin.v[mij] < i || (this->lin.v[mij] == i && this->col.v[mij] < j)) {
			st = mij + 1;
		}
		else {
			dr = mij - 1;
		}
	}
	int k;
	this->lin.adauga(i);
	this->col.adauga(j);
	this->val.adauga(e);
	for (k = this->lin.getlg() - 1; k >= 0; k--) {
		if (this->lin.v[k] == i && this->col.v[k] < j) {
			break;
		}
		else if (this->lin.v[k] < i) {
			break;
		}
	}
	int poz;
	poz = k + 1;
	for (k = this->lin.getlg() - 1; k > poz; k--) {
		this->lin.v[k] = this->lin.v[k - 1];
		this->col.v[k] = this->col.v[k - 1];
		this->val.v[k] = this->val.v[k - 1];
	}
	this->lin.v[poz] = i;
	this->col.v[poz] = j;
	this->val.v[poz] = e;

	return NULL_TELEMENT;
}


Matrice Matrice::Transpusa() {
	int i;
	int poz;
	TElem elem;
	Matrice nou(this->nrLinii(), this->nrColoane());
	for (i = 0; i < this->lin.getlg(); i++) {
		elem = this->element(this->lin.v[i], this->col.v[i]);
		nou.modifica(this->col.v[i], this->lin.v[i], elem);	
	}
	return nou;
}
