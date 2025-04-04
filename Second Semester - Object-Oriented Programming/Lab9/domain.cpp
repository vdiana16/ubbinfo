#include "domain.h"
#include <sstream>


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

void Produs::setId(int idnou) {
	id = idnou;
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

bool Produs::operator!=(const Produs& ot) {
	return !operator==(ot);
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

std::vector<string> split(const string& inputs, char delim) {
	std::vector<string> linieprod;
	std::stringstream stream(inputs);
	std::string crt;
	while (std::getline(stream, crt, delim))
	{
		linieprod.push_back(crt);
	}
	return linieprod;
}

std::istream & operator>> (std::istream& inputStream, Produs& produs) {
	std::string linie;
	std::getline(inputStream, linie);
	std::vector<string> lprodus = split(linie, ',');
	if (lprodus.size() != 5)
		return inputStream;
	produs.setId(std::stoi(lprodus[0]));
	produs.setNume(lprodus[1]);
	produs.setTip(lprodus[2]);
	produs.setPret(std::stod(lprodus[3]));
	produs.setProducator(lprodus[4]);
	return inputStream;
}

std::ostream & operator<<(std::ostream& outputStream, const Produs& produs) {
	outputStream << produs.getId() << "," << produs.getNume() << "," << produs.getTip() << "," << produs.getPret() << "," << produs.getProducator() << "\n";
	return outputStream;
}