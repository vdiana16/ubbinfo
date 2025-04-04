#include "exceptions.h"


void ProdusValidator::validare(const Produs& p) {
	string mesaje;
	if (p.getPret() <= 0) {
		mesaje.append("Pret incorect!\n");
	}
	if (p.getNume().size() == 0) {
		mesaje.append("Nume vid!\n");
	}
	if (p.getTip().size() == 0) {
		mesaje.append("Tip vid!\n");
	}
	if (p.getProducator().size() == 0) {
		mesaje.append("Producator vid!\n");
	}
	if (mesaje.size() > 0) {
		throw ValidException(mesaje);
	}
}