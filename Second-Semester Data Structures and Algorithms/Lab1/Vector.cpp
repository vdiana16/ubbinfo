#include "Vector.h";

using namespace std;

//Teta(1)
Vectorind::Vectorind(){
	this->lg = 0;
	this->cp = 2;
	this->v = new int[this->cp];
}
//Teta(1)
Vectorind::~Vectorind() { 
	delete[] this->v; 
}

//Teta(n)
void Vectorind::redim() {
	if (this->cp == this->lg) {
		int i;
		int* aux = new int[this->cp * 2];
		for (i = 0; i < this->lg; i++) {
			aux[i] = this->v[i];
		}
		delete this->v;
		this->v = aux;
		this->cp = this->cp * 2;
	}
}

//Teta(1) amortizat
void Vectorind::adauga(int ind) {
	redim();
	this->v[this->lg] = ind;
	this->lg++;
}


//Caz favorabil: teta(1) cand elementul se afla la mijloc
//Caz defavorabil: teta(n) cand elementul se afla pe prima pozitie sau pe ultima
//Caz mediu: teta(n)
//O(n)
void Vectorind::sterge(int ind) {
	int i, poz = -1;
	for (i = 0; i < this->lg; i++) {
		if (this->v[i] == ind) {
			poz = i;
			break;
		}
	}
	if (poz != -1) {
		for (i = poz; i < this->lg - 1; i++) {
			this->v[i] = this->v[i + 1];
		}
		this->lg--;
	}
}

//Teta(1)
int Vectorind::getlg() const{
	return this->lg;
}

Vectorval::Vectorval() {
	this->lg = 0;
	this->cp = 2;
	this->v = new TElem[this->cp];
}

Vectorval::~Vectorval() { 
	delete[] this->v; 
}

void Vectorval::redim() {
	if (this->lg == this->cp) {
		int i;
		TElem* aux = new TElem[this->cp*2];
		for (i = 0; i < this->lg; i++) {
			aux[i] = this->v[i];
		}
		delete[] this->v;
		this->v = aux;
		this->cp = this->cp * 2;
	}
}

void Vectorval::adauga(TElem val) {
	redim();
	this->v[this->lg] = val;
	this->lg++;
}

void Vectorval::sterge(TElem val) {
	int i, poz = -1;
	for (i = 0; i < this->lg; i++) {
		if (this->v[i] == val) {
			poz = i;
			break;
		}
	}
	if (poz != -1) {
		for (i = poz; i < this->lg - 1; i++) {
			this->v[i] = this->v[i + 1];
		}
		this->lg--;
	}
}