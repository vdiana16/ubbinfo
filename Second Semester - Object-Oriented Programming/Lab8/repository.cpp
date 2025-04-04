#include "repository.h"
#include "exceptii.h"
#include <algorithm>
#include <functional>

int RepoProdus::getId() {
	return this->id;
}

void RepoProdus::setId() {
	this->id++;
}


bool RepoProdus::existaProdus(const Produs& p) {
	for (auto prod : produse ){
		if (prod == p) {
			return true;
		}
	}
	return false;
}



int RepoProdus::cautaId(const int& id) const{
	auto it = std::find_if(produse.begin(), produse.end(), [=](const Produs& prod) {
		return prod.getId() == id;
		});

	if (it != produse.end()) {
		return std::distance(produse.begin(), it);
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

Produs& RepoProdus::cautaProdus(const int& id) {
	int poz = cautaId(id);
	if (poz != -1) {
		return produse[poz];
	}
	throw(RepoException("Nu exista acest produs!\n"));
}

const vector<Produs>& RepoProdus::getLista() const noexcept {
	return produse;
}


int RepoProdus::cautaProdusNume(const string& nume) {
	auto it = std::find_if(produse.begin(), produse.end(), [=](const Produs& prod) {
		return prod.getNume() == nume;
		});

	if (it != produse.end()) {
		int poz = std::distance(produse.begin(), it);
		return produse[poz].getId();
	}
	return -1;
}