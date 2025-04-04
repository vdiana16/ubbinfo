#include "tests.h"
#include <iostream>
#include <assert.h>
#include <cstdbool>
#include <sstream>
#include <fstream>

void Teste::runTeste() {
	testCreareProdus();
	testCopieProdus();
	testCmp();
	testOperatori();

	testAdaugaProdus();
	testStergeProdus();
	testModificaProdus();
	testCautaProdus();
	testRepoProb();

	testAdaugaProd();
	testStergeProd();
	testCautaProd();
	testModificaProd();
	testGetId();
	testSortNume();
	testSortPret();
	testSortNumeTip();
	//testFiltPretMaiMare();
	testFiltNume();
	testFiltProducator();

	testCos();
	testCosService();

	testGenerareRaport();

	testUndo();

	testFileRepo();
}

void Teste::testCreareProdus() {
	Produs p = { 1,"Lapte","A",10,"Zuzu" };

	assert(p.getId() == 1);
	assert(p.getNume() == "Lapte");
	assert(p.getTip() == "A");
	assert(p.getPret() == 10);
	assert(p.getProducator() == "Zuzu");

	p.setId(2);
	assert(p.getId() == 2);
	p.setNume("Iaurt");
	assert(p.getNume() == "Iaurt");
	p.setTip("B");
	assert(p.getTip() == "B");
	p.setPret(20);
	assert(p.getPret() == 20);
	p.setProducator("Danone");
	assert(p.getProducator() == "Danone");
}

void Teste::testCopieProdus() {
	Produs p1 = { 1,"Lapte","A",10,"Zuzu" };
	Produs p2 = { p1 };

	assert(p1.getId() == p2.getId());
	assert(p1.getNume() == p2.getNume());
	assert(p1.getTip() == p2.getTip());
	assert(p1.getPret() == p2.getPret());
	assert(p1.getProducator() == p2.getProducator());
}

void Teste::testCmp() {
	Produs p1 = { 1,"Lapte","A",10,"Zuzu" };
	Produs p2 = { 2,"Iaurt","C",15,"Danone" };

	assert(cmpNume(p1, p2) == false);
	assert(cmpPret(p1, p2) == true);
	assert(cmpNume(p2, p1) == true);
	assert(cmpPret(p2, p1) == false);
	assert(cmpTip(p1, p2) == true);
	assert(cmpTip(p2, p1) == false);
}

void Teste::testOperatori() {
	Produs p1 = { 1,"Lapte","A",10,"Zuzu" };
	Produs p2 = { 2,"Lapte","A",10,"Zuzu" };
	Produs p3 = { 3,"Iaurt","C",15,"Danone" };

	assert(p1 == p2);
	assert(p1 != p3);

	Produs p4{};
	std::istringstream input("1,Lapte,A,10,Zuzu");
	input >> p4;
	assert(p4.getId() == 1);
	assert(p4.getNume() == "Lapte");
	assert(p4.getTip() == "A");
	assert(p4.getPret() == 10);
	assert(p4.getProducator() == "Zuzu");
	std::istringstream inp("1,Lapte,A,10");
	Produs p5{};
	inp >> p5; assert(p4.getId() == 1);
	assert(p4.getNume() == "Lapte");
	assert(p4.getTip() == "A");
	assert(p4.getPret() == 10);

	std::ostringstream output;
	output << p4;
	string outp = output.str();
	assert(outp == "1,Lapte,A,10,Zuzu\n");
}

void Teste::testAdaugaProdus() {
	RepoProdus rep;

	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);
	try {
		rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "Exista deja acest produs!\n");
	}
}

void Teste::testStergeProdus() {
	RepoProdus rep;

	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);
	rep.stergeProdus(1);
	assert(rep.getLista().size() == 2);

	try {
		rep.stergeProdus(0);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}
}

void Teste::testModificaProdus() {
	RepoProdus rep;
	int pozitie;

	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);

	rep.modificaProdus(Produs{ 1,"Oua","A",20,"LaBunica" });
	pozitie = rep.cautaId(1);
	auto lista = rep.getLista();
	assert(lista[pozitie].getNume() == "Oua");

	try {
		rep.modificaProdus(Produs{ 6,"Oua","A",20,"LaBunica" });
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}
}

void Teste::testCautaProdus() {
	RepoProdus rep;
	Produs pgasit, pcautat;

	rep.adaugaProdus(Produs{ 1,"Lapte","A",10,"Zuzu" });
	rep.adaugaProdus(Produs{ 2,"Iaurt","B",15,"Danone" });
	rep.adaugaProdus(Produs{ 3,"Unt","C",20,"Napolact" });

	assert(rep.getLista().size() == 3);

	pcautat = Produs{ 2,"Iaurt","B",15,"Danone" };
	pgasit = rep.cautaProdus(2);
	assert(pgasit == pcautat);

	assert(rep.cautaProdusNume("Iaurt") == 2);
	assert(rep.cautaProdusNume("Ulei") == -1);

}

