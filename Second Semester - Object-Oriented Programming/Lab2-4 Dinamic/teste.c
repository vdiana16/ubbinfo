#include "teste.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void runTeste() {
	//teste domain
	testCreareCheltuiala();
	testValidareCheltuiala();
	testCopieCheltuiala();
	testEgalitateCheltuieli();
	testCmpSuma();
	testCmpTip();
	testFiltrareApartament();
	testFiltrareSuma();
	testFiltrareTip();

	//teste repository
	testCreareLista();
	testAdaugareCheltuiala();
	testCautareCheltuiala();
	testModificareCheltuiala();
	testStergereCheltuiala();
	testcopieLista();

	// teste service
	testCreareSrv();
	testAdaugareChelt();
	testModificareChelt();
	testStergereChelt();
	testFiltrareCheltApart();
	testFiltrareCheltSuma();
	testFiltrareCheltTip();
	testSortareCheltSuma();
	testSortareCheltTip();
}

void testCreareCheltuiala() {
	Cheltuiala* chelt = creareCheltuiala(10, 210, "apa");
	
	assert(chelt != NULL);
	assert(chelt->nrapart == 10);
	assert(chelt->suma == 210);
	assert(strcmp(chelt->tip, "apa") == 0);

	distrugereCheltuiala(chelt);

}

void testValidareCheltuiala() {
	assert(validareCheltuiala(1, 20, "") == 1);
	assert(validareCheltuiala(1, 0, "") == 1);
	assert(validareCheltuiala(0, 0, "") == 1);
	assert(validareCheltuiala(1, 90, "curent") == 1);
	assert(validareCheltuiala(1, 90, "apa") == 0);
}

void testCopieCheltuiala() {
	Cheltuiala* chelt, * cheltcop;
	chelt = creareCheltuiala(1, 90, "apa");

	cheltcop = copieCheltuiala(chelt);

	assert(egalitateCheltuieli(chelt, cheltcop) == 1);

	distrugereCheltuiala(chelt);
	distrugereCheltuiala(cheltcop);
}

void testEgalitateCheltuieli(){
	Cheltuiala* chelt1, *chelt2, *chelt3, *chelt4;
	chelt1 = creareCheltuiala(1, 90, "apa");
	chelt2 = creareCheltuiala(1, 90, "gaz");
	chelt3 = creareCheltuiala(1, 90, "apa");
	chelt4 = creareCheltuiala(10, 90, "apa");

	assert(egalitateCheltuieli(chelt1, chelt3) == 1);
	assert(egalitateCheltuieli(chelt1, chelt2) == 0);
	assert(egalitateCheltuieli(chelt1, chelt4) == 0);

	distrugereCheltuiala(chelt1);
	distrugereCheltuiala(chelt2);
	distrugereCheltuiala(chelt3);
	distrugereCheltuiala(chelt4);
}

void testCmpSuma() {
	Cheltuiala* chelt1, * chelt2, * chelt3, * chelt4;
	chelt1 = creareCheltuiala(1, 190, "apa");
	chelt2 = creareCheltuiala(2, 90, "gaz");
	chelt3 = creareCheltuiala(3, 80, "canal");
	chelt4 = creareCheltuiala(10, 90, "apa");

	assert(cmpSuma(chelt1, chelt2) == 1);
	assert(cmpSuma(chelt3, chelt2) == 0);
	assert(cmpSuma(chelt2, chelt4) == 0);

	distrugereCheltuiala(chelt1);
	distrugereCheltuiala(chelt2);
	distrugereCheltuiala(chelt3);
	distrugereCheltuiala(chelt4);
}

void testCmpTip() {
	Cheltuiala* chelt1, * chelt2, * chelt3, * chelt4;
	chelt1 = creareCheltuiala(1, 190, "apa");
	chelt2 = creareCheltuiala(2, 90, "gaz");
	chelt3 = creareCheltuiala(3, 80, "canal");
	chelt4 = creareCheltuiala(10, 90, "apa");

	assert(cmpTip(chelt2, chelt1) == 1);
	assert(cmpTip(chelt2, chelt3) == 1);
	assert(cmpTip(chelt1, chelt4) == 0);

	distrugereCheltuiala(chelt1);
	distrugereCheltuiala(chelt2);
	distrugereCheltuiala(chelt3);
	distrugereCheltuiala(chelt4);
}

