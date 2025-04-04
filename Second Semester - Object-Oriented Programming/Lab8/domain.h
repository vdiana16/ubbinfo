#pragma once
#ifndef DOMAIN_H
#define DOMAIN_H
#include <iostream>
#include <string>
using std::string;
using std::cout;

class Produs {
private:
	int id;
	string nume;
	string tip;
	double pret;
	string producator;
public:
	//Constructor implicit 
	Produs() :id{ 0 }, nume{ "" }, tip{ "" }, pret{ 0 }, producator{ "" } {};

	/*
	* Constructorul produsului
	* @param: id - int
	*		  nume, tip, producator - string
	*		  pret - double
	*/
	Produs(const int id, const string nume, const string tip, const double pret, const string producator) :id{ id }, nume{ nume }, tip{ tip }, pret{ pret }, producator{ producator } {}

	//Functie de copiere
	Produs(const Produs& ot) :id{ ot.id }, nume{ ot.nume }, tip{ ot.tip }, pret{ ot.pret }, producator{ ot.producator } {
		cout << "Hi\n";
	}

	//Destructor
	~Produs() = default;

	//Getters pentru atributele clasei
	int getId() const;
	double getPret() const;
	string getNume() const;
	string getTip() const;
	string getProducator() const;

	//Setters pentru atrubutele clasei, excluzand id-ul
	void setPret(double pretnou);
	void setNume(string numenou);
	void setTip(string tipnou);
	void setProducator(string producatornou);

	bool operator==(const Produs& cop);
};

/*
*Compara dupa nume
* @return: true daca p1.tip<p2.tip, altfel false
*/
bool cmpNume(const Produs& p1, const Produs& p2);

/*
*Compara dupa pret
* @return: true daca p1.pret<p2.pret, altfel false
*/
bool cmpPret(const Produs& p1, const Produs& p2);


/*
*Compara dupa tip
* @return: true daca p1.tip<p2.tip, altfel false
*/
bool cmpTip(const Produs& p1, const Produs& p2);

class ProdusDTO {
public:
	string tip;
	int nr;
	ProdusDTO() = default;
	ProdusDTO(const std::string& t, int n) : tip{ t }, nr{ n } {};
};


#endif // !DOMAIN_H