void Teste::testAdaugaProd() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);
	rep.emptyFile();
	assert(srv.getListaProd().size() == 0);
	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	assert(srv.getListaProd().size() == 1);

	auto lista = srv.getListaProd();

	assert(lista[0].getId() == 1);
	assert(lista[0].getNume() == "Oua");
	assert(lista[0].getTip() == "B");
	assert(lista[0].getPret() == 15);
	assert(lista[0].getProducator() == "LaBunica");

	try {
		srv.adaugaProd("Oua", "B", 15, "LaBunica");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "Exista deja acest produs!\n");
	}

	try {
		srv.adaugaProd("", "", 0, "");
		assert(false);
	}
	catch (const ValidException& e) {
		assert(e.getMesaje() == "Pret incorect!\nNume vid!\nTip vid!\nProducator vid!\n");
	}
	rep.emptyFile();


}


void Teste::testStergeProd() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
	srv.adaugaProd("Unt", "C", 7.15, "Napolact");

	assert(srv.getListaProd().size() == 4);

	srv.stergeProd(3);
	assert(srv.getListaProd().size() == 3);

	auto lista = srv.getListaProd();
	assert(lista[0].getNume() == "Oua");
	assert(lista[1].getNume() == "Lapte");
	assert(lista[2].getNume() == "Unt");

	srv.stergeProd(2);
	auto lista2 = srv.getListaProd();
	assert(srv.getListaProd().size() == 2);
	assert(lista2[0].getNume() == "Oua");
	assert(lista2[1].getNume() == "Unt");

	try {
		srv.stergeProd(10);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}
	rep.emptyFile();
}

void Teste::testModificaProd() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");

	assert(srv.getListaProd().size() == 3);

	srv.modificaProd(1, "Ulei", "C", 20, "Spornic");

	auto lista = srv.getListaProd();
	assert(lista[0].getId() == 1);
	assert(lista[0].getNume() == "Ulei");
	assert(lista[0].getTip() == "C");
	assert(lista[0].getPret() == 20);
	assert(lista[0].getProducator() == "Spornic");

	try {
		srv.modificaProd(1, "", "", 0, "");
		assert(false);
	}
	catch (const ValidException& e) {
		assert(e.getMesaje() == "Pret incorect!\nNume vid!\nTip vid!\nProducator vid!\n");
	}

	try {
		srv.modificaProd(5, "Oua", "A", 20, "LaBunica");
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}
	rep.emptyFile();
}

void Teste::testCautaProd() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");

	assert(srv.getListaProd().size() == 3);

	auto prodcautat = srv.cautaProd(2);

	assert(prodcautat.getNume() == "Lapte");
	assert(prodcautat.getTip() == "A");
	assert(prodcautat.getPret() == 20);
	assert(prodcautat.getProducator() == "Zuzu");

	auto poz = srv.cautaProdN("Lapte");
	assert(poz == 2);
	assert(srv.cautaProdN("L") == -1);

	try {
		srv.cautaProd(20);
		assert(false);
	}
	catch (const RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}
	rep.emptyFile();
}

void Teste::testGetId() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");

	assert(srv.getId() == 4);
	rep.emptyFile();
}

void Teste::testSortNume() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 15, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
	srv.adaugaProd("Ulei", "D", 15, "Spornic");
	srv.adaugaProd("Faina", "C", 6, "Dobrogea");

	assert(srv.getListaProd().size() == 5);

	auto lsort = srv.sortNume();
	assert(lsort[0].getNume() == "Faina");
	assert(lsort[1].getNume() == "Kinder Bueno");
	assert(lsort[2].getNume() == "Lapte");
	assert(lsort[3].getNume() == "Oua");
	assert(lsort[4].getNume() == "Ulei");

	rep.emptyFile();
}

void Teste::testSortPret() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Lapte", "A", 20, "Zuzu");
	srv.adaugaProd("Kinder Bueno", "C", 30, "Kinder");
	srv.adaugaProd("Ulei", "D", 15, "Spornic");
	srv.adaugaProd("Faina", "C", 6, "Dobrogea");

	assert(srv.getListaProd().size() == 5);

	auto lsort = srv.sortPret();
	assert(lsort[0].getNume() == "Faina");
	assert(lsort[1].getNume() == "Oua");
	assert(lsort[2].getNume() == "Ulei");
	assert(lsort[3].getNume() == "Lapte");
	assert(lsort[4].getNume() == "Kinder Bueno");

	rep.emptyFile();
}