void testFiltrareApartament() {
	Cheltuiala* chelt1, * chelt2;
	chelt1 = creareCheltuiala(1, 190, "apa");
	chelt2 = creareCheltuiala(2, 90, "gaz");

	assert(filtrareApartament(chelt1, 10) == 1);
	assert(filtrareApartament(chelt2, 2) == 0);

	distrugereCheltuiala(chelt1);
	distrugereCheltuiala(chelt2);
}

void testFiltrareSuma() {
	Cheltuiala* chelt1, * chelt2;
	chelt1 = creareCheltuiala(1, 190, "apa");
	chelt2 = creareCheltuiala(2, 90, "gaz");

	assert(filtrareSuma(chelt1, 190) == 0);
	assert(filtrareSuma(chelt2, 900) == 1);

	distrugereCheltuiala(chelt1);
	distrugereCheltuiala(chelt2);
}

void testFiltrareTip() {
	Cheltuiala* chelt1, * chelt2;
	chelt1 = creareCheltuiala(1, 190, "apa");
	chelt2 = creareCheltuiala(2, 90, "gaz");

	assert(filtrareTip(chelt1, "gaz") == 1);
	assert(filtrareTip(chelt2, "gaz") == 0);

	distrugereCheltuiala(chelt1);
	distrugereCheltuiala(chelt2);
}

void testCreareLista() {
	Repo* lista = creareLista(distrugereCheltuiala);
	
	assert(lista->cp == 2);
	assert(lista->lg == 0);
	distrugereLista(lista);
}

void testAdaugareCheltuiala() {
	Repo* lista = creareLista(distrugereCheltuiala);
	Cheltuiala* chelt1, * chelt2, * chelt3;
	chelt1 = creareCheltuiala(1, 20, "apa");
	chelt2 = creareCheltuiala(2, 120, "gaz");
	chelt3 = creareCheltuiala(1, 20, "apa");

	assert(adaugareCheltuiala(lista,chelt1,egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt2, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt3, egalitateCheltuieli) == 1);
	assert(lista->lg == 2);

	distrugereLista(lista);
}

void testCautareCheltuiala() {
	Repo* lista = creareLista(distrugereCheltuiala);
	Cheltuiala* chelt1, * chelt2, * chelt3, * chelt4;
	chelt1 = creareCheltuiala(1, 20, "apa");
	chelt2 = creareCheltuiala(2, 120, "gaz");
	chelt3 = creareCheltuiala(3, 90, "canal");
	chelt4 = creareCheltuiala(4, 99.10, "canal");

	assert(adaugareCheltuiala(lista, chelt1, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt2, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt3, egalitateCheltuieli) == 0);
	assert(lista->lg == 3);
	assert(cautareCheltuiala(lista, chelt1, egalitateCheltuieli) == 0);
	assert(cautareCheltuiala(lista, chelt4, egalitateCheltuieli) == -1);

	distrugereLista(lista);
	distrugereCheltuiala(chelt4);
}

void testModificareCheltuiala() {
	Repo* lista = creareLista(distrugereCheltuiala);
	Cheltuiala* chelt1, * chelt2, * chelt3, * chelt4;
	chelt1 = creareCheltuiala(1, 20, "apa");
	chelt2 = creareCheltuiala(2, 120, "gaz");
	chelt3 = creareCheltuiala(3, 90, "canal");
	chelt4 = creareCheltuiala(1, 190, "incalzire");

	assert(adaugareCheltuiala(lista, chelt1, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt2, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt3, egalitateCheltuieli) == 0);
	assert(lista->lg == 3);
	modificareCheltuiala(lista, chelt4, 0, egalitateCheltuieli);
	assert(((Cheltuiala*)(lista->element[0]))->suma == 190);
	assert(strcmp(((Cheltuiala*)(lista->element[0]))->tip, "incalzire") == 0);
	assert(lista->lg == 3);

	distrugereLista(lista);
}

