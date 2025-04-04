#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "repository.h"

Repo* creareLista(dist_fct f) {
	Repo* listachelt;
	listachelt = malloc(sizeof(Repo));

	listachelt->lg = 0;
	listachelt->cp = 2;
	listachelt->element = malloc(listachelt->cp * sizeof(ElemType));
	listachelt->dest = f;

	return listachelt;
}

void distrugereLista(Repo* listachelt) {
	int i;
	for (i = 0; i < listachelt->lg; i++) {
		listachelt->dest(listachelt->element[i]);
	}
	free(listachelt->element);
	free(listachelt);
}

void redimensionareLista(Repo* listachelt) {
	int i;
	listachelt->cp = listachelt->cp * 2;
	ElemType* temp;
	temp = malloc(listachelt->cp * sizeof(ElemType));
	for (i = 0; i < listachelt->lg; i++) {
		temp[i] = listachelt->element[i];
	}
	free(listachelt->element);
	listachelt->element = temp;
}

int cautareCheltuiala(Repo* listachelt, ElemType* elem, egal_fct eq) {
	int i;
	for (i = 0; i < listachelt->lg; i++) {
		if (eq(listachelt->element[i], elem) == 1) {
			return i;
		}
	}
	return -1;
}

int adaugareCheltuiala(Repo* listachelt, ElemType* elem, egal_fct eq) {
	int poz;
	poz = cautareCheltuiala(listachelt, elem, eq);
	if (poz == -1) {
		if (listachelt->lg == listachelt->cp) {
			redimensionareLista(listachelt);
		}
		listachelt->element[listachelt->lg++] = elem;
		return 0;
	}
	distrugereCheltuiala(elem);
	return 1;
}

void modificareCheltuiala(Repo* listachelt, ElemType* elem, int poz, egal_fct eq) {
	listachelt->dest(listachelt->element[poz]);
	listachelt->element[poz] = elem;
}


int stergereCheltuiala(Repo* listachelt, ElemType* elem, egal_fct eq) {
	int poz, i;
	poz = cautareCheltuiala(listachelt, elem, eq);
	if (poz != -1) {
		listachelt->dest(listachelt->element[poz]);
		for (i = poz; i < listachelt->lg - 1; i++) {
			listachelt->element[i] = listachelt->element[i + 1];
		}
		listachelt->lg--;
		listachelt->dest(elem);
		return 0;
	}
	distrugereCheltuiala(elem);
	return 1;
}

Repo* copieLista(Repo* listachelt, cop_fct cp) {
	Repo* listacop;
	int i;
	listacop = creareLista(listachelt->dest);
	for (i = 0; i < listachelt->lg; i++) {
		adaugareCheltuiala(listacop, cp(listachelt->element[i]), egalitateCheltuieli);
	}
	return listacop;
}