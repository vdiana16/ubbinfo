#include <iostream>
#include "teste.h"
#include "ui.h"

using std::cout;

int main() {
	Teste rteste;
	rteste.runTeste();
	RepoProdus rep;
	ProdusValidator val;
	Cos coscump;
	ServiceProdus srv{ rep,val,coscump };
	UI ui{ srv };
	ui.run();
	return 0;
}
