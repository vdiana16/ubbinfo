#pragma once

#ifndef UI_H
#define UI_H

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
* Afiseaza o cheltuiala
* listachelt - pointer catre lista de cheltuieli
*/
void afiseazaCheltuiala(Cheltuiala* chelt);

/*
* Adauga o cheltuiala in lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void adaugare(Srv srvchelt);

/*
* Modifica o cheltuiala din lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void modificare(Srv srvchelt);

/*
* Sterge o cheltuiala din lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void stergere(Srv srvchelt);

/*
* Filtreaza lista de cheltuieli dupa apartament, suma si tip
* listachelt - pointer catre lista de cheltuieli
*/
void filtrare(Srv srvchelt);

/*
* Sorteaza lista de cheltuieli dupa suma sau tip
* listachelt - pointer catre lista de cheltuieli
* 0 crescator, 1 descrescator
*/
void sortare(Srv srvchelt);

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

#endif // !UI_H


