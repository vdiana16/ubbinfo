#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Buget {
public:
    string nume;
    int suma;
    char destinatie; // 'I' pentru investiții, 'C' pentru cheltuieli
    int vechime; // vechimea în luni

    Buget(string nume, int suma, char destinatie, int vechime)
        : nume(nume), suma(suma), destinatie(destinatie), vechime(vechime) {}

    void incrementeazaVarsta() {
        vechime++;
    }

    bool esteMatur() const {
        return (destinatie == 'I' && vechime >= 12);
    }

    bool esteExpirat() const {
        return (destinatie == 'C' && vechime >= 10);
    }
};