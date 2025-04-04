#include <stdio.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "teste.h"

/*
7. Administrator imobil

Creati o aplicatie care petmite gestiunea de cheltuieli lunare pentru apartamentele dintr-un bloc.
Fiecare cheltuiala are: numarul apartamentului, suma, tipul (apa, canal, incalzire, gaz).
Aplicatia permite:
a) Adaugarea de cheltuieli pentru un apartament
b) Modificarea unei cheltuieli existente (tipul, suma)
c) Stergere cheltuiala
d) Vizualizare lista de cheltuieli filtrat dupa o proprietate (suma, tipul,apartament)
e) Vizualizare lista de cheltuieli ordonat dupa suma sau tip (crescator/descrescator)
*/

int main()
{
	runTeste();
	run();
	_CrtDumpMemoryLeaks();
}
    
