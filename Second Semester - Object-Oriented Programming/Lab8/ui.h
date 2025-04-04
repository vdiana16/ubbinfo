#pragma once

#ifndef UI_H
#define UI_H

#include "service.h"
#include "coscump.h"

class UI {
private:
	//Referinta la service
	ServiceProdus& srv;

	//Curata buffer-ul intern
	void curataBuffer() const;

	//Afiseaza meniul
	void meniu() const;

	//Metoda de adaugare a unui produs in lista
	void adaugaUI() const;

	//Metoda de stergere a unui produs din lista
	void stergeUI() const;

	//Metoda de modificarea unui produs din lista
	void modificaUI() const; 

	//Metoda de catarea unui produs in lista
	void cautaUI() const;

	//Metoda de sortarea listei de produse
	void sortUI() const;

	//Metoda de filtrarea listei de produse
	void filtUI() const;

	/*Metoda de afisarea unei liste de produse date ca parametru
	* @param: produse - vector de produse
	*/
	void tiparesteListaUI(const vector<Produs>& produse) const;

	//Metoda de afisarea unei liste de produse
	void tiparesteUI() const;

	//Metoda pentru gestionarea cosului de cumparaturi
	void cosUI() const;

	//Metoda pentru generare raport
	void generareRapUI() const;
public:
	//Constructorul clasei
	UI(ServiceProdus& srv) : srv{ srv } {}

	//Nu se permite copierea clasei
	UI(const UI& ot) = delete;

	//Metoda prin care este rulata aplicatia
	void run() const;
};
#endif // !UI_H