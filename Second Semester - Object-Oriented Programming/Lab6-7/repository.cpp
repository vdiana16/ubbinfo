#include "repository.h"
#include "exceptii.h"

int RepoProdus::getId() {
	return this->id;
}

void RepoProdus::setId() {
	this->id++;
}


bool RepoProdus::existaProdus(const Produs& p){
	int i;
	for (i = 0; i < produse.size(); i++) {
		if (produse[i] == p) {
			return true;
		}
	}
	return false;
}

int RepoProdus::cautaId(const int& id) const {
	int i;
	for (i = 0; i < produse.size(); i++) {
		if (produse[i].getId() == id) {
			return i;
		}
	}
	return -1;
}

void RepoProdus::adaugaProdus(const Produs& prod) {
	if (existaProdus(prod) == false) {
		produse.push_back(prod);
	}
	else {
		throw(RepoException("Exista deja acest produs!\n"));
	}
}

void RepoProdus::stergeProdus(const int& id) {
	int pozitie = cautaId(id);
	if (pozitie != -1) {
		produse.erase(produse.begin() + pozitie);
	}
	else {
		throw(RepoException("Nu exista acest produs!\n"));
	}
}

void RepoProdus::modificaProdus(const int& id, const Produs& prod) {
	int pozitie = cautaId(id);
	if (pozitie != -1) {
		produse[pozitie].setNume(prod.getNume());
		produse[pozitie].setTip(prod.getTip());
		produse[pozitie].setPret(prod.getPret());
		produse[pozitie].setProducator(prod.getProducator());
	}
	else {
		throw(RepoException("Nu exista acest produs!\n"));
	}
}

Produs& RepoProdus::cautaProdus(const int& id){
	int i;
	for (i = 0; i < produse.size(); i++) {
		if (produse[i].getId() == id) {
			return produse[i];
		}
	}
	throw(RepoException("Nu exista acest produs!\n"));
}

const vector<Produs>& RepoProdus::getLista() const noexcept {
	return produse;
}
