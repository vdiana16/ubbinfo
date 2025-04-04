#pragma once

#ifndef REPOSITORY_H
#define REPOSITORY_H


#include "domain.h"

/*
* Definesc tipuri de date pentru programarea generica
*/
typedef void* ElemType;

typedef void(*dist_fct)(ElemType);

typedef ElemType(*cop_fct)(ElemType);

typedef int(*egal_fct)(ElemType, ElemType);


typedef struct {
	ElemType* element;
	int lg;
	int cp;
	dist_fct dest;
}Repo;

/*
* Functie care creeaza o liste de cheltuieli de tip Repo
* @param: f - functia de distrugere
* @return: o lista de tip Repo
*/
Repo* creareLista(dist_fct f);

/*
* Functie care distruge listei de cheltuieli
* @param: listachelt - lista care trebuie distrusa
*/
void distrugereLista(Repo* listachelt);

/*
* Functie care redimensioneaza spatiu de memorare
* @param: listachelt - lista care trebuie redimensionata
*/
void redimensionareLista(Repo* listachelt);

/*
* Functie care cauta o cheluiala in lista de cheltuieli
* @param: listachelt - lista in care se cauta
*		  elem - elementul cautat
*		  eq - functia de egalitate
* @return: pozitia elementului in lista daca exista, altfel -1
*/
int cautareCheltuiala(Repo* listachelt, ElemType* elem, egal_fct eq);

/*
* Functie care adauga o cheluiala in lista de cheltuieli
* @param: listachelt - lista in care se adauga noul element
*		  elem - elementul care trebuie adaugat
*	      eq - functia de egalitate
* @return: 0 daca elementul a fost adaugat cu succes, 1 altfel
*/
int adaugareCheltuiala(Repo* listachelt, ElemType* elem, egal_fct eq);

/*
* Functie care modifica o cheluiala in lista de cheltuieli
* @param: listachelt - lista in care se adauga noul element
*		  elem - elementul care trebuie modificat
*		  elemnou - elementul cu care se modifica
*		  eq - functia de egalitate
*/
void modificareCheltuiala(Repo* listachelt, ElemType* elem, int poz, egal_fct eq);

/*
* Functie care sterge o cheluiala din lista de cheltuieli
* @param: listachelt - lista in care se adauga noul element
*		  elem - elementul care trebuie sters
*		  eq - functia de egalitate
* @return: 0 daca elementul a fost adaugat cu succes, 1 altfel
*/
int stergereCheltuiala(Repo* listachelt, ElemType* elem, egal_fct eq);

/*
* Functie care copiaza o lista de cheltuieli
* @param: listachelt - lista in care se adauga noul element
* @return: lista copiata
*/
Repo* copieLista(Repo* listachelt, cop_fct cp);

#endif // !REPOSITORY_H
