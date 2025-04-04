#include "service.h"
#include <algorithm>
#include <functional>


void ServiceProdus::adaugaProd(const string& nume, const string& tip, double pret, const string& producator) {
	Produs prod{ rep.getId(),nume,tip,pret,producator};
	val.validare(prod);
	rep.adaugaProdus(prod);
	rep.setId();
}

const vector<Produs>& ServiceProdus::getListaProd() const noexcept {
	return rep.getLista();
}

void ServiceProdus::stergeProd(const int& id) {
	rep.stergeProdus(id);
}

void ServiceProdus::modificaProd(const int& id, const string& nume, const string& tip, double pret, const string& producator) {
	Produs prod{ id,nume,tip,pret,producator };
	val.validare(prod);
	rep.modificaProdus(id, prod);
}

Produs& ServiceProdus::cautaProd(const int& id) {
	return rep.cautaProdus(id);
}

vector<Produs> ServiceProdus::generalSort(bool(*maiMic)(const Produs&, const Produs&)) {
	vector <Produs> copie{ rep.getLista() };
	for (size_t i = 0; i < copie.size(); i++) {
		for (size_t j = i + 1; j < copie.size(); j++) {
			if (!maiMic(copie[i], copie[j])) {
				Produs aux = copie[i];
				copie[i] = copie[j];
				copie[j] = aux;
			}
		}
	}
	return copie;
}

vector<Produs> ServiceProdus::sortNume() {
	auto copie = rep.getLista();
	std::sort(copie.begin(), copie.end(), cmpNume);
	return copie;
	//return generalSort(cmpNume);
}

vector<Produs> ServiceProdus::sortPret() {
	//auto copie = rep.getLista();
	//std::sort(copie.begin(), copie.end(), cmpPret);
	//return copie;
	return generalSort(cmpPret);
}

vector<Produs> ServiceProdus::sortNumeTip() {
	return generalSort([](const Produs& p1, const Produs& p2) {
		if (p1.getNume() == p2.getNume()) {
			return cmpTip(p1, p2);
		}
		return cmpNume(p1, p2);
	});
}

vector<Produs> ServiceProdus::generalFilt(function<bool(const Produs&)> fct) {
	vector<Produs> rez;
	for (const auto& prod : rep.getLista()) {
		if (fct(prod)) {
			rez.push_back(prod);
		}
	}
	return rez;
}

vector<Produs> ServiceProdus::filtPretMaiMare(double pret) {
	return generalFilt([pret](const Produs& p) {
		return p.getPret() > pret;
	});
}

vector<Produs> ServiceProdus::filtNume(string nume) {
	return generalFilt([nume](const Produs& p) {
		return p.getNume() == nume;
	});
}

vector<Produs> ServiceProdus::filtProducator(string producator) {
	return generalFilt([producator](const Produs& p) {
		return p.getProducator() == producator;
	});
}