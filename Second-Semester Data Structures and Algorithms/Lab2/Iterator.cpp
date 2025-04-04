#include "Iterator.h"
#include "LO.h"
#include <exception>

using namespace std;

//Teta(1)
Iterator::Iterator(const LO& lo) : lista(lo){
	this->curent = lista.prim;
}

//Teta(1)
void Iterator::prim() {
	this->curent = lista.prim;
}

//Teta(1)
void Iterator::urmator(){
	if (!valid()) {
		throw exception();
	}
	this->curent = this->curent->urmator();
}

//Teta(1)
bool Iterator::valid() const{
	if (this->curent == nullptr) {
		return false;
	}
	return true;
}

//Teta(1)
TElement Iterator::element() const{
	if (!valid()) {
		throw exception();
	}
	return this->curent->element();
}


