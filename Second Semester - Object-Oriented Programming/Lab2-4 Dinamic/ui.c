#include "ui.h"
#include "domain.h"
#include "repository.h"
#include "service.h"
#include <stdio.h>

void curatareInput() {
	int caracter;
	while ((caracter = getchar()) != '\n' && caracter != EOF) {
	}
}

void afiseazaCheltuiala(Cheltuiala* chelt) {
	printf("Numar apartament: %d \n", chelt->nrapart);
	printf("Suma: %f \n", chelt->suma);
	printf("Tipul cheltuielii: %s \n", chelt->tip);
	printf("\n");
}

void afiseazaCheltuieli(Repo* listachelt) {
	int i;
	Cheltuiala c;
	if (listachelt->lg != 0) {
		printf("\nCheltuielile sunt:\n");
		for (i = 0; i < listachelt->lg; i++) {
			afiseazaCheltuiala((Cheltuiala*)(listachelt->element[i]));
		}
	}
	else {
		printf("Momentan nu exista cheltuieli in lista...\n");
	}
	printf("\n");
}


void adaugare(Srv srvchelt) {
	int nrapart = -1;
	float suma = -1;
	char tip[20] = "";

	printf("Introduceti cheltuiala:\n");
	printf("Numarul apartamentului: ");
	scanf_s("%d", &nrapart);
	curatareInput();
	printf("Suma cheltuielii: ");
	scanf_s("%f", &suma);
	curatareInput();
	printf("Tipul cheltuielii: ");
	scanf_s("%s", tip, 20);

	int stare;
	stare = adaugareChelt(&srvchelt, nrapart, suma, tip);
	if (stare != 0) {
		printf("Eroare la adaugare!\n");
	}
	else {
		printf("Cheltuiala adaugata cu succes!\n");
	}
}

void modificare(Srv srvchelt) {
	int nrapart = -1;
	float suma = -1, sumanoua = -1;
	char tip[20] = "", tipnou[20] = "";

	printf("Introduceti cheltuiala de modificat:\n");
	printf("Numarul apartamentului: ");
	scanf_s("%d", &nrapart);
	curatareInput();
	printf("Suma cheltuielii: ");
	scanf_s("%f", &suma);
	curatareInput();
	printf("Tipul cheltuielii: ");
	scanf_s("%s", tip, 20);
	printf("Introduceti noile caracteristici ale cheltuielii: \n");
	printf("Suma cheltuielii: ");
	scanf_s("%f", &sumanoua);
	curatareInput();
	printf("Tipul cheltuielii: ");
	scanf_s("%s", tipnou, 20);

	int stare;
	stare = modificareChelt(&srvchelt, nrapart, suma, tip, sumanoua, tipnou);
	if (stare != 0) {
		printf("Eroare la modificare!\n");
	}
	else {
		printf("Cheltuiala modificata cu succes!\n");
	}
}

void stergere(Srv srvchelt) {
	int nrapart = -1;
	float suma = -1;
	char tip[20] = "";
	printf("Introduceti cheltuiala:\n");
	printf("Numarul apartamentului: ");
	scanf_s("%d", &nrapart);
	curatareInput();
	printf("Suma cheltuielii: ");
	scanf_s("%f", &suma);
	curatareInput();
	printf("Tipul cheltuielii: ");
	scanf_s("%s", tip, 20);

	int stare;
	stare = stergereChelt(&srvchelt, nrapart, suma, tip);
	if (stare != 0) {
		printf("Eroare la stergere!\n");
	}
	else {
		printf("Cheltuiala stearsa cu suuces!\n");
	}
}

