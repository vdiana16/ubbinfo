#pragma once

/*
* Structura pentru reprezentarea unei cheltuieli
* nrapart - numarul apartamentului
* suma - suma cheltuielii
* tip - tipul cheltuielii
*/

typedef struct{
	int nrapart;
	float suma;
	char tip[30];
}Cheltuiala;

/*
* Functie care creeaza o cheltuiala
* nrapart - numar intreg
* suma - numar real
* tip - sir de caractere
* Post: returneaza o cheltuiala de tipul structurii precizate
*/
Cheltuiala creareCheltuiala(int nrapart, float suma, char* tip);

/*
* Functie care distruge o cheltuiala
* c - pointer la o cheltuiala
* Post: marcheaza cheltuiala pentru a nu o mai putea folosi
*/
void distrugereCheltuiala(Cheltuiala* c);

/*
* Functie care valideaza o cheltuiala
* chelt - o cheltuiala cu atributele specifice
* Post: cheltuiala valida
*/
int valideazaCheltuiala(Cheltuiala chelt);
