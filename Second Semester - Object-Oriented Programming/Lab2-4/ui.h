#pragma once
#include "domain.h"
#include "repository.h"
#include "service.h"

/*
* curatare input pentru a nu avea erori
*/
void curatareInput();

/*
* Afiseaza lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void afiseazaCheltuieli(Repo* listachelt);

/*
* Adauga o cheltuiala in lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void adaugare(Repo* listachelt);

/*
* Modifica o cheltuiala din lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void modificare(Repo* listachelt);

/*
* Sterge o cheltuiala din lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void stergere(Repo* listachelt);

/*
* Filtreaza lista de cheltuieli dupa apartament, suma si tip
* listachelt - pointer catre lista de cheltuieli
*/
void filtrare(Repo* listachelt);

/*
* Sorteaza lista de cheltuieli dupa suma sau tip
* listachelt - pointer catre lista de cheltuieli
* 0 crescator, 1 descrescator
*/
void sortare(Repo* listachelt);

/*
* Afiseaza meniul general
*/
void meniu();

/*
* Afiseaza meniul pentru filtrare
*/
void minimeniufiltrare();

/*
* Afiseaza meniul pentru sortare
*/
void minimeniusortare();

/*
* Ruleaza aplicatia
*/
void run();