void testStergereCheltuiala() {
	Repo* lista = creareLista(distrugereCheltuiala);
	Cheltuiala* chelt1, * chelt2, * chelt3, * chelt4;
	chelt1 = creareCheltuiala(1, 20, "apa");
	chelt2 = creareCheltuiala(2, 120, "gaz");
	chelt3 = creareCheltuiala(3, 90, "canal");
	chelt4 = creareCheltuiala(91, 210, "apa");

	assert(adaugareCheltuiala(lista, chelt1, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt2, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt3, egalitateCheltuieli) == 0);
	assert(lista->lg == 3);
	assert(stergereCheltuiala(lista, chelt4, egalitateCheltuieli) == 1);
	assert(lista->lg == 3);
	chelt1 = creareCheltuiala(1, 20, "apa");
	assert(stergereCheltuiala(lista, chelt1, egalitateCheltuieli) == 0);
	assert(lista->lg == 2);

	distrugereLista(lista);
}

void testcopieLista() {
	Repo* lista = creareLista(distrugereCheltuiala), * listacop;
	Cheltuiala* chelt1, * chelt2, * chelt3;
	chelt1 = creareCheltuiala(1, 20, "apa");
	chelt2 = creareCheltuiala(2, 120, "gaz");
	chelt3 = creareCheltuiala(3, 90, "canal");
	
	assert(adaugareCheltuiala(lista, chelt1, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt2, egalitateCheltuieli) == 0);
	assert(adaugareCheltuiala(lista, chelt3, egalitateCheltuieli) == 0);
	assert(lista->lg == 3);
	listacop = copieLista(lista, copieCheltuiala);
	assert(listacop->lg == 3);
	assert(strcmp(((Cheltuiala*)(lista->element[0]))->tip, ((Cheltuiala*)(listacop->element[0]))->tip) == 0);

	distrugereLista(listacop);
	distrugereLista(lista);
}

void testCreareSrv() {
	Srv srvtest;
	srvtest = creareSrv();

	assert((srvtest.listacrt->lg) == 0);
	assert((srvtest.listacrt->cp) == 2);
	
	distrugereSrv(&srvtest);
}

void testAdaugareChelt() {
	Srv srvtest;
	srvtest = creareSrv();

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(srvtest.listacrt->lg == 2);
	assert(adaugareChelt(&srvtest, 12, 100, "internet") == 1);
	assert(adaugareChelt(&srvtest, 120, 0, "") == 1);
	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 1);

	distrugereSrv(&srvtest);
}

void testModificareChelt() {
	Srv srvtest;
	srvtest = creareSrv();

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 90, 200, "canal") == 0);
	assert(srvtest.listacrt->lg == 3);
	assert(modificareChelt(&srvtest, 90, 200, "canal", 300, "incalzire") == 0);
	assert(modificareChelt(&srvtest, 80, 200, "canal", 300, "incalzire") == 1);
	assert(modificareChelt(&srvtest, 90, 200, "", 300, "") == 1);
	assert(((Cheltuiala*)srvtest.listacrt->element[2])->suma == 300);
	assert(strcmp(((Cheltuiala*)srvtest.listacrt->element[2])->tip, "incalzire") == 0);

	distrugereSrv(&srvtest);
}

void testStergereChelt() {
	Srv srvtest;
	srvtest = creareSrv();

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 90, 200, "canal") == 0);
	assert(srvtest.listacrt->lg == 3);
	assert(stergereChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(srvtest.listacrt->lg == 2);
	assert(stergereChelt(&srvtest, 120, 200, "") == 1);
	assert(stergereChelt(&srvtest, 20, 16, "gaz") == 1);

	distrugereSrv(&srvtest);
}