void Teste::testSortNumeTip() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 15, "Pambac");
	srv.adaugaProd("Faina", "C", 6, "Dobrogea");

	assert(srv.getListaProd().size() == 5);
	auto lsort = srv.sortNumeTip();
	assert(lsort[0].getId() == 2);
	assert(lsort[1].getId() == 5);
	assert(lsort[2].getId() == 4);
	assert(lsort[3].getId() == 1);
	assert(lsort[4].getId() == 3);

	rep.emptyFile();

}

/*void Teste::testFiltPretMaiMare() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 6, "Pambac");
	srv.adaugaProd("Faina", "C", 15, "Dobrogea");

	assert(srv.getListaProd().size() == 5);

	auto lfilt = srv.filtPretMaiMare(14);
	assert(lfilt[0].getId() == 2);
	assert(lfilt[1].getId() == 3);
	assert(lfilt[2].getId() == 5);

	rep.emptyFile();
}
*/
void Teste::testFiltNume() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Faina", "C", 15, "Dobrogea");
	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "Rasfatul bunicii");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 6, "Pambac");

	assert(srv.getListaProd().size() == 5);

	auto lfilt = srv.filtNume("Faina");
	assert(lfilt[0].getId() == 1);
	assert(lfilt[1].getId() == 3);
	assert(lfilt[2].getId() == 5);

	rep.emptyFile();
}

void Teste::testFiltProducator() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Faina", "C", 15, "Dobrogea");
	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "LaBunica");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "D", 6, "Pambac");

	assert(srv.getListaProd().size() == 5);

	auto lfilt = srv.filtProducator("LaBunica");
	assert(lfilt[0].getId() == 2);
	assert(lfilt[1].getId() == 3);
	assert(lfilt[2].getId() == 4);

	rep.emptyFile();
}

void Teste::testCos() {
	Cos c;
	auto p = Produs{ 1,"Lapte","A",10,"Zuzu" };

	c.adaugaCos(p);
	vector<Produs> testrez;
	testrez = c.getComponente();
	assert(testrez[0].getId() == 1);
	assert(testrez[0].getNume() == "Lapte");
	assert(testrez[0].getTip() == "A");
	assert(testrez[0].getPret() == 10);
	assert(testrez[0].getProducator() == "Zuzu");

	c.adaugaCos(p);
	testrez = c.getComponente();
	assert(testrez.size() == 2);

	c.stergeCos();
	testrez = c.getComponente();
	assert(testrez.empty());

	vector<Produs> testp;
	testp.emplace_back(Produs{ 1,"Lapte","A",10,"Danone" });
	testp.emplace_back(Produs{ 2, "Kinder Bueno", "C", 7.15, "Kinder" });
	testp.emplace_back(Produs{ 3,"Unt","C",20,"Napolact" });

	c.adaugaRandom(testp, 2);
	assert(c.getComponente().size() == 2);

	c.salveazaFisier("testf.html");

	Cos c1;
	vector<Produs> testp2;
	testp2.emplace_back(Produs{ 1,"Lapte","A",10,"Danone" });
	c1.adaugaRandom(testp2, 3);
	assert(c1.getComponente().size() == 2);
}

void Teste::testGenerareRaport() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Faina", "C", 15, "Dobrogea");
	srv.adaugaProd("Oua", "B", 12, "LaBunica");
	srv.adaugaProd("Faina", "A", 20, "LaBunica");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "B", 6, "Pambac");

	assert(srv.getListaProd().size() == 5);
	std::map<std::string, ProdusDTO> rapt = srv.generareRaport(rep.getLista());
	assert(rapt.size() == 3);

	assert(rapt["A"].nr == 1);
	assert(rapt["B"].nr == 2);
	assert(rapt["C"].nr == 2);
	assert(rapt.find("D") == rapt.end());
	rep.emptyFile();
}

void Teste::testCosService() {
	FileRepositoryProdus rep{ "../testsrv.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Lapte", "B", 15, "LaDorna");
	srv.adaugaProdCos("Lapte");
	vector<Produs> testrez;
	testrez = srv.getComp();
	assert(testrez[0].getId() == 1);
	assert(testrez[0].getNume() == "Lapte");
	assert(testrez[0].getTip() == "B");
	assert(testrez[0].getPret() == 15);
	assert(testrez[0].getProducator() == "LaDorna");

	srv.adaugaProdCos("Lapte");
	testrez = srv.getComp();
	assert(testrez.size() == 2);

	srv.golesteCos();
	testrez = srv.getComp();
	assert(testrez.empty());

	vector<Produs> testp;
	srv.adaugaProd("Iaurt", "A", 10, "Danone");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
	srv.adaugaProd("Unt", "C", 20, "Napolact");

	srv.generareCos(2);
	assert(srv.getComp().size() == 2);

	srv.exportCos("testf.html");
	rep.emptyFile();
}

