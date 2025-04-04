#include "coscump.h"
#include <random>
#include <fstream>

Cos::Cos() {
    componente.clear();
}

void Cos::adaugaCos(const Produs& p) {
    componente.push_back(p);
}

void Cos::stergeCos() {
    componente.clear();
}

void Cos::adaugaRandom(const vector<Produs>& elemente, const int& n) {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, elemente.size() - 1);
    frecvcomp.assign(elemente.size(), 0);
    for (int i = 0; i < n; i++) {
        int nr = dist(mt);
        int contor = 0;
        while (frecvcomp[nr] >= 2 && contor < 5) {
            int nr = dist(mt);
            contor++;
        }
        if (frecvcomp[nr] < 2) {
            adaugaCos(elemente[nr]);
            frecvcomp[nr]++;
        }
    }
}

void Cos::salveazaFisier(const string& numefis) {
    std::ofstream fout(numefis);
    fout << "<html>" << std::endl;
    fout << "<head><title>Tabel Componente</title></head>" << std::endl;
    fout << "<body>" << std::endl;
    fout << "<table border='1'>" << std::endl;
    fout << "<tr>"
        << "<th>Nr.crt.</th>"
        << "<th>Nume</th>"
        << "<th>Tip</th>"
        << "<th>Pret</th>"
        << "<th>Producator</th>"
        << "</tr>" << std::endl;
    int i = 1;
    for (auto& p : componente) {
        fout << "<tr>"
            << "<td>" << i++ << "</td>"
            << "<td>" << p.getNume() << "</td>"
            << "<td>" << p.getTip() << "</td>"
            << "<td>" << p.getPret() << "</td>"
            << "<td>" << p.getProducator() << "</td>"
            << "</tr>" << std::endl;
    }
    fout << "</table>" << std::endl;
    fout << "</body>" << std::endl;
    fout << "</html>" << std::endl;
}

const vector<Produs>& Cos::getComponente() const noexcept {
    return componente;
}