#pragma once
#ifndef FILEREPOSITORY_H
#define FILEREPOSITORY_H
#include "repository.h"
#include "exceptions.h"


class FileRepositoryProdus : public RepoProdus {
private:
	string numefis;
public:
	void loadFromFile();
	void storeToFile();
	void emptyFile();
	FileRepositoryProdus() = default;
	explicit FileRepositoryProdus(const string& nume);

	void setPath(const string& nume) {
		this->numefis = nume;
	}

	void adaugaProdus(const Produs& prod) override {
		RepoProdus::adaugaProdus(prod);
		storeToFile();
	}

	void stergeProdus(const int& id) override {
		RepoProdus::stergeProdus(id);
		storeToFile();
	}

	void modificaProdus(const Produs& prod) override {
		RepoProdus::modificaProdus(prod);
		storeToFile();
	}

	~FileRepositoryProdus() override= default;
};

#endif // !FILEREPOSITORY_H
