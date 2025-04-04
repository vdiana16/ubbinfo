#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

//Teta(1)
IteratorMultime::IteratorMultime(Multime& m) : multime(m){
	curent = m.prim;
}

//Teta(1)
void IteratorMultime::prim() {
	curent = multime.prim;
}

//Teta(1)
void IteratorMultime::urmator() {
	if (!valid())
		throw std::exception("Iteratorul nu este valid!");
	curent = multime.urm[curent];
}

//Teta(1)
TElem IteratorMultime::element() const {
	if (!valid())
		throw std::exception("Iteratorul nu este valid!");
	return multime.e[curent];
}

//Teta(1)
bool IteratorMultime::valid() const {
	return curent != -1;
}

////caz favorabil:Teta(1)
// caz mediu:Teta(n)
//caz defavorabil:Teta(n)
//overall:O(n)
TElem IteratorMultime::elimina() {
	TElem e = element();
	urmator();
	if (!valid())
	{
		throw std::exception("Iteratorul nu este valid!");
	}
	multime.sterge(e);
	return e;
}