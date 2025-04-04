#pragma once
#include "domain.h"
#include <vector>
#include <string>

using std::vector;

class Cos {
private:
	vector<Produs> componente;
	vector<int> frecvcomp;
public:
	//Constructor default
	Cos();
	
	/*
	* Returneaza produsele din cosul de cumparaturi
	* @return: vectorul de produse existente in cos
	*/
	const vector<Produs>& getComponente() const noexcept;

	/*
	* Metoda ce adauga un nou produs in cos
	* @paraam: p - produsul ce urmeaza sa fie adaugat
	*/
	void adaugaCos(const Produs& p);

	/*
	* Metoda ce goleste cosul de cumparauri
	*/
	void stergeCos();

	int cautaCos(const Produs& p);

	/*
	* Metoda ce adauga random entitati in cos
	* @param: elemente - produse disponibile
	* @param: n - numarul de produse ce trebuie adaugate
	*/
	void adaugaRandom(const vector<Produs>& elememnte, const int& n);

	/*
	* Metoda ce salveaza cosul in fisier
	* @param: numefis - numele fisierului
	*/
	void salveazaFisier(const string& numefis);
};
