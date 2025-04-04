#include "domain.h"
#include <stdlib.h>
#include <string.h>

Cheltuiala* creareCheltuiala(int nrapart, float suma, char* tip) {
	Cheltuiala* chelt = malloc(sizeof(Cheltuiala));

	chelt->nrapart = nrapart;
	chelt->suma = suma;

	int nrc;
	nrc = (int)strlen(tip) + 1;
	chelt->tip = malloc(nrc * sizeof(char));
	
	strcpy_s(chelt->tip, nrc, tip);

	return chelt;
}

void distrugereCheltuiala(Cheltuiala* chelt) {
	free(chelt->tip);
	free(chelt);
}

int validareCheltuiala(int nrapart, float suma, char* tip) {
	if (nrapart <= 0) {
		return 1;
	}
	if (suma <= 0) {
		return 1;
	}
	if (strlen(tip) == 0) {
		return 1;
	}
	if (strcmp(tip, "apa") != 0 && strcmp(tip, "gaz") != 0 && strcmp(tip, "canal") != 0 && strcmp(tip, "incalzire") != 0) {
		return 1;
	}
	return 0;
}

Cheltuiala* copieCheltuiala(Cheltuiala* a) {
	Cheltuiala* chelt = creareCheltuiala(a->nrapart, a->suma, a->tip);
	return chelt;
}

int egalitateCheltuieli(Cheltuiala* chelt1, Cheltuiala* chelt2) {
	if (chelt1->nrapart == chelt2->nrapart && chelt1->suma == chelt2->suma && strcmp(chelt1->tip, chelt2->tip) == 0) {
		return 1;
	}
	return 0;
}

int cmpSuma(Cheltuiala* chelt1, Cheltuiala* chelt2) {
	if (chelt1->suma > chelt2->suma) {
		return 1;
	}
	return 0;
}

int cmpTip(Cheltuiala* chelt1, Cheltuiala* chelt2) {
	if (strcmp(chelt1->tip, chelt2->tip) > 0) {
		return 1;
	}
	return 0;
}

int filtrareApartament(Cheltuiala* c, int val) {
	if (c->nrapart == val) {
		return 0;
	}
	return 1;
}

int filtrareSuma(Cheltuiala* c, float val) {
	if (c->suma == val) {
		return 0;
	}
	return 1;
}

int filtrareTip(Cheltuiala* c, char* val) {
	if (strcmp(c->tip, val) == 0) {
		return 0;
	}
	return 1;
}
