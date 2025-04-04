#include <fstream>
#include "filerepository.h"

FileRepositoryProdus::FileRepositoryProdus(const std::string& nume) {
	this->numefis = nume;
	loadFromFile();
}

void FileRepositoryProdus::loadFromFile() {
	std::ifstream file(numefis);
	Produs produs{ };
	while (file >> produs) {
		adaugaProdus(produs);
	}
	file.close();
}

void FileRepositoryProdus::storeToFile() {
	std::ofstream outfile(numefis);
	if (!outfile.is_open()) {
		throw RepoException("Fisierul nu se poate deschide! \n");
	}
	for (const auto& produs : this->getLista()) {
		outfile << produs;
	}
	outfile.close();
}

void FileRepositoryProdus::emptyFile() {
	std::ofstream outfile(numefis);
	outfile << "";
	outfile.close();
}