#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "teste.h"
#include "domain.h"
#include "repository.h"
#include "service.h"

void ruleazaTeste() {
	testCreareCheltuiala();
	testDistrugereCheltuiala();

	testCreareLista();
	testAdugareCheltuiala();
	testVerificareCheltuiala();
	testModificareCheltuiala();
	testCopiereLista();
	testCautareCheltuiala();
	testStergereCheltuiala();

	testAdaugareChelt();
	testModificareChelt();
	testStergereChelt();
	testFiltrareTip();
	testFiltrareApartament();
	testFiltrareSuma();
	testSortareSuma();
	testSortareTip();
}

void testCreareCheltuiala() {
	Cheltuiala chelt = creareCheltuiala(1, 100, "apa");

	assert(chelt.nrapart == 1);
	assert(chelt.suma == 100);
	assert(strcmp(chelt.tip, "apa") == 0);

}

void testDistrugereCheltuiala() {
	Cheltuiala chelt = creareCheltuiala(1, 100, "apa");
	distrugereCheltuiala(&chelt);
	assert(chelt.nrapart == -1);
	assert(chelt.suma == -1);
	assert(strlen(chelt.tip) == 0);
}


void testCreareLista() {
	Repo listat;
	listat = creareLista();

	assert(lgLista(&listat) == 0);
}

void testAdugareCheltuiala() {
	Repo listat;
	listat = creareLista();
	Cheltuiala chelt1, chelt2, chelt3, chelt4, chelt;
	chelt1 = creareCheltuiala(10, 100, "apa");
	chelt2 = creareCheltuiala(8, 20, "gaz");
	chelt3 = creareCheltuiala(16, 10, "canal");
	chelt4 = creareCheltuiala(16, 10, "c");

	assert(adaugareCheltuiala(&listat, chelt1) == 0);
	assert(adaugareCheltuiala(&listat, chelt2) == 0);
	assert(adaugareCheltuiala(&listat, chelt3) == 0);
	assert(adaugareCheltuiala(&listat, chelt1) == 1);
	assert(adaugareCheltuiala(&listat, chelt4) == 1);
	assert(lgLista(&listat) == 3);

	chelt = getCheltuiala(&listat, 0);
	assert(chelt.nrapart == 10);
	chelt = getCheltuiala(&listat, 1);
	assert(chelt.suma == 20);
	chelt = getCheltuiala(&listat, 2);
	assert(strcmp(chelt.tip, "canal") == 0);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
}

void testVerificareCheltuiala() {
	Repo listat;
	listat = creareLista();
	Cheltuiala chelt1, chelt2;
	chelt1 = creareCheltuiala(8, 20, "gaz");
	chelt2 = creareCheltuiala(16, 10, "canal");

	assert(verificareCheltuiala(&listat, chelt1) == 0);

	assert(adaugareCheltuiala(&listat, chelt1) == 0);
	assert(adaugareCheltuiala(&listat, chelt2) == 0);
	assert(lgLista(&listat) == 2);

	assert(verificareCheltuiala(&listat, chelt1) == 1);
	assert(lgLista(&listat) == 2);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
}

void testCopiereLista() {
	Repo listat, listatcop;
	listat = creareLista();
	Cheltuiala chelt1, chelt2, chelt;
	chelt1 = creareCheltuiala(8, 20, "gaz");
	chelt2 = creareCheltuiala(16, 10, "canal");

	assert(adaugareCheltuiala(&listat, chelt1) == 0);
	assert(adaugareCheltuiala(&listat, chelt2) == 0);
	assert(lgLista(&listat) == 2);

	listatcop = copiereLista(&listat);
	assert(lgLista(&listatcop) == 2);

	chelt = getCheltuiala(&listat, 0);
	assert(chelt.suma == 20);

}

