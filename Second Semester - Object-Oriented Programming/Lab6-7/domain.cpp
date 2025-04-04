#include "domain.h"



int Produs::getId() const {
	return id;
}

double Produs::getPret() const {
	return pret;
}

string Produs::getNume() const {
	return nume;
}

string Produs::getTip() const {
	return tip;
}

string Produs::getProducator() const {
	return producator;
}

void Produs::setPret(double pretnou) {
	pret = pretnou;
}

void Produs::setNume(string numenou) {
	nume = numenou;
}
void Produs::setTip(string tipnou) {
	tip = tipnou;
}

void Produs::setProducator(string producatornou) {
	producator = producatornou;
}

bool Produs::operator==(const Produs& cop) {
	return nume == cop.getNume() && tip == cop.getTip() && pret == cop.getPret() && producator == cop.getProducator();
}

bool cmpNume(const Produs& p1, const Produs& p2) {
	return p1.getNume() < p2.getNume();
}

bool cmpPret(const Produs& p1, const Produs& p2) {
	return p1.getPret() < p2.getPret();
}

bool cmpTip(const Produs& p1, const Produs& p2) {
	return p1.getTip() < p2.getTip();
}

