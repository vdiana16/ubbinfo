#pragma once
#ifndef REPOSITOY_H
#define REPOSITORY_H
#include "domain.h"
#include <vector>
#include <string>
#include <ostream>
#include <map>
#include <utility>

using std::vector;
using std::string;
using std::map;

class RepoAbs {
public:
	virtual void adaugaProdus(const Produs& prod) = 0;

	virtual void stergeProdus(const int& id) = 0;

	virtual void modificaProdus(const Produs& prod) = 0;

	virtual vector<Produs>& getLista() = 0;

	virtual int cautaId(const int& id) const = 0;

	virtual Produs& cautaProdus(const int& id) = 0;

	virtual int cautaProdusNume(const string& nume) = 0;

	virtual ~RepoAbs() = default;
};

class RepoProdus: public RepoAbs {
private:
	//Vectorul in care retin produsele
	vector<Produs> produse;

	bool existaProdus(const Produs& p);

	int id = 1;
public:


	//Constructor repo
	RepoProdus() = default;

	//Nu se copiaza aceasta clasa
	RepoProdus(const RepoProdus& ot) = delete;

	virtual ~RepoProdus() = default;

	/*Metoda care adauga produsul
	* @param:prod - produsul care trebuie adaugat
	*/
	virtual void adaugaProdus(const Produs& prod) override;

	/*Metoda care sterge un produs
	* @id:id-ul produsului care urmeaza sa fie sters
	*/
	virtual void stergeProdus(const int& id) override;

	/*Metoda care modifica un produs
	* @param id:id-ul produsului care trebuie modificat
	*	     prod:datele produsului care trebuie modificate
	*/
	virtual void modificaProdus(const Produs& prod) override;

	/*Metoda care cauta un produs
	* @param: id: id-ul produsului dupa care se cauta
	* @return: produsul cautat
	*/
	Produs& cautaProdus(const int& id);

	/*Metoda care cauta un produs
	* @param: nume: numele produsului dupa care se cauta
	* @return: pozitia produsului cautat
	*/
	int cautaProdusNume(const string& nume);

	/*Metoda care cauta un produs dupa id
	* @param: id: id-ul produsuluis
	* @return: pozitia produsului daca acesta exista, altfel -1
	*/
	int cautaId(const int& id) const;

	//Getter pentru returnarea produselor existente
	vector<Produs>& getLista() override;
};

class RepoProb : public RepoAbs {
private:
	float prob;
	map<int, Produs> elemente;
	vector<Produs> toate;
	void probabilitate();
public:
	RepoProb() = default;

	explicit RepoProb(float sansa);
	
	void adaugaProdus(const Produs& prod) override;

	void stergeProdus(const int& id) override;

	void modificaProdus(const Produs& prod) override;

	int cautaId(const int& id) const override;

	Produs& cautaProdus(const int& id) override;

	int cautaProdusNume(const string& nume) override;

	vector<Produs>& getLista() override;

	~RepoProb() = default;
};

#endif // !REPOSITOY_H
