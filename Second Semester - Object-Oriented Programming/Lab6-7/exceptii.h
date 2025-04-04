#pragma once
#ifndef EXCEPTII_H
#define EXCEPTII_H

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
	string getMesaj() {
		return mesaj;
	}
};

//Clasa de exceptii pentru validator
class ValidException {
	vector<string> mesaje;
public:
	ValidException(const vector<string>& mesaje) :mesaje{ mesaje } {}
	vector<string> getMesaje() {
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

#endif // !EXCEPTII_H
