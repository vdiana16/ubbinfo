#pragma once

#include "domain.h"

/*
* Definesc tipul ElemType de tip Cheltuiala
*/ 
typedef Cheltuiala ElemType;

/*
* Definesc structura Repo pentru retinerea unei liste cu elemente de tip cheltuiala
* elmente[i] - un element de tip cheltuiala
* lg - lungimea listei
*/
typedef struct {
	ElemType element[50];
	int lg;
}Repo;

/*
* Crearea unei liste de cheltuieli
* Post: lista de cheltuieli de tip Repo
*/
Repo creareLista();

/*
* Distrugerea listei de cheltuieli
* listachelt - pointer catre lista de cheltuieli
*/
void distrugereLista(Repo* listachelt);

/*
* Returnarea unei cheltuieli din lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
* pozitie - intreg, pozitia elementului dorit
* Pre: pozitie valida
* Post: cheltuiala de tip ElemType
*/
ElemType getCheltuiala(Repo* listachelt, int pozitie);

/*
* Returneaza numarul de cheltuieli din lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
* Post: cheltuiala de pe pozitia dorita
*/
int lgLista(Repo* listachelt);

/*
* Verifica sa nu mai existe o cheltuiala identica cu cea care se adauga
* listachelt - pointer catre lista de cheltuieli
* elem - element de tip cheltuiala
* Post: 0 daca elementul se poate adauga, 1 altfel
*/
int verificareCheltuiala(Repo* listachelt, ElemType elem);

/*
* Adauga o cheluiala in lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
* elem - element de tip cheltuiala
* Post: 0 daca elementul a fost adaugat cu succes, 1 altfel
*/
int adaugareCheltuiala(Repo* listachelt, ElemType elem);

/*
* Modifica o cheluiala existenta in lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
* elem - element de tip cheltuiala de modificat
* elemnou - element de tip cheltuiala modificat
* Post: 0 daca elementul a fost modificat cu succes, 1 altfel
*/
int modificareCheltuiala(Repo* listachelt, ElemType elem, ElemType elemnou);

/*
* Cauta o cheluiala in lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
* elem - element de tip cheltuiala de modificat
* Post: pozitia elementului daca acesta a fost gasit, -1 altfel
*/
int cautareCheltuiala(Repo* listachelt, ElemType elem);

/*
* Sterge o cheluiala din lista de cheltuieli
* listachelt - pointer catre lista de cheltuieli
* elem - element de tip cheltuiala de modificat
* Post: elementul a fost sters cu succe, 1 altfel
*/
int stergereCheltuiala(Repo* listachelt, ElemType elem);

/*
* Realizeaza o copie a listei de cheltuieli
* listachelt - pointer catre lista de cheltuieli
* Post: lista noua de cheltuieli, identica cu cea primita ca si parametru
*/
Repo copiereLista(Repo* listachelt);