void Teste::testUndo() {
	std::ofstream f("../testsrv2.txt");
	f << "";
	f.close();
	FileRepositoryProdus rep{ "../testsrv2.txt" };
	rep.emptyFile();
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv(rep, val, coscump);

	srv.adaugaProd("Iaurt", "A", 10, "Danone");
	srv.adaugaProd("Kinder Bueno", "C", 7.15, "Kinder");
	srv.adaugaProd("Unt", "C", 20, "Napolact");
	srv.adaugaProd("Oua", "C", 30, "LaBunica");
	srv.adaugaProd("Faina", "B", 6, "Pambac");

	srv.undo();
	try {
		srv.cautaProd(5);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}
	srv.stergeProd(3);
	try {
		srv.cautaProd(3);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}

	srv.undo();
	assert(srv.cautaProd(3).getNume() == "Unt");

	srv.modificaProd(1, "Paste", "A", 30, "Barilla");
	srv.stergeProd(1);
	srv.adaugaProd("Gris", "C", 11, "Pambac");
	assert(srv.getListaProd().size() == 4);

	srv.undo();
	assert(srv.getListaProd().size() == 3);
	try {
		srv.cautaProd(1);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMesaj() == "Nu exista acest produs!\n");
	}
	srv.undo();
	assert(srv.cautaProd(1).getNume() == "Paste");
	srv.undo();
	assert(srv.cautaProd(1).getNume() == "Iaurt");
	srv.undo();
	srv.undo();
	srv.undo();
	srv.undo();
	try {
		srv.undo();
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.getMesaj() == "Nu se mai poate face undo!\n");
	}

	rep.emptyFile();
}

void Teste::testFileRepo() {
	FileRepositoryProdus filerepo{ "../test.txt" };
	filerepo.emptyFile();

	Produs test1{ 1,"A","B",10,"C" };
	try
	{
		filerepo.adaugaProdus(test1);
	}
	catch (RepoException& e) {}
	assert(filerepo.getLista().size() == 1);
	filerepo.storeToFile();
	assert(filerepo.cautaProdusNume("A") != -1);
	assert(filerepo.getLista()[0].getTip() == "B");
	assert(filerepo.getLista()[0].getNume() == "A");
	assert(filerepo.getLista()[0].getPret() == 10);
	assert(filerepo.getLista()[0].getProducator() == "C");

	try
	{
		FileRepositoryProdus repf{ "dir/h.txt" };
		repf.storeToFile();
		assert(false);
	}
	catch (RepoException& m)
	{
		assert(m.getMesaj() == "Fisierul nu se poate deschide! \n");
	}

}

void Teste::testRepoProb() {
	Produs p1{ 1,"Lapte","A",10,"Zuzu" };
	auto rep1 = RepoProb(1);
	rep1.adaugaProdus(p1);
	const auto& listat = rep1.getLista();
	assert(listat.size() == 1);
	assert(listat[0].getId() == 1);
	assert(listat[0].getNume() == "Lapte");
	assert(listat[0].getTip() == "A");
	assert(listat[0].getProducator() == "Zuzu");
	assert(listat[0].getPret() == 10);

	Produs p2 = { 1,"Iaurt","C",15,"Danone" };
	rep1.modificaProdus(p2);
	const auto& listat2 = rep1.getLista();
	assert(listat2.size() == 1);
	assert(listat2[0].getId() == 1);
	assert(listat2[0].getNume() == "Iaurt");
	assert(listat2[0].getTip() == "C");
	assert(listat2[0].getProducator() == "Danone");
	assert(listat2[0].getPret() == 15);

	auto poz = rep1.cautaId(1);
	assert(poz == 0);

	auto poz2 = rep1.cautaId(55);
	assert(poz2 == -1);

	poz2 = rep1.cautaProdusNume("Iaurt");
	assert(poz2 == 0);

	auto prod = rep1.cautaProdus(1);
	assert(prod.getId() == 1);

	try {
		auto prod1 = rep1.cautaProdus(10);
		assert(false);
	}
	catch (RepoException msg) {
		assert(true);
	}


	poz = rep1.cautaProdusNume("Lapte");
	assert(poz == -1);

	Produs p4{ 2,"Iaurt","B",11,"Danone" };
	rep1.adaugaProdus(p4);
	rep1.stergeProdus(1);
	const auto& listat3 = rep1.getLista();
	assert(listat3.size() == 1);
	assert(listat3[0].getId() == 2);

	rep1 = RepoProb((int)0);
	try {
		rep1.adaugaProdus(p1);
		assert(false);
	}
	catch (RepoException msg) {
		assert(true);
	}

}