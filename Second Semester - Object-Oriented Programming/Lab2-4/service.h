#pragma once
#include "repository.h"

/*
* Adauga o cheltuiala valida in lista
* listachelt - pointer catre lista de cheltuieli
* nrapart - numar intreg
* suma - numar real
* tip - sir de caractere
* Pre: nrapart>0, suma>0, tip!=vid
* Post: 0 daca cheltuiala e adaugata cu succes, altfel 1
*/
int adaugareChelt(Repo* listachelt, int nrapart, float suma, char* tip);

/*
* Modifica o cheltuiala din lista
* listachelt - pointer catre lista de cheltuieli
* nrapart - numar intreg
* suma - numar real
* tip - sir de caractere
* sumanoua - numar real
* tipnou - sir de caractere
* Pre: nrapart>0, suma>0, tip!=vid, sumanoua>0, tipnou!=vid
* Post: 0 daca cheltuiala e modificata cu succes, altfel 1
*/
int modificareChelt(Repo* listachelt, int nrapart, float suma, char* tip, float sumanoua, char* tipnou);

/*
* Sterge o cheltuiala existenta din lista
* listachelt - pointer catre lista de cheltuieli
* nrapart - numar intreg
* suma - numar real
* tip - sir de caractere
* Pre: nrapart>0, suma>0, tip!=vid
* Post: 0 daca cheltuiala e stearsa cu succes, altfel 1
*/
int stergereChelt(Repo* listachelt, int nrapart, float suma, char* tip);

/*
* Returneaza lista cu toate cheltuielile
* listachelt - pointer catre lista de cheltuieli
*/
Repo getToateChelt(Repo* listachelt);

/*
* Filtreaza lista de cheltuieli dupa numarul apartamemtului
* listachelt - pointer catre lista de cheltuieli
* numarapart - intreg
* Pre: numarapart>0
* Post: lista filtrata
*/
Repo filtrareApartament(Repo* listachelt, int numarapart);

/*
* Filtreaza lista de cheltuieli dupa suma cheltuielii apartamemtului
* listachelt - pointer catre lista de cheltuieli
* suma - real
* Pre: suma>0
* Post: lista filtrata
*/
Repo filtrareSuma(Repo* listachelt, float sumachelt);


/*
* Filtreaza lista de cheltuieli dupa tipul cheltuielii apartamemtului
* listachelt - pointer catre lista de cheltuieli
* tip - string
* Pre: tip!=vid
* Post: lista filtrata
*/
Repo filtrareTip(Repo* listachelt, char* tipchelt);

/*
* Sorteaza lista crescatore/descresctor dupa suma cheltuielilor
* listachelt - pointer catre lista de cheltuieli
* sortare - 0 crescator, 1 descrescator
* Post: lista sortata
*/
Repo sortareSuma(Repo* listachelt, int sortare);

/*
* Sorteaza lista crescatore/descresctor dupa tipul cheltuielilor
* listachelt - pointer catre lista de cheltuieli
* sortare - 0 crescator, 1 descrescator
* Post: lista sortata
*/
Repo sortareTip(Repo* listachelt, int sortare);
