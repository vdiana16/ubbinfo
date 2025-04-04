#pragma once
#include "domain.h"
#include "repository.h"
#include "service.h"

/*
Testeaza toata aplicatia
*/
void ruleazaTeste();

/*
* Teste pentru domeniu
*/
void testCreareCheltuiala();

void testDistrugereCheltuiala();

/*
* Teste pentru repository
*/
void testCreareLista();

void testAdugareCheltuiala();

void testVerificareCheltuiala();

void testModificareCheltuiala();

void testCopiereLista();

void testCautareCheltuiala();

void testStergereCheltuiala();

/*
* Teste pentru service
*/

void testAdaugareChelt();

void testModificareChelt();

void testStergereChelt();

void testFiltrareTip();

void testFiltrareApartament();

void testFiltrareSuma();

void testSortareSuma();

void testSortareTip();