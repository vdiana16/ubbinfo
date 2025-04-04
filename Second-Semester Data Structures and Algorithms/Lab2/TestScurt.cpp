#include <assert.h>
#include <exception>
#include "Iterator.h"
#include "LO.h"

using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	LO lo = LO(relatie1);
	assert(lo.dim() == 0);
	assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator iterator = lo.iterator();
    assert(iterator.valid());
    iterator.prim();
    assert(iterator.element() == 1);
    iterator.urmator();
    assert(!iterator.valid());
    iterator.prim();
    assert(iterator.valid());
    assert(lo.cauta(1) == 0);
    assert(lo.sterge(0) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());
}



void testStergeintre() {
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    try {
        lo.stergeintre(1, 2);
        assert(false);
    }
    catch (exception& e) {
        assert(true);
    }
    lo.adauga(1);
    lo.adauga(5);
    lo.adauga(2);
    lo.adauga(5);
    lo.adauga(9);
    assert(lo.dim() == 5);
    try {
        lo.stergeintre(5, 1);
        assert(false);
    }
    catch (exception& e) {
        assert(true);
    }
    try {
        lo.stergeintre(10, 0);
        assert(false);
    }
    catch (exception& e) {
        assert(true);
    }
    lo.stergeintre(1, 3);
    assert(lo.dim() == 2);
    lo.stergeintre(1, 1);
    assert(lo.dim() == 1);
}