#include <iostream>
#include <string>
#include <limits>

using std::cout;
using std::cin;
using namespace std;

#include "ui.h"
#include "domain.h"

void UI::curataBuffer()  const{
	if (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void UI::tiparesteListaUI(const vector<Produs>& produse) const{
	if (produse.size() > 0) {
		cout << "-----Produsele sunt:-----\n";
		for (const auto& prod : produse) {
			cout << "Id: " << prod.getId() << "\n" << "Nume: " << prod.getNume() << "\n" << "Tip: " << prod.getTip() << "\n" <<
				"Pret: " << prod.getPret() << "\n" << "Producator: " << prod.getProducator() << "\n";
		}
		cout << "-----Sfarsit lista produse.\n";
	}
	else {
		cout << "Lista vida!\n";
	}
}

void UI::tiparesteUI() const{
	vector<Produs> produse = srv.getListaProd();
	if (produse.size() > 0) {
		cout << "-----Produsele sunt:-----\n";
		for (const auto& prod : produse) {
			cout << "Id: " << prod.getId() << "\n" << "Nume: " << prod.getNume() << "\n" << "Tip: " << prod.getTip() << "\n" <<
				"Pret: " << prod.getPret() << "\n" << "Producator: " << prod.getProducator() << "\n";
		}
		cout << "-----Sfarsit lista produse.\n";
	}
	else {
		cout << "Lista vida!\n";
	}
}

void UI::adaugaUI() const{
	string nume, tip, producator;
	double pret;
	cout << "Dati numele produsului: ";
	cin >> nume;
	cout << "Dati tipul produsului: ";
	cin >> tip;
	cout << "Dati pretul produsului: ";
	cin >> pret;
	curataBuffer();
	cout << "Dati producatorul produsului: ";
	cin >> producator;
	srv.adaugaProd(nume, tip, pret, producator);
	cout << "Adaugat cu succes!\n";
}

void UI::stergeUI() const{
	int id;
	cout << "Dati id-ul produsului cautat: ";
	cin >> id;
	curataBuffer();
	srv.stergeProd(id);
	cout << "Produs sters cu succes!\n";
}

void UI::modificaUI() const{
	int id;
	string nume, tip, producator;
	double pret;
	cout << "Dati id-ul produsului de modificat: ";
	cin >> id;
	curataBuffer();
	cout << "Dati noul nume al produsului: ";
	cin >> nume;
	cout << "Dati noul tip al produsului: ";
	cin >> tip;
	cout << "Dati noul pret al produsului: ";
	cin >> pret;
	curataBuffer();
	cout << "Dati noul producator al produsului: ";
	cin >> producator;
	srv.modificaProd(id, nume, tip, pret, producator);
}

void UI::cautaUI() const{
	int id;
	string nume, tip, producator;
	double pret;
	cout << "Dati id-ul produsului cautat: ";
	cin >> id;
	curataBuffer();
	Produs prod = srv.cautaProd(id);
	cout << "Produsul cautat este: \n";
	cout << "Id: " << prod.getId() << "\n" << "Nume: " << prod.getNume() << "\n" << "Tip: " << prod.getTip() << "\n" <<
		"Pret: " << prod.getPret() << "\n" << "Producator: " << prod.getProducator() << "\n";

}

void UI::sortUI() const{
	int cs;
	cout << "-----Meniu sortare:-----\n";
	cout << "1.dupa nume\n";
	cout << "2.dupa pret\n";
	cout << "3.dupa nume si tip\n";
	cout << "Introduceti comanda: ";
	cin >> cs;
	curataBuffer();
	if (cs == 1) {
		tiparesteListaUI(srv.sortNume());
	}
	else if (cs == 2) {
		tiparesteListaUI(srv.sortPret());
	}
	else if (cs == 3) {
		tiparesteListaUI(srv.sortNumeTip());
	}
	else {
		cout << "Comanda invalida!\n";
	}
}

void UI::filtUI() const{
	int cf;
	string nume, producator;
	double pret;
	cout << "-----Meniu filtrare:-----\n";
	cout << "1.dupa nume\n";
	cout << "2.dupa pret\n";
	cout << "3.dupa producator\n";
	cout << "Introduceti comanda: ";
	cin >> cf;
	curataBuffer();
	if (cf == 1) {
		cout << "\nDati numele dupa care se face filtrarea: ";
		cin >> nume;
		cout << "\n";
		tiparesteListaUI(srv.filtNume(nume));
	}
	else if (cf == 2) {
		cout << "\nDati pretul minim dupa care se face filtrarea: ";
		cin >> pret;
		cout << "\n";
		tiparesteListaUI(srv.filtPretMaiMare(pret));
	}
	else if (cf == 3) {
		cout << "\nDati producatorul dupa care se face filtrarea: ";
		cin >> producator;
		cout << "\n";
		tiparesteListaUI(srv.filtProducator(producator));
	}
	else {
		cout << "Comanda invalida!\n";
	}
}

void UI::generareRapUI() const {
	std::map<std::string, ProdusDTO> raport = srv.generareRaport(srv.getListaProd());
	for (auto it = raport.begin(); it != raport.end(); it++) {
		cout << "Tip: " << it->first << " Numarul de produse: " << it->second.nr << "\n";
	}
}

void UI::cosUI() const{
	cout << "-----Cos de cumparaturi:-----\n";
	Cos c;
	int comc, nr;
	string numecautat, numefis;
	while (true) {
		cout << "Numarul de produse din cosul de cumparaturi: " << srv.getComp().size() << "\n";
		cout << "-----Meniu cos de cumparaturi:-----\n";
		cout << "1.Adauga produs in cos\n";
		cout << "2.Goleste cos\n";
		cout << "3.Genereaza cos\n";
		cout << "4.Export\n";
		cout << "Introduceti comanda: ";
		cin >> comc;
		if (comc == 1) {
			tiparesteUI();
			cout << "Introduceti numele produsului de adaugat: ";
			cin >> numecautat;
			try {
				srv.adaugaProdCos(numecautat);
			}
			catch (RepoException& e) {
				cout << e.getMesaj() << "\n";
			}
				
		}
		else if(comc == 2) {
			srv.golesteCos();
		}
		else if (comc == 3) {
			cout << "Introduceti numarul de produse ce doriti sa le adaugati in cos: ";
			cin >> nr;
			if (nr <= 0) {
				cout << "Numar incorect!\n";
				continue;
			}
			srv.generareCos(nr);
		}
		else if (comc == 4) {
			cout << "Introduceti numele fisierului: ";
			cin >> numefis;
			srv.exportCos(numefis);
		}
		else {
			cout << "Comanda invalida\n!";
			break;
		}
	}
}

void UI::meniu() const{
	cout << "-------------------------------------------------------\n";
	cout << "-----Meniu-----\n";
	cout << "0.Iesire\n";
	cout << "1.Adauga produs\n";
	cout << "2.Sterge produs\n";
	cout << "3.Modifica produs\n";
	cout << "4.Cauta produs\n";
	cout << "5.Sorteaza lista de produse\n";
	cout << "6.Filtreaza lista de produse\n";
	cout << "7.Afiseaza lista de produse\n";
	cout << "8.Cos de cumparaturi:\n";
	cout << "9.Generare raport dupa tip:\n";
	cout << "10.Undo";
	cout << "Introduceti comanda dorita: ";
}

void UI::run() const{
	while (true) {
		meniu();
		int cmd;
		cin >> cmd;
		cout << "---------------------------------------------------\n";
		curataBuffer();
		switch (cmd)
		{
		case 0:
			return;
		case 1:
			try {
				adaugaUI();
			}
			catch (ValidException& e) {
				for (auto i : e.getMesaje()) {
					cout << i << "\n";
				}
			}
			catch (RepoException& e) {
				cout << e.getMesaj();
			}
			break;
		case 2:
			try {
				stergeUI();
			}
			catch (RepoException& e) {
				cout << e.getMesaj();
			}
			break;
		case 3:
			try {
				modificaUI();
			}
			catch (ValidException& e) {
				for (auto i : e.getMesaje()) {
					cout << i << "\n";
				}
			}
			catch (RepoException& e) {
				cout << e.getMesaj();
			}
			break;
		case 4:
			try {
				cautaUI();
			}
			catch (RepoException& e) {
				cout << e.getMesaj();
			}
			break;
		case 5:
			sortUI();
			break;
		case 6:
			filtUI();
			break;
		case 7:
			tiparesteUI();
			break;
		case 8:
			cosUI();
		case 9:
			generareRapUI();
		default:
			cout << "Comanda incorecta!\n";
		}
	}
}