#include "service.h"
#include <algorithm>
#include <functional>
#include <iterator>

int ServiceProdus::getId() {
	int id, maxi = 0;
	for (const auto& p : rep.getLista()) {
		if (p.getId() > maxi) {
			maxi = p.getId();
		}
	}
	id = maxi + 1;
	return id;
}

void ServiceProdus::adaugaProd(const string& nume, const string& tip, double pret, const string& producator) {
	Produs prod{ getId(),nume,tip,pret,producator };
	val.validare(prod);
	rep.adaugaProdus(prod);
	undoAct.push_back(std::make_unique<UndoAdauga>(rep, prod));
}

vector<Produs>& ServiceProdus::getListaProd() {
	return rep.getLista();
}

void ServiceProdus::stergeProd(const int& id) {
	Produs prod = rep.cautaProdus(id);
	rep.stergeProdus(id);
	undoAct.push_back(std::make_unique<UndoSterge>(rep, prod));
}

void ServiceProdus::modificaProd(const int& id, const string& nume, const string& tip, double pret, const string& producator) {
	Produs prodv = rep.cautaProdus(id);
	Produs prod{ id,nume,tip,pret,producator };
	val.validare(prod);
	rep.modificaProdus(prod);
	undoAct.push_back(std::make_unique<UndoModifica>(rep, prodv));
}

Produs& ServiceProdus::cautaProd(const int& id) {
	return rep.cautaProdus(id);
}

int ServiceProdus::cautaProdN(const string& nume) {
	return rep.cautaProdusNume(nume);
}

vector<Produs> ServiceProdus::sortNume() {
	auto copie = rep.getLista();
	std::sort(copie.begin(), copie.end(), cmpNume);
	return copie;
	//return generalSort(cmpNume);
}

vector<Produs> ServiceProdus::sortPret() {
	auto copie = rep.getLista();
	std::sort(copie.begin(), copie.end(), cmpPret);
	return copie;
	//return generalSort(cmpPret);
}

vector<Produs> ServiceProdus::sortNumeTip() {
	auto copie = rep.getLista();
	std::sort(copie.begin(), copie.end(), [](const Produs& p1, const Produs& p2) {
		if (p1.getNume() == p2.getNume()) {
			return cmpTip(p1, p2);
		}
		return cmpNume(p1, p2);
		});
	return copie;
}


vector<Produs> ServiceProdus::filtPretMaiMare(double pret) {
	vector<Produs> rezultat;
	auto copie = rep.getLista();
	for (const auto& p : copie) {
		if (p.getPret() > pret) {
			rezultat.push_back(p);
		}
	}
	return rezultat;
}

vector<Produs> ServiceProdus::filtNume(string nume) {
	vector<Produs> rezultat;
	auto copie = rep.getLista();
	std::copy_if(copie.begin(), copie.end(), std::back_inserter(rezultat), [nume](const Produs& p) {
		return p.getNume() == nume;
		});
	return rezultat;
}

vector<Produs> ServiceProdus::filtProducator(string producator) {
	vector<Produs> rezultat;
	auto copie = rep.getLista();
	std::copy_if(copie.begin(), copie.end(), std::back_inserter(rezultat), [producator](const Produs& p) {
		return p.getProducator() == producator;
		});
	return rezultat;
}


std::map<std::string, ProdusDTO> ServiceProdus::generareRaport(const std::vector<Produs>& produse) {
	std::map<std::string, ProdusDTO> raport;
	for (const auto& prod : produse) {
		const std::string& tip = prod.getTip();
		if (raport.find(tip) != raport.end()) {
			raport[tip].nr = raport[tip].nr + 1;
		}
		else {
			raport[tip] = ProdusDTO(tip, 1);
		}
	}
	return raport;
}

const vector<Produs>& ServiceProdus::getComp() noexcept {
	return coscump.getComponente();
}

void ServiceProdus::adaugaProdCos(const string& nume) {
	int poz = rep.cautaProdusNume(nume);
	if (poz != -1) {
		auto prodcautat = rep.cautaProdus(poz);
		coscump.adaugaCos(prodcautat);
	}
	else {
		throw RepoException("Nu exista acest produs!\n");
	}
}

void ServiceProdus::generareCos(int nrprod) {
	coscump.adaugaRandom(rep.getLista(), nrprod);
}

void ServiceProdus::golesteCos() {
	coscump.stergeCos();
}

void ServiceProdus::exportCos(const string& numefis) {
	coscump.salveazaFisier(numefis);
}

void ServiceProdus::undo() {
	if (undoAct.empty()) {
		throw RepoException("Nu se mai poate face undo!\n");
	}
	undoAct.back()->doUndo();
	undoAct.pop_back();
}