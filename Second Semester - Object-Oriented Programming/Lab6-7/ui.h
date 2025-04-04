#pragma once

#ifndef UI_H
#define UI_H

#include "service.h"

class UI {
private:
	//Referinta la service
	ServiceProdus& srv;

	//Curata buffer-ul intern
	void curataBuffer();

	//Afiseaza meniul
	void meniu();

	//Metoda de adaugare a unui produs in lista
	void adaugaUI();

	//Metoda de stergere a unui produs din lista
	void stergeUI();

	//Metoda de modificarea unui produs din lista
	void modificaUI();

	//Metoda de catarea unui produs in lista
	void cautaUI();

	//Metoda de sortarea listei de produse
	void sortUI();

	//Metoda de filtrarea listei de produse
	void filtUI();

	/*Metoda de afisarea unei liste de produse date ca parametru
	* @param: produse - vector de produse
	*/
	void tiparesteListaUI(const vector<Produs>& produse);
	
	//Metoda de afisarea unei liste de produse
	void tiparesteUI();
public:
	//Constructorul clasei
	UI(ServiceProdus& srv) : srv{ srv } {}

	//Nu se permite copierea clasei
	UI(const UI& ot) = delete;

	//Metoda prin care este rulata aplicatia
	void run();
};
#endif // !UI_H