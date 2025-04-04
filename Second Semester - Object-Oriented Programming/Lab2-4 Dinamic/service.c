#include "service.h"

Srv creareSrv() {
	Srv srvchelt;
	srvchelt.listacrt = creareLista((dist_fct)(distrugereCheltuiala));
	return srvchelt;
}

void distrugereSrv(Srv* srvchelt) {
	distrugereLista(srvchelt->listacrt);
}

int adaugareChelt(Srv* srvchelt, int nrapart, float suma, char* tip) {
	int stare;
	Cheltuiala* chelt;
	stare = validareCheltuiala(nrapart, suma, tip);
	if (stare == 0) {
		chelt = creareCheltuiala(nrapart, suma, tip);
		return adaugareCheltuiala(srvchelt->listacrt, chelt, egalitateCheltuieli);
	}
	return 1;
}

int modificareChelt(Srv* srvchelt, int nrapart, float suma, char* tip, float sumanoua, char* tipnou) {
	int stare1, stare2, poz;
	Cheltuiala* chelt;
	stare1 = validareCheltuiala(nrapart, suma, tip);
	stare2 = validareCheltuiala(nrapart, sumanoua, tipnou);
	chelt = creareCheltuiala(nrapart, suma, tip);
	poz = cautareCheltuiala(srvchelt->listacrt, chelt, egalitateCheltuieli);
	if (stare1 == 0 && poz != -1 && stare2 == 0) {
		distrugereCheltuiala(chelt);
		chelt = creareCheltuiala(nrapart, sumanoua, tipnou);
		modificareCheltuiala(srvchelt->listacrt, chelt, poz, egalitateCheltuieli);
		return 0;
	}
	distrugereCheltuiala(chelt);
	return 1;
}

int stergereChelt(Srv* srvchelt, int nrapart, float suma, char* tip) {
	int stare;
	Cheltuiala* chelt;
	stare = validareCheltuiala(nrapart, suma, tip);
	if (stare == 0) {
		chelt = creareCheltuiala(nrapart, suma, tip);
		return stergereCheltuiala(srvchelt->listacrt, chelt, egalitateCheltuieli);
	}
	return 1;
}

Repo* filtrareCheltApart(Repo* listachelt, int nrapart, filtapart_fct filt) {
	int i;
	Repo* rez = creareLista(listachelt->dest);
	for (i = 0; i < listachelt->lg; i++) {
		if (filt(listachelt->element[i], nrapart) == 0) {
			adaugareCheltuiala(rez, copieCheltuiala(listachelt->element[i]), egalitateCheltuieli);
		}
	}
	return rez;
}

Repo* filtrareCheltSuma(Repo* listachelt, float suma, filtsuma_fct filt) {
	int i;
	Repo* rez = creareLista(listachelt->dest);
	for (i = 0; i < listachelt->lg; i++) {
		if (filt(listachelt->element[i], suma) == 0) {
			adaugareCheltuiala(rez, copieCheltuiala(listachelt->element[i]), egalitateCheltuieli);
		}
	}
	return rez;
}

Repo* filtrareCheltTip(Repo* listachelt, char* tip, filtip_fct filt) {
	int i;
	Repo* rez = creareLista(listachelt->dest);
	for (i = 0; i < listachelt->lg; i++) {
		if (filt(listachelt->element[i], tip) == 0) {
			adaugareCheltuiala(rez, copieCheltuiala(listachelt->element[i]), egalitateCheltuieli);
		}
	}
	return rez;
}

Repo* sortareCheltSuma(Repo* listachelt, int crescator, cmpsuma_fct cmp) {
	int i, j;
	Repo* rez = copieLista(listachelt, copieCheltuiala);
	if (crescator == 1) {
		for (i = 0; i < rez->lg - 1; i++) {
			for (j = i + 1; j < rez->lg; j++) {
				if (cmp(rez->element[i], rez->element[j]) == 1) {
					ElemType* temp = rez->element[i];
					rez->element[i] = rez->element[j];
					rez->element[j] = temp;
				}
			}
		}
	}
	else {
		for (i = 0; i < rez->lg - 1; i++) {
			for (j = i + 1; j < rez->lg; j++) {
				if (cmp(rez->element[i], rez->element[j]) == 0) {
					ElemType* temp = rez->element[i];
					rez->element[i] = rez->element[j];
					rez->element[j] = temp;
				}
			}
		}
	}
	return rez;
}

Repo* sortareCheltTip(Repo* listachelt, int crescator, cmptip_fct cmp) {
	int i, j;
	Repo* rez = copieLista(listachelt, copieCheltuiala);
	if (crescator == 1) {
		for (i = 0; i < rez->lg - 1; i++) {
			for (j = i + 1; j < rez->lg; j++) {
				if (cmp(rez->element[i], rez->element[j]) == 1) {
					ElemType* temp = rez->element[i];
					rez->element[i] = rez->element[j];
					rez->element[j] = temp;
				}
			}
		}
	}
	else {
		for (i = 0; i < rez->lg - 1; i++) {
			for (j = i + 1; j < rez->lg; j++) {
				if (cmp(rez->element[i], rez->element[j]) == 0) {
					ElemType* temp = rez->element[i];
					rez->element[i] = rez->element[j];
					rez->element[j] = temp;
				}
			}
		}
	}
	return rez;
}