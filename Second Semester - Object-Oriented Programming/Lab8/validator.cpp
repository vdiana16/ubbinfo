#include "exceptii.h"


void ProdusValidator::validare(const Produs& p) {
	vector<string> mesaje;
	if (p.getPret() <= 0) {
		mesaje.push_back("Pret incorect!\n");
	}
	if (p.getNume().size() == 0) {
		mesaje.push_back("Nume vid!\n");
	}
	if (p.getTip().size() == 0) {
		mesaje.push_back("Tip vid!\n");
	}
	if (p.getProducator().size() == 0) {
		mesaje.push_back("Producator vid!\n");
	}
	if (mesaje.size() > 0) {
		throw ValidException(mesaje);
	}
}