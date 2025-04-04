#include <string.h>
#include <assert.h>
#include "service.h"

int adaugareChelt(Repo* listachelt, int nrapart, float suma, char* tip) {
	int stare;
	Cheltuiala c;
	c = creareCheltuiala(nrapart, suma, tip);
	stare = valideazaCheltuiala(c);
	if (stare != 0) {
		return stare;
	}
	return adaugareCheltuiala(listachelt, c);
}

int modificareChelt(Repo* listachelt, int nrapart, float suma, char* tip, float sumanoua, char* tipnou) {
	int stare, staren;
	Cheltuiala c, cnoua;
	c = creareCheltuiala(nrapart, suma, tip);
	cnoua = creareCheltuiala(nrapart, sumanoua, tipnou);
	stare = valideazaCheltuiala(c);
	if (stare != 0) {
		return stare;
	}
	staren = valideazaCheltuiala(cnoua);
	if (staren != 0) {
		return staren;
	}
	return modificareCheltuiala(listachelt, c, cnoua);
}

int stergereChelt(Repo* listachelt, int nrapart, float suma, char* tip) {
	int stare;
	Cheltuiala c;
	c = creareCheltuiala(nrapart, suma, tip);
	stare = valideazaCheltuiala(c);
	if (stare != 0) {
		return stare;
	}
	return stergereCheltuiala(listachelt, c);
}

Repo getToateChelt(Repo* listachelt) {
	return copiereLista(listachelt);
}

Repo filtrareApartament(Repo* listachelt, int numarapart) {
	int i;
	Repo listafilt;
	listafilt = creareLista();
	for (i = 0; i < lgLista(listachelt); i++) {
		ElemType c;
		c = getCheltuiala(listachelt, i);
		if (c.nrapart == numarapart) {
			adaugareCheltuiala(&listafilt, c);
		}
	}
	return listafilt;
}

Repo filtrareSuma(Repo* listachelt, float sumachelt) {
	int i;
	Repo listafilt;
	listafilt = creareLista();
	for (i = 0; i < lgLista(listachelt); i++) {
		ElemType c;
		c = getCheltuiala(listachelt, i);
		if (c.suma == sumachelt) {
			adaugareCheltuiala(&listafilt, c);
		}
	}
	return listafilt;
}

Repo filtrareTip(Repo* listachelt, char* tipchelt) {
	int i;
	Repo listafilt;
	listafilt = creareLista();
	for (i = 0; i < lgLista(listachelt); i++) {
		ElemType c;
		c = getCheltuiala(listachelt, i);
		if (strcmp(c.tip,tipchelt) == 0) {
			adaugareCheltuiala(&listafilt, c);
		}
	}
	return listafilt;
}

Repo sortareSuma(Repo* listachelt, int sortare) {
	int i, j;
	Repo listasortata;
	Cheltuiala c;
	listasortata = copiereLista(listachelt);
	if (sortare == 0) {
		for (i = 0; i < lgLista(listachelt) - 1; i++) {
			for (j = i + 1; j < lgLista(listachelt); j++) {
				if (listasortata.element[i].suma > listasortata.element[j].suma) {
					c = listasortata.element[i];
					listasortata.element[i] = listasortata.element[j];
					listasortata.element[j] = c;
				}
			}
		}
	}
	else if (sortare == 1){
		for (i = 0; i < lgLista(listachelt) - 1; i++) {
			for (j = i + 1; j < lgLista(listachelt); j++) {
				if (listasortata.element[i].suma < listasortata.element[j].suma) {
					c = listasortata.element[i];
					listasortata.element[i] = listasortata.element[j];
					listasortata.element[j] = c;
				}
			}
		}
	}
	return listasortata;
}

Repo sortareTip(Repo* listachelt, int sortare) {
	int i, j;
	Repo listasortata;
	Cheltuiala c;
	listasortata = copiereLista(listachelt);
	if (sortare == 0) {
		for (i = 0; i < lgLista(listachelt) - 1; i++) {
			for (j = i + 1; j < lgLista(listachelt); j++) {
				if (strcmp(listasortata.element[i].tip, listasortata.element[j].tip) > 0) {
					c = listasortata.element[i];
					listasortata.element[i] = listasortata.element[j];
					listasortata.element[j] = c;
				}
			}
		}
	}
	else if (sortare == 1) {
		for (i = 0; i < lgLista(listachelt) - 1; i++) {
			for (j = i + 1; j < lgLista(listachelt); j++) {
				if (strcmp(listasortata.element[i].tip, listasortata.element[j].tip) < 0) {
					c = listasortata.element[i];
					listasortata.element[i] = listasortata.element[j];
					listasortata.element[j] = c;
				}
			}
		}
	}
	return listasortata;
}