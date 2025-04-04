#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "domain.h"

Cheltuiala creareCheltuiala(int nrapart, float suma, char* tip) {
	Cheltuiala chelt;
	chelt.nrapart = nrapart;
	chelt.suma = suma;
	strcpy_s(chelt.tip, sizeof(chelt.tip), tip);

	return chelt;
}

void distrugereCheltuiala(Cheltuiala* chelt) {
	chelt->nrapart = -1;
	chelt->suma = -1;
	chelt->tip[0] = '\0';
}

int valideazaCheltuiala(Cheltuiala chelt) {
	if (chelt.nrapart <= 0) {
		return 1;
	}
	if (chelt.suma <= 0) {
		return 2;
	}
	if (strlen(chelt.tip) == 0) {
		return 3;
	}
	return 0;
}