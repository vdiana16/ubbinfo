#pragma once
#ifndef TESTS_H
#define TESTS_H

#include "domain.h"
#include "repository.h"
#include "service.h"
#include "exceptions.h"
#include "coscump.h"
#include "filerepository.h"

class Teste {
	// teste domain
	void testCreareProdus();
	void testCopieProdus();
	void testCmp();
	void testOperatori();

	// teste repository
	void testAdaugaProdus();
	void testStergeProdus();
	void testModificaProdus();
	void testCautaProdus();
	void testRepoProb();

	// teste service
	void testAdaugaProd();
	void testStergeProd();
	void testModificaProd();
	void testCautaProd();
	void testGetId();
	void testSortNume();
	void testSortPret();
	void testSortNumeTip();
	void testFiltPretMaiMare();
	void testFiltNume();
	void testFiltProducator();

	// teste cos
	void testCos();
	void testCosService();

	//test raport
	void testGenerareRaport();

	//teste undo
	void testUndo();

	//teste FileRepo
	void testFileRepo();

public:
	Teste() {};
	void runTeste();
	~Teste() {};
};


#endif // !TESTS_H