#pragma once
#ifndef REPOSITOY_H
#define REPOSITORY_H
#include "domain.h"
#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;

class RepoProdus {
private:
	//Vectorul in care retin produsele
	vector<Produs> produse;

	bool existaProdus(const Produs& p);

	int id = 1;
public:

	int getId();

	void setId();

	//Constructor repo
	RepoProdus() = default;

	//Nu se copiaza aceasta clasa
	RepoProdus(const RepoProdus& ot) = delete;

	~RepoProdus() = default;

	/*Metoda care adauga produsul
	* @param:prod - produsul care trebuie adaugat
	*/
	void adaugaProdus(const Produs& prod);

	/*Metoda care sterge un produs
	* @id:id-ul produsului care urmeaza sa fie sters
	*/
	void stergeProdus(const int& id);

	/*Metoda care modifica un produs
	* @param id:id-ul produsului care trebuie modificat
	*	     prod:datele produsului care trebuie modificate
	*/
	void modificaProdus(const int& id, const Produs& prod);

	/*Metoda care cauta un produs 
	* @param: prod: produsul care se cauta
	*/
	Produs& cautaProdus(const int& id);

	/*Metoda care cauta un produs dupa id
	* @param: id: id-ul produsului
	* @return: pozitia produsului daca acesta exista, altfel -1
	*/
	int cautaId(const int& id) const;

	//Getter pentru returnarea produselor existente
	const vector<Produs>& getLista() const noexcept;
};


#endif // !REPOSITOY_H
