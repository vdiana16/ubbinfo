#include <stdio.h>
#include "ui.h"

void curatareInput() {
	int caracter;
	while ((caracter = getchar()) != '\n' && caracter != EOF) {
	}
}

void afiseazaCheltuieli(Repo* listachelt) {
	int i;
	Cheltuiala c;
	printf("\nCheltuielile sunt:\n");
	if (lgLista(listachelt) != 0) {
		for (i = 0; i < lgLista(listachelt); i++) {
			c = getCheltuiala(listachelt, i);
			printf("Numarul apartamentului este: %d \n", c.nrapart);
			printf("Suma cheltuielii este: %f \n", c.suma);
			printf("Tipul cheltuielii este: %s \n", c.tip);
			printf("\n");
		}
	}
	else {
		printf("Momentan nu exista cheltuieli in lista...\n");
	}
	printf("\n");
}


void adaugare(Repo* listachelt) {
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
	stare = adaugareChelt(listachelt, nrapart, suma, tip);
	if (stare != 0) {
		printf("Cheltuiala invalida!\n");
	}
	else {
		printf("Cheltuiala adaugata cu succes!\n");
	}
}

void modificare(Repo* listachelt) {
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
	stare = modificareChelt(listachelt, nrapart, suma, tip, sumanoua, tipnou);
	if (stare != 0) {
		printf("Cheltuiala nemodificata!\n");
	}
	else {
		printf("Cheltuiala modificata cu succes!\n");
	}
}

void stergere(Repo* listachelt) {
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
	stare = stergereChelt(listachelt, nrapart, suma, tip);
	if (stare != 0) {
		printf("Cheltuiala inexistenta!\n");
	}
	else {
		printf("Cheltuiala stearsa cu suuces!\n");
	}
}

void filtrare(Repo* listachelt) {
	int numarapart, proprietate = 0;
	float sumachelt;
	char tipchelt[20] = "";
	Repo listarez;
	listarez = creareLista();
	scanf_s("%d", &proprietate);
	curatareInput();
	switch (proprietate)
	{
	case 1:
		printf("Introduceti numarul apartamentului: ");
		scanf_s("%d", &numarapart);
		curatareInput();
		listarez = filtrareApartament(listachelt, numarapart);
		if (lgLista(&listarez) == 0) {
			printf("Nu s-a gasit nicio filtrare!\n");
		}
		else {
			afiseazaCheltuieli(&listarez);
		}
		break;
	case 2:
		printf("Introduceti suma cheltuielii: ");
		scanf_s("%f", &sumachelt);
		curatareInput();
		listarez = filtrareSuma(listachelt, sumachelt);
		if (lgLista(&listarez) == 0) {
			printf("Nu s-a gasit nicio filtrare!\n");
		}
		else {
			afiseazaCheltuieli(&listarez);
		}
		break;
	case 3:
		printf("Introduceti tipul cheltuielii: ");
		scanf_s("%s", tipchelt, 20);
		curatareInput();
		listarez = filtrareTip(listachelt, tipchelt);
		if (lgLista(&listarez) == 0) {
			printf("Nu s-a gasit nicio filtrare!\n");
		}
		else {
			afiseazaCheltuieli(&listarez);
		}
		break;
	default:
		printf("Proprietate inexistenta!");
		break;
	}
}

void sortare(Repo* listachelt) {
	int criteriu = 0, ordsort = -1;
	Repo listarez;
	listarez = creareLista();
	printf("Introduceti criteriul de sortare:\n");
	scanf_s("%d", &criteriu);
	curatareInput();
	switch (criteriu)
	{
	case 1:
		printf("Introduceti ordinea de sortare:\n");
		scanf_s("%d", &ordsort);
		if (ordsort == 0 || ordsort == 1) {
			listarez = sortareSuma(listachelt, ordsort);
			afiseazaCheltuieli(&listarez);
		}
		break;
	case 2:
		printf("Introduceti ordinea de sortare:\n");
		scanf_s("%d", &ordsort);
		if (ordsort == 0 || ordsort == 1) {
			listarez = sortareTip(listachelt, ordsort);
			afiseazaCheltuieli(&listarez);
		}
		break;
	default:
		break;
	}

}

void meniu() {
	printf("Acestea sunt optiunile posibile:\n");
	printf("    1 - Adauga cheltuiala\n");
	printf("    2 - Modifica cheltuiala\n");
	printf("    3 - Sterge cheltuiala\n");
	printf("    4 - Filtreaza cheltuielile dupa o prioritate\n");
	printf("    5 - Ordoneaza cheltuielile dupa suma/tip\n");
}

void minimeniufiltrare() {
	printf("Acestea sunt proprietatile dupa care se poate realiza filtrarea:\n");
	printf("    1 - apartament");
	printf("    2 - suma");
	printf("    3 - tip");
	printf("Introduceti proprietatea dorita:\n ");
	printf("\n");
}

void minimeniusortare() {
	printf("Acestea sunt sortarile disponibile:\n");
	printf("    1 - suma");
	printf("    2 - tip");
	printf("    0 - crescator");
	printf("    1 - descrescator");
	printf("\n");
}

void run() {
	int ok = 1, optiune = 0;
	printf("	Aici se afla administrarea unor imobile\n");
	Repo toatecheltuielile = creareLista();
	while (ok) {
		afiseazaCheltuieli(&toatecheltuielile);
		meniu();
		scanf_s("%d", &optiune);
		curatareInput();
		printf("\n");
		switch (optiune) {
		case 0:
			ok = 0;
			printf("Pa,pa!\n");
			break;
		case 1:
			adaugare(&toatecheltuielile);
			break;
		case 2:
			modificare(&toatecheltuielile);
			break;
		case 3:
			stergere(&toatecheltuielile);
			break;
		case 4:
			minimeniufiltrare();
			filtrare(&toatecheltuielile);
			break;
		case 5:
			minimeniusortare();
			sortare(&toatecheltuielile);
			break;
		default:
			printf("Optiune invalida!");
		}
	}
}
