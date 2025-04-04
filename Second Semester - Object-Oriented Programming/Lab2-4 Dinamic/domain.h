#pragma once

#ifndef DOMAIN_H
#define DOMAIN_H

/*
* Structura pentru reprezentarea unei cheltuieli
* nrapart - numarul apartamentului
* suma - suma cheltuielii
* tip - tipul cheltuielii
*/

typedef struct {
	int nrapart;
	float suma;
	char* tip;
}Cheltuiala;

/*
* Functie care creeaza o cheltuiala
* @param: nrapart - numar intreg
*		  suma - numar real
*		  tip - sir de caractere
* @return: cheltuiala creata
*/
Cheltuiala* creareCheltuiala(int nrapart, float suma, char* tip);

/*
* Functie care distruge o cheltuiala
* @param: c - cheltuiala  
*/
void distrugereCheltuiala(Cheltuiala* c);

/*
* Functie care valideaza o cheltuiala
* @param: nrapart - numarul apartamentului
*		suma - suma cheltuielii
*		tip - tipul cheltuielii (gaz,apa,canal,incalzire)
* @return: 0 daca cheltuiala este valida, 1 altfel
*/
int validareCheltuiala(int nrapart, float suma, char* tip);

/*
* Functie care copiaza un element de tip Cheltuiala
* @param: a - cheltuiala
* @return: copia unei cheltuieli 
*/
Cheltuiala* copieCheltuiala(Cheltuiala* a);

/*
* Functie care verifica egalitatea a doua cheltuieli
* @param: chelt1, chelt2 - cheltuielile care se testeaza
* @return: 1 daca doua cheltuieli sunt egale ,0 altfel
*/
int egalitateCheltuieli(Cheltuiala* chelt1, Cheltuiala* chelt2);

/*
* Functie care compara doua cheltuieli, in functie de suma
* @param: chelt1 - prima cheltuiala
*		chelt2 - a doua cheltuiala
* @return: 1 daca suma chelt1 > suma chelt2, altfel 0
*/
int cmpSuma(Cheltuiala* chelt1, Cheltuiala* chelt2);

/*
* Functie care compara doua cheltuieli, in functie de tip
* @param: chelt1 - prima cheltuiala
*		chelt2 - a doua cheltuiala
* @return: 1 daca tip chelt1 > tip chelt2, altfel 0
*/
int cmpTip(Cheltuiala* chelt1, Cheltuiala* chelt2);

/*
* Functie de filtrare a cheltuielilor, dupa apartament
* @param: chelt - cheltuiala
*		val - valoarea dupa care se filtreaza
* @return: 0 - daca elementul apartine filtrarii, 1 altfel
*/
int filtrareApartament(Cheltuiala* c, int val);

/*
* Functie de filtrare a cheltuielilor, dupa suma cheltuielii
* @param: chelt - cheltuiala
*		val - valoarea dupa care se filtreaza
* @return: 0 - daca elementul apartine filtrarii, 1 altfel
*/
int filtrareSuma(Cheltuiala* c, float val);

/*
* Functie de filtrare a cheltuielilor, dupa tipul cheltuielii
* @param: chelt - cheltuiala
*		val - valoarea dupa care se filtreaza
* @return: 0 - daca elementul apartine filtrarii, 1 altfel
*/
int filtrareTip(Cheltuiala* c, char* val);

#endif // !DOMAIN_H