void testFiltrareCheltApart() {
	Srv srvtest;
	Repo* reztest;
	srvtest = creareSrv();

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 90, 200, "canal") == 0);
	assert(adaugareChelt(&srvtest, 12, 120.10, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 12, 300, "canal") == 0);
	assert(srvtest.listacrt->lg == 5);
	reztest = filtrareCheltApart(srvtest.listacrt, 12, filtrareApartament);
	assert(reztest->lg == 3);

	distrugereLista(reztest);
	distrugereSrv(&srvtest);
}

void testFiltrareCheltSuma() {
	Srv srvtest;
	Repo* reztest;
	srvtest = creareSrv();

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 90, 120.10, "canal") == 0);
	assert(adaugareChelt(&srvtest, 12, 120.10, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 12, 300, "canal") == 0);
	assert(srvtest.listacrt->lg == 5);
	reztest = filtrareCheltSuma(srvtest.listacrt, 120.10, filtrareSuma);
	assert(reztest->lg == 2);

	distrugereLista(reztest);
	distrugereSrv(&srvtest);
}

void testFiltrareCheltTip() {
	Srv srvtest;
	Repo* reztest;
	srvtest = creareSrv();

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 90, 120.10, "canal") == 0);
	assert(adaugareChelt(&srvtest, 12, 120.10, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 12, 300, "canal") == 0);
	assert(srvtest.listacrt->lg == 5);
	
	reztest = filtrareCheltTip(srvtest.listacrt, "gaz", filtrareTip);
	assert(reztest->lg == 2);

	distrugereLista(reztest);
	distrugereSrv(&srvtest);
}

void testSortareCheltSuma() {
	Srv srvtest;
	srvtest = creareSrv();
	Repo* reztestcresc, * reztestdescresc;

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 90, 12, "canal") == 0);
	
	reztestcresc = sortareCheltSuma(srvtest.listacrt, 1, cmpSuma);
	assert(reztestcresc->lg == 3);
	assert(((Cheltuiala*)(reztestcresc->element[0]))->nrapart == 90);
	assert(((Cheltuiala*)(reztestcresc->element[1]))->nrapart == 12);
	assert(((Cheltuiala*)(reztestcresc->element[2]))->nrapart == 120);

	reztestdescresc = sortareCheltSuma(srvtest.listacrt, 0, cmpSuma);
	assert(reztestcresc->lg == 3);
	assert(((Cheltuiala*)(reztestdescresc->element[0]))->nrapart == 120);
	assert(((Cheltuiala*)(reztestdescresc->element[1]))->nrapart == 12);
	assert(((Cheltuiala*)(reztestdescresc->element[2]))->nrapart == 90);
	
	distrugereLista(reztestcresc);
	distrugereLista(reztestdescresc);
	distrugereSrv(&srvtest);
}

void testSortareCheltTip() {
	Srv srvtest;
	srvtest = creareSrv();
	Repo* reztestcresc, * reztestdescresc;

	assert(adaugareChelt(&srvtest, 12, 100, "apa") == 0);
	assert(adaugareChelt(&srvtest, 120, 200, "gaz") == 0);
	assert(adaugareChelt(&srvtest, 90, 12, "canal") == 0);
	
	reztestcresc = sortareCheltTip(srvtest.listacrt, 1, cmpTip);
	assert(reztestcresc->lg == 3);
	assert(((Cheltuiala*)(reztestcresc->element[0]))->nrapart == 12);
	assert(((Cheltuiala*)(reztestcresc->element[1]))->nrapart == 90);
	assert(((Cheltuiala*)(reztestcresc->element[2]))->nrapart == 120);
	
	reztestdescresc = sortareCheltTip(srvtest.listacrt, 0, cmpTip);
	assert(reztestcresc->lg == 3);
	assert(((Cheltuiala*)(reztestdescresc->element[0]))->nrapart == 120);
	assert(((Cheltuiala*)(reztestdescresc->element[1]))->nrapart == 90);
	assert(((Cheltuiala*)(reztestdescresc->element[2]))->nrapart == 12);
	
	distrugereLista(reztestcresc);
	distrugereLista(reztestdescresc);
	distrugereSrv(&srvtest);
}