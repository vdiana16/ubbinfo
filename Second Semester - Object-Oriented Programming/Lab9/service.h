#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include "repository.h"
#include "exceptions.h"
#include "coscump.h"
#include "undo.h"
#include "filerepository.h"
#include <vector>
#include <functional>
#include <map>

using std::vector;
using std::function;
using std::unique_ptr;

class ServiceProdus {
private:
	//Referinta la repository
	RepoAbs& rep;
	//Referinta la validator
	ProdusValidator& val;
	//Cos cumparaturi
	Cos& coscump;
	//Lista de undo
	std::vector<unique_ptr<ActiuneUndo>> undoAct;

	/*
	* Functie de sortare generala
	* @param: maiMic - functie care compara 2 Produse, verificadaca are loc relatia mai mic
	* @return: returneaza lista sortata dupa un criteriu dat
	*/
	vector<Produs> generalSort(bool (*maiMic)(const Produs&, const Produs&));

	/*
	* Functie de filtrare generala
	* @param: maiMic - functie care compara 2 Produse, verificadaca are loc relatia mai mic
	* @return: returneaza lista produselor care indeplinesc filtru
	*/
	vector<Produs> generalFilt(function<bool(const Produs&)> fct);
public:

	int getId();

	//Constructorul clasei
	ServiceProdus(RepoAbs& rep, ProdusValidator& val, Cos& coscump) : rep{ rep }, val{ val }, coscump{ coscump } {};

	//Nu se poate copia service-ul
	ServiceProdus(const ServiceProdus& ot) = delete;

	//Constructor implicit
	ServiceProdus() = default;

	//Destructor implicit
	~ServiceProdus() = default;

	/*Metoda care adauga un produs in lista de produse
	* @param: nume, tip, producator - string
	*		  pret - double
	*/
	void adaugaProd(const string& nume, const string& tip, double pret, const string& producator);
	/*Metoda care sterge un produs din lista de produse
	* @param: id - int
	*/
	void stergeProd(const int& id);

	/*Metoda care modifica un produs din lista de produse
	* @param:id -int
	*		 nume, tip, producator - string
	*		 pret - double
	*/
	void modificaProd(const int& id, const string& nume, const string& tip, double pret, const string& producator);

	/*Metoda care cauta un produs din lista de produse
	* @param:id -int
	* @return:returneaza produsul cautat
	*/
	Produs& cautaProd(const int& id);

	/*Metoda care cauta un produs dupa nume din lista de produse
	* @param:id -int
	* @return:returneaza pozitia produsului cautat
	*/
	int cautaProdN(const string& nume);

	/*Getter pentru lista de produse
	* @return: returneaza lista de produse
	*/
	vector<Produs>& getListaProd();

	/*
	* Metoda care sorteaza dupa numele produselor
	* @return: returneaza lista sortata
	*/
	vector<Produs> sortNume();

	/*
	* Metoda care sorteaza dupa pretul produselor
	* @return: returneaza lista sortata
	*/
	vector<Produs> sortPret();

	/*
	* Metoda care sorteaza dupa numele si tipul produselor
	* @return: returneaza lista sortata
	*/
	vector<Produs> sortNumeTip();

	/*
	* Metoda care filtreaza produsele care au pretul produselor mai mare decat un pret dat
	* @param: pret - double, pretul dupa care se face filtrarea
	* @return: returneaza lista filtrata
	*/
	vector<Produs> filtPretMaiMare(double pret);

	/*
	* Metoda care filtreaza produsele care au acelasi nume cu numele dat
	* @param: nume - string, numele produsului dupa care se face filtrarea
	* @return: returneaza lista filtrata
	*/
	vector<Produs> filtNume(string nume);

	/*
	* Metoda care filtreaza produsele care au acelasi producator cu producatorul dat
	* @param: producator - string, producatorul produsului dupa care se face filtrarea
	* @return: returneaza lista filtrata
	*/
	vector<Produs> filtProducator(string producator);

	/*
	* Cos cumparaturi
	*/
	const vector<Produs>& getComp() noexcept;

	void adaugaProdCos(const string& nume);

	void generareCos(int nrprod);

	void golesteCos();

	void exportCos(const string& numefis);

	/*
	* Raport
	*/
	std::map<std::string, ProdusDTO> generareRaport(const std::vector<Produs>& produse);

	/*
	* Undo
	*/
	void undo();
};

#endif // !SERVICE_H