void filtrare(Srv srvchelt) {
	int numarapart, proprietate = 0;
	float sumachelt;
	char tipchelt[20] = "";
	Repo* listarez;
	scanf_s("%d", &proprietate);
	curatareInput();
	switch (proprietate)
	{
	case 1:
		printf("Introduceti numarul apartamentului: ");
		scanf_s("%d", &numarapart);
		curatareInput();
		listarez = filtrareCheltApart(srvchelt.listacrt, numarapart, filtrareApartament);
		if (listarez->lg == 0) {
			printf("Nu s-a gasit nicio filtrare!\n");
		}
		else {
			afiseazaCheltuieli(listarez);
			distrugereLista(listarez);
		}
		break;
	case 2:
		printf("Introduceti suma cheltuielii: ");
		scanf_s("%f", &sumachelt);
		curatareInput();
		listarez = filtrareCheltSuma(srvchelt.listacrt, sumachelt, filtrareSuma);
		if (listarez->lg == 0) {
			printf("Nu s-a gasit nicio filtrare!\n");
		}
		else {
			afiseazaCheltuieli(listarez);
			distrugereLista(listarez);
		}
		break;
	case 3:
		printf("Introduceti tipul cheltuielii: ");
		scanf_s("%s", tipchelt, 20);
		curatareInput();
		listarez = filtrareCheltTip(srvchelt.listacrt, tipchelt, filtrareTip);
		if (listarez->lg == 0) {
			printf("Nu s-a gasit nicio filtrare!\n");
		}
		else {
			afiseazaCheltuieli(listarez);
			distrugereLista(listarez);
		}
		break;
	default:
		printf("Proprietate inexistenta!\n");
		break;
	}
}

void sortare(Srv srvchelt) {
	int criteriu = 0, ordsort = -1;
	Repo* listarez;
	printf("Introduceti criteriul de sortare:\n");
	scanf_s("%d", &criteriu);
	curatareInput();
	switch (criteriu)
	{
	case 1:
		printf("Introduceti ordinea de sortare:\n");
		scanf_s("%d", &ordsort);
		if (ordsort == 0 || ordsort == 1) {
			listarez = sortareCheltSuma(srvchelt.listacrt, ordsort, cmpSuma);
			afiseazaCheltuieli(listarez);
			distrugereLista(listarez);
		}
		break;
	case 2:
		printf("Introduceti ordinea de sortare:\n");
		scanf_s("%d", &ordsort);
		if (ordsort == 0 || ordsort == 1) {
			listarez = sortareCheltTip(srvchelt.listacrt, ordsort, cmpTip);
			afiseazaCheltuieli(listarez);
			distrugereLista(listarez);
		}
		break;
	default:
		break;
	}

}

void meniu() {
	printf("Acestea sunt optiunile posibile:\n");
	printf("    0 - Iesire din program\n");
	printf("    1 - Adauga cheltuiala\n");
	printf("    2 - Modifica cheltuiala\n");
	printf("    3 - Sterge cheltuiala\n");
	printf("    4 - Filtreaza cheltuielile dupa o prioritate\n");
	printf("    5 - Ordoneaza cheltuielile dupa suma/tip\n");
	printf("    6 - Afisarea listei de cheltuieli\n");
}

void minimeniufiltrare() {
	printf("Acestea sunt proprietatile dupa care se poate realiza filtrarea:\n");
	printf("    1 - apartament\n");
	printf("    2 - suma\n");
	printf("    3 - tip\n");
	printf("Introduceti proprietatea dorita:\n ");
	printf("\n");
}

void minimeniusortare() {
	printf("Acestea sunt sortarile disponibile:\n");
	printf("    1 - suma\n");
	printf("    2 - tip\n");
	printf("Aceasta este ordinea de sortare disponibila:\n");
	printf("    1 - crescator\n");
	printf("    0 - descrescator\n");
	printf("\n");
}

void run() {
	int ok = 1, optiune = 0;
	printf("	Aici se afla administrarea unor imobile \n");
	Srv toatecheltuielile = creareSrv();
	while (ok) {
		meniu();
		scanf_s("%d", &optiune);
		curatareInput();
		printf("\n");
		switch (optiune) {
		case 0:
			ok = 0;
			printf("Pa,pa!\n");
			distrugereSrv(&toatecheltuielile);
			break;
		case 1:
			adaugare(toatecheltuielile);
			break;
		case 2:
			modificare(toatecheltuielile);
			break;
		case 3:
			stergere(toatecheltuielile);
			break;
		case 4:
			minimeniufiltrare();
			filtrare(toatecheltuielile);
			break;
		case 5:
			minimeniusortare();
			sortare(toatecheltuielile);
			break;
		case 6:
			afiseazaCheltuieli(toatecheltuielile.listacrt);
		default:
			printf("Optiune invalida!\n");
		}
	}
}