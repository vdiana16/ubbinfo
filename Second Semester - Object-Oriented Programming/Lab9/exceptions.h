#pragma once
#ifndef EXCEPTIONS
#define EXCEPTIONS


#include "domain.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

//Clasa de exceptii pentru repository

class RepoException {
	string mesaj;
public:
	RepoException(string mesaj) :mesaj{ mesaj } {};
	string getMesaj() const {
		return mesaj;
	}
};

//Clasa de exceptii pentru validator
class ValidException {
	string mesaje;
public:
	ValidException(string mesaje) :mesaje{ mesaje } {}
	string getMesaje() const {
		return mesaje;
	}
};

class ProdusValidator {
public:
	/*
	* Valideaza un produs
	* @param: prod - proodusul care trebuie validat
	* @conditii: id, pret >0
	*			 nume, tip si producator sa nu fie vid
	*/
	void validare(const Produs& p);
};

#endif // !EXCEPTIONS