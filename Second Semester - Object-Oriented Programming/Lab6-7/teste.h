#pragma once
#ifndef TESTE_H
#define TESTE_H

#include "domain.h"
#include "repository.h"
#include "service.h"
#include "exceptii.h"

class Teste {
	// teste domain
	void testCreareProdus();
	void testCopieProdus();
	void testCmp();
	void testEgalitate();

	// teste repository
	void testAdaugaProdus();
	void testStergeProdus();
	void testModificaProdus();
	void testCautaProdus();

	// teste service
	void testAdaugaProd();
	void testStergeProd();
	void testModificaProd();
	void testCautaProd();
	void testSortNume();
	void testSortPret();
	void testSortNumeTip();
	void testFiltPretMaiMare();
	void testFiltNume();
	void testFiltProducator();

public:
	Teste() {};
	void runTeste();
	~Teste() {};
};


#endif // !TESTE_H