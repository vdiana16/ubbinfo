#include <iostream>
#include "teste.h"
#include "ui.h"

using std::cout;

int main() {
	Teste rteste;
	rteste.runTeste();
	RepoProdus rep;
	ProdusValidator val;
	ServiceProdus srv{ rep,val };
	UI ui{ srv };
	ui.run();
	
	return 0;
}
