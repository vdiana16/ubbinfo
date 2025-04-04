#include "repository.h"
#include "exceptions.h"
#include <algorithm>
#include <functional>
#include <random>



bool RepoProdus::existaProdus(const Produs& p) {
	for (auto prod : produse) {
		if (prod == p) {
			return true;
		}
	}
	return false;
}



int RepoProdus::cautaId(const int& id) const {
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

void RepoProdus::modificaProdus(const Produs& prod) {
	int pozitie = cautaId(prod.getId());
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

vector<Produs>& RepoProdus::getLista(){
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

void RepoProb::probabilitate() {
	auto p = int(prob * 10);
	int numar = rand() % 10 + 1;
	if (numar <= p) {
		return;
	}
	throw RepoException("Nu ai noroc!\n");
}

void RepoProb::adaugaProdus(const Produs &p) {
	probabilitate();
	elemente.insert(std::make_pair(elemente.size(), p));
}

void RepoProb::modificaProdus(const Produs& p) {
	probabilitate();
	int pozitie = cautaId(p.getId());
	for (auto& prod : elemente) {
		if (prod.first == pozitie) {
			elemente.erase(pozitie);
			elemente.insert(std::make_pair(pozitie, p));
			break;
		}
	}
}

void RepoProb::stergeProdus(const int& id) {
	probabilitate();
	int pozitie = cautaId(id);
	elemente.erase(pozitie);
	map<int, Produs> secundar;
	secundar.clear();
	for (auto& p : elemente) {
		secundar.insert(std::make_pair(secundar.size(), p.second));
	}
	elemente = secundar;
}

vector<Produs>& RepoProb::getLista() {
	probabilitate();
	toate.clear();
	for (auto& p : elemente) {
		toate.push_back(p.second);
	}
	return toate;
}

RepoProb::RepoProb(float sansa) {
	prob = sansa;
	elemente.clear();
}

int RepoProb::cautaId(const int& id) const {
	int poz = -1;
	for (const auto& i : elemente) {
		poz += 1;
		if (i.second.getId() == id) {
			return poz;
		}
	}
	return -1;
}

Produs& RepoProb::cautaProdus(const int& id) {
	int poz = cautaId(id);
	for (auto& prod : elemente) {
		if (prod.first == poz) {
			return prod.second;
		}
	}
	throw(RepoException("Nu exista acest produs!\n"));
}

int RepoProb::cautaProdusNume(const string& nume) {
	for (auto& prod : elemente) {
		if (prod.second.getNume() == nume) {
			int poz = cautaId(prod.second.getId());
			return poz;
		}
	}
	return -1;
}