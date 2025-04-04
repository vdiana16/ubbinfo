#include "TestScurt.h"
#include <assert.h>
#include <exception>
#include "Multime.h"
#include "IteratorMultime.h"

void testAll() { //apelam fiecare functie sa vedem daca exista
	Multime m;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5)==true);
	assert(m.adauga(1)==true);
	assert(m.adauga(10)==true);
	assert(m.adauga(7)==true);
	assert(m.adauga(1)==false);
	assert(m.adauga(10)==false);
	assert(m.adauga(-3)==true);
	assert(m.dim() == 5);
	assert(m.cauta(10) == true);
	assert(m.cauta(16) == false);
	assert(m.sterge(1) == true);
	assert(m.sterge(6) == false);
	assert(m.dim() == 4);


	IteratorMultime im = m.iterator();
	im.prim();
	int s = 0;
	while (im.valid()) {
		TElem e = im.element();
		s += e;
		im.urmator();
	}
	assert(s == 19);

}

void testElimina() {
	Multime m;
	assert(m.vida() == true);
	assert(m.dim() == 0);
	assert(m.adauga(5) == true);
	assert(m.adauga(1) == true);
	assert(m.adauga(10) == true);
	assert(m.adauga(7) == true);
	assert(m.adauga(9) == true);
	assert(m.adauga(19) == true);
	assert(m.adauga(-3) == true);
	assert(m.dim() == 7);
	IteratorMultime im = m.iterator();
	im.prim();
	im.elimina();
	assert(m.dim() == 6);
	im.elimina();
	assert(m.dim() == 5);
	im.elimina();
	assert(m.dim() == 4);
	im.elimina();
	assert(m.dim() == 3);
	im.elimina();
	assert(m.dim() == 2);
	im.elimina();
	assert(m.dim() == 1);
	try {
		im.elimina();
		assert(false);
	}
	catch(const std::exception & e) {
		assert(true);
	}
}