void testModificareCheltuiala() {
	Repo listat;
	listat = creareLista();
	Cheltuiala chelt1, chelt2, chelt3, chelt;
	chelt1 = creareCheltuiala(8, 20, "gaz");
	chelt2 = creareCheltuiala(16, 10, "canal");
	chelt3 = creareCheltuiala(16, 100, "incalzire");

	assert(adaugareCheltuiala(&listat, chelt1) == 0);
	assert(adaugareCheltuiala(&listat, chelt2) == 0);
	assert(lgLista(&listat) == 2);

	assert(modificareCheltuiala(&listat, chelt2, chelt3) == 0);
	chelt = getCheltuiala(&listat, 1);
	assert(chelt.suma == chelt3.suma);
	assert(strcmp(chelt.tip, chelt3.tip) == 0);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
}

void testCautareCheltuiala() {
	Repo listat;
	listat = creareLista();
	Cheltuiala chelt1, chelt2, chelt3, chelt4;
	chelt1 = creareCheltuiala(8, 20, "gaz");
	chelt2 = creareCheltuiala(16, 10, "apa");
	chelt3 = creareCheltuiala(17, 100, "gaz");
	chelt4 = creareCheltuiala(100, 100, "apa");

	assert(adaugareCheltuiala(&listat, chelt1) == 0);
	assert(adaugareCheltuiala(&listat, chelt2) == 0);
	assert(adaugareCheltuiala(&listat, chelt3) == 0);
	assert(lgLista(&listat) == 3);

	assert(cautareCheltuiala(&listat, chelt1) == 0);
	assert(cautareCheltuiala(&listat, chelt4) == -1);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
}

void testStergereCheltuiala() {
	Repo listat;
	listat = creareLista();
	Cheltuiala chelt1, chelt2, chelt3, chelt4;
	chelt1 = creareCheltuiala(8, 20, "gaz");
	chelt2 = creareCheltuiala(16, 10, "canal");
	chelt3 = creareCheltuiala(17, 100, "incalzire");
	chelt4 = creareCheltuiala(100, 100, "apa");

	assert(adaugareCheltuiala(&listat, chelt1) == 0);
	assert(adaugareCheltuiala(&listat, chelt2) == 0);
	assert(adaugareCheltuiala(&listat, chelt3) == 0);
	assert(lgLista(&listat) == 3);

	assert(stergereCheltuiala(&listat, chelt2) == 0);
	assert(stergereCheltuiala(&listat, chelt4) == 1);
	assert(lgLista(&listat) == 2);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
}

void testAdaugareChelt() {
	int stare;
	Repo listat, listacop;
	listat = creareLista();

	stare = adaugareChelt(&listat, 0, 0, "");
	assert(stare != 0);
	assert(lgLista(&listat) == 0);
	stare = adaugareChelt(&listat, 9, 0, "");
	assert(stare != 0);
	assert(lgLista(&listat) == 0);
	stare = adaugareChelt(&listat, 10, 100, "");
	assert(stare != 0);
	assert(lgLista(&listat) == 0);

	assert(adaugareChelt(&listat, 10, 100, "apa") == 0);
	assert(adaugareChelt(&listat, 88, 120, "gaz") == 0);
	assert(adaugareChelt(&listat, 90, 20, "canal") == 0);
	listacop = getToateChelt(&listat);
	assert(lgLista(&listacop) == 3);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
	distrugereLista(&listacop);
	assert(lgLista(&listacop) == 0);
}

void testModificareChelt() {
	int stare;
	Repo listat, listacop;
	Cheltuiala chelt;
	listat = creareLista();

	stare = modificareChelt(&listat, 2, 100, "apa", 1000, "gaz");
	assert(stare != 0);
	assert(lgLista(&listat) == 0);

	assert(adaugareChelt(&listat, 10, 100, "apa") == 0);
	assert(adaugareChelt(&listat, 88, 120, "gaz") == 0);
	assert(adaugareChelt(&listat, 90, 20, "canal") == 0);
	assert(modificareChelt(&listat, 88, 120, "gaz", 100, "apa") == 0);
	assert(modificareChelt(&listat, 88, 120, "", 90, "apa") != 0);
	assert(modificareChelt(&listat, 88, 120, "gaz", 0, "") != 0);
	chelt = getCheltuiala(&listat, 1);
	assert(chelt.nrapart == 88);
	assert(chelt.suma == 100);
	assert(strcmp(chelt.tip, "apa") == 0);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
	distrugereLista(&listacop);
	assert(lgLista(&listacop) == 0);
}

void testStergereChelt() {
	int stare;
	Repo listat;
	Cheltuiala chelt;
	listat = creareLista();

	stare = stergereChelt(&listat, 22, 100, "apa");
	assert(stare != 0);
	assert(lgLista(&listat) == 0);

	assert(adaugareChelt(&listat, 10, 100, "apa") == 0);
	assert(adaugareChelt(&listat, 88, 120, "gaz") == 0);
	assert(adaugareChelt(&listat, 90, 20, "canal") == 0);
	assert(lgLista(&listat) == 3);
	assert(stergereChelt(&listat, 90, 20, "canal") == 0);
	assert(stergereChelt(&listat, 90, 20, "") != 0);
	assert(lgLista(&listat) == 2);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
}

void testFiltrareTip() {
	Repo listat, listacop;
	Cheltuiala chelt1, chelt2;
	listat = creareLista();

	assert(lgLista(&listat) == 0);
	assert(adaugareChelt(&listat, 10, 100, "canal") == 0);
	assert(adaugareChelt(&listat, 88, 120, "gaz") == 0);
	assert(adaugareChelt(&listat, 90, 20, "canal") == 0);
	assert(adaugareChelt(&listat, 180, 90, "canal") == 0);
	assert(adaugareChelt(&listat, 88, 99, "incalzire") == 0);
	assert(lgLista(&listat) == 5);
	listacop = filtrareTip(&listat, "canal");
	assert(lgLista(&listacop) == 3);
	chelt1 = getCheltuiala(&listacop, 0);
	chelt2 = getCheltuiala(&listat, 0);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);
	chelt1 = getCheltuiala(&listacop, 1);
	chelt2 = getCheltuiala(&listat, 2);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);
	chelt1 = getCheltuiala(&listacop, 2);
	chelt2 = getCheltuiala(&listat, 3);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
	distrugereLista(&listacop);
	assert(lgLista(&listacop) == 0);
}

void testFiltrareApartament() {
	Repo listat, listacop;
	Cheltuiala chelt1, chelt2;
	listat = creareLista();

	assert(lgLista(&listat) == 0);
	assert(adaugareChelt(&listat, 10, 100, "canal") == 0);
	assert(adaugareChelt(&listat, 88, 120, "gaz") == 0);
	assert(adaugareChelt(&listat, 10, 20, "canal") == 0);
	assert(adaugareChelt(&listat, 180, 90, "canal") == 0);
	assert(adaugareChelt(&listat, 9, 99, "incalzire") == 0);
	assert(lgLista(&listat) == 5);
	listacop = filtrareApartament(&listat, 10);
	assert(lgLista(&listacop) == 2);
	chelt1 = getCheltuiala(&listacop, 0);
	chelt2 = getCheltuiala(&listat, 0);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);
	chelt1 = getCheltuiala(&listacop, 1);
	chelt2 = getCheltuiala(&listat, 2);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
	distrugereLista(&listacop);
	assert(lgLista(&listacop) == 0);
}

void testFiltrareSuma() {
	Repo listat, listacop;
	Cheltuiala chelt1, chelt2;
	listat = creareLista();

	assert(lgLista(&listat) == 0);
	assert(adaugareChelt(&listat, 10, 20, "canal") == 0);
	assert(adaugareChelt(&listat, 88, 120, "gaz") == 0);
	assert(adaugareChelt(&listat, 100, 20, "canal") == 0);
	assert(adaugareChelt(&listat, 180, 20, "apa") == 0);
	assert(adaugareChelt(&listat, 9, 20, "incalzire") == 0);
	assert(lgLista(&listat) == 5);
	listacop = filtrareSuma(&listat, 20);
	assert(lgLista(&listacop) == 4);
	chelt1 = getCheltuiala(&listacop, 0);
	chelt2 = getCheltuiala(&listat, 0);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);
	chelt1 = getCheltuiala(&listacop, 1);
	chelt2 = getCheltuiala(&listat, 2);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);
	chelt1 = getCheltuiala(&listacop, 2);
	chelt2 = getCheltuiala(&listat, 3);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);
	chelt1 = getCheltuiala(&listacop, 3);
	chelt2 = getCheltuiala(&listat, 4);
	assert(chelt1.nrapart == chelt2.nrapart);
	assert(chelt1.suma == chelt2.suma);
	assert(strcmp(chelt1.tip, chelt2.tip) == 0);


	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
	distrugereLista(&listacop);
	assert(lgLista(&listacop) == 0);
}

void testSortareSuma() {
	Repo listat, listacop;
	Cheltuiala chelt1, chelt2;
	listat = creareLista();

	assert(lgLista(&listat) == 0);
	assert(adaugareChelt(&listat, 10, 22, "canal") == 0);
	assert(adaugareChelt(&listat, 88, 80, "gaz") == 0);
	assert(adaugareChelt(&listat, 100, 99, "canal") == 0);
	assert(adaugareChelt(&listat, 180, 16, "apa") == 0);
	assert(adaugareChelt(&listat, 9, 90, "incalzire") == 0);

	listacop = sortareSuma(&listat, 0);
	chelt1 = getCheltuiala(&listacop, 0);
	chelt2 = getCheltuiala(&listat, 3);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 1);
	chelt2 = getCheltuiala(&listat, 0);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 2);
	chelt2 = getCheltuiala(&listat, 1);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 3);
	chelt2 = getCheltuiala(&listat, 4);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 4);
	chelt2 = getCheltuiala(&listat, 2);
	assert(chelt1.suma == chelt2.suma);
	
	listacop = sortareSuma(&listat, 1);
	chelt1 = getCheltuiala(&listacop, 0);
	chelt2 = getCheltuiala(&listat, 2);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 1);
	chelt2 = getCheltuiala(&listat, 4);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 2);
	chelt2 = getCheltuiala(&listat, 1);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 3);
	chelt2 = getCheltuiala(&listat, 0);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 4);
	chelt2 = getCheltuiala(&listat, 3);
	assert(chelt1.suma == chelt2.suma);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
	distrugereLista(&listacop);
	assert(lgLista(&listacop) == 0);
	
}

void testSortareTip() {
	Repo listat, listacop;
	Cheltuiala chelt1, chelt2;
	listat = creareLista();

	assert(lgLista(&listat) == 0);
	assert(adaugareChelt(&listat, 10, 22, "canal") == 0);
	assert(adaugareChelt(&listat, 88, 80, "gaz") == 0);
	assert(adaugareChelt(&listat, 100, 99, "canal") == 0);
	assert(adaugareChelt(&listat, 180, 16, "apa") == 0);
	assert(adaugareChelt(&listat, 9, 90, "incalzire") == 0);

	listacop = sortareTip(&listat, 0);
	chelt1 = getCheltuiala(&listacop, 0);
	chelt2 = getCheltuiala(&listat, 3);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 1);
	chelt2 = getCheltuiala(&listat, 2);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 2);
	chelt2 = getCheltuiala(&listat, 0);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 3);
	chelt2 = getCheltuiala(&listat, 1);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 4);
	chelt2 = getCheltuiala(&listat, 4);
	assert(chelt1.suma == chelt2.suma);

	listacop = sortareTip(&listat, 1);
	chelt1 = getCheltuiala(&listacop, 0);
	chelt2 = getCheltuiala(&listat, 4);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 1);
	chelt2 = getCheltuiala(&listat, 1);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 2);
	chelt2 = getCheltuiala(&listat, 2);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 3);
	chelt2 = getCheltuiala(&listat, 0);
	assert(chelt1.suma == chelt2.suma);
	chelt1 = getCheltuiala(&listacop, 4);
	chelt2 = getCheltuiala(&listat, 3);
	assert(chelt1.suma == chelt2.suma);

	distrugereLista(&listat);
	assert(lgLista(&listat) == 0);
	distrugereLista(&listacop);
	assert(lgLista(&listacop) == 0);

}
