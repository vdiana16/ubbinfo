#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "repository.h"

Repo creareLista() {
	Repo listachelt;

	listachelt.lg = 0;
	return listachelt;
}

void distrugereLista(Repo* listachelt) {
	listachelt->lg = 0;
}

ElemType getCheltuiala(Repo* listachelt, int pozitie) {
	return listachelt->element[pozitie];
}

int lgLista(Repo* listachelt) {
	return listachelt->lg;
}

int verificareCheltuiala(Repo* listachelt, ElemType elem) {
	int i;
	for (i = 0; i < lgLista(listachelt); i++) {
		Cheltuiala c;
		c = getCheltuiala(listachelt, i);
		if (c.nrapart == elem.nrapart && c.suma == elem.suma && strcmp(c.tip, elem.tip) == 0) {
			return 1;
		}
	}
	if (strcmp(elem.tip, "apa") != 0 && strcmp(elem.tip, "gaz") != 0 && strcmp(elem.tip, "canal") != 0 && strcmp(elem.tip, "incalzire") != 0) {
		return 1;
	}
	return 0;
}

int adaugareCheltuiala(Repo* listachelt, ElemType elem) {
	int starec;
	starec = verificareCheltuiala(listachelt, elem);
	if (starec == 0) {
		listachelt->element[lgLista(listachelt)] = elem;
		listachelt->lg++;
		return 0;
	}
	return 1;
}


Repo copiereLista(Repo* listachelt) {
	Repo copielista;
	copielista = creareLista();
	int i;
	for (i = 0; i < lgLista(listachelt); i++) {
		ElemType c;
		c = getCheltuiala(listachelt, i);
		adaugareCheltuiala(&copielista, c);

	}
	return copielista;
}

int modificareCheltuiala(Repo* listachelt, ElemType elem, ElemType elemnou) {
	int i;
	for (i = 0; i < lgLista(listachelt); i++) {
		Cheltuiala c;
		c = getCheltuiala(listachelt, i);
		if (c.nrapart == elem.nrapart && c.suma == elem.suma && strcmp(c.tip, elem.tip) == 0) {
			c.suma = elemnou.suma;
			strcpy_s(c.tip, sizeof(elemnou.tip), elemnou.tip);
			listachelt->element[i] = c;
			return 0;
		}
	}
	return 1;
}

int cautareCheltuiala(Repo* listachelt, ElemType elem) {
	int i, poz = -1;
	Cheltuiala c;
	for (i = 0; i < lgLista(listachelt); i++) {
		c = getCheltuiala(listachelt, i);
		if (c.nrapart == elem.nrapart && c.suma == elem.suma && strcmp(c.tip, elem.tip) == 0) {
			poz = i;
			break;
		}
	}
	return poz;
}

int stergereCheltuiala(Repo* listachelt, ElemType elem) {
	int i, poz;
	Cheltuiala c;
	poz = cautareCheltuiala(listachelt, elem);
	if (poz == -1) {
		return 1;
	}
	for (i = poz; i < lgLista(listachelt) - 1; i++) {
		listachelt->element[i] = listachelt->element[i + 1];
	}
	listachelt->lg--;
	return 0;
}