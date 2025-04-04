#pragma once
#ifndef SERVICE_H
#define SERVICE_H

#include "domain.h"
#include "repository.h"

/*
* Definesc tipuri de date pentru programarea generica
*/
typedef int(*filtapart_fct)(ElemType, int);

typedef int(*filtsuma_fct)(ElemType, float);

typedef int(*filtip_fct)(ElemType, char*);

typedef int(*cmpsuma_fct)(ElemType, ElemType);

typedef int(*cmptip_fct)(ElemType, ElemType);

typedef struct {
	Repo* listacrt;
}Srv;

/*
* Creeaza un service pentru cheltuieli
* @return: service-ul de cheltuieli
*/
Srv creareSrv();

/*
* Distruge service-ul de cheltuieli
*/
void distrugereSrv(Srv* srvchelt);

/* Adauga o cheltuiala valida in lista
* @param:srvchelt
*		nrapart - numar intreg
*		suma - numar real
*		tip - sir de caractere
* @return: 0 daca adaugarea s-a efectuat cu succes, altfel 1
*/
int adaugareChelt(Srv* srvchelt, int nrapart, float suma, char* tip);


/* Modifica o cheltuiala din lista
* @param:srvchelt
*		nrapart - numar intreg
*		suma - numar real
*		tip - sir de caractere
*		sumanoua - numar real
*		tipnou - sir de caractere
* @return: 0 daca modificarea s-a efectuat cu succes, altfel 1
*/
int modificareChelt(Srv* srvchelt, int nrapart, float suma, char* tip, float sumanoua, char* tipnou);

/* Sterge o cheltuiala din lista
* @param:srvchelt
*		nrapart - numar intreg
*		suma - numar real
*		tip - sir de caractere
* @return: 0 daca stergerea s-a efectuat cu succes, altfel 1
*/
int stergereChelt(Srv* srvchelt, int nrapart, float suma, char* tip);

/* Filtreaza lista dupa apartament
* @param:listachelt - lista de cheltuieli
*		nrapart - numar intreg
* @return: lista filtrata
*/
Repo* filtrareCheltApart(Repo* listachelt, int nrapart, filtapart_fct filt);

/* Filtreaza lista dupa suma
* @param:listachelt - lista de cheltuieli
*		suma - numar real
* @return: lista filtrata
*/
Repo* filtrareCheltSuma(Repo* listachelt, float suma, filtsuma_fct filt);

/* Filtreaza lista dupa tip
* @param:listachelt - lista de cheltuieli
*		tip - sir de caractere
* @return: lista filtrata
*/
Repo* filtrareCheltTip(Repo* listachelt, char* tip, filtip_fct filt);

/* Sorteaza lista dupa suma
* @param:listachelt - lista de cheltuieli
*		 crescator - ordinea de sortare (0 - desc, 1-cresc)
*		 cmp - functia de comparare
* @return: lista ordonata
*/
Repo* sortareCheltSuma(Repo* listachelt, int crescator, cmpsuma_fct cmp);

/* Sorteaza lista dupa tip
* @param:listachelt - lista de cheltuieli
*		crescator - ordinea de sortare(0 - desc, 1 - cresc)
*		cmp - functia de comparare
* @return: lista ordonata
*/
Repo* sortareCheltTip(Repo* listachelt, int crescator, cmptip_fct cmp);

#endif // !SERVICE_H
