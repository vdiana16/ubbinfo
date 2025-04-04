#include <iostream>
#include "tests.h"
#include "ui.h"
#define _CRTDBG_MAP_ALLOC

using std::cout;

int main() {
	{

		Teste rteste;
		rteste.runTeste();
		FileRepositoryProdus rep{"listaproduse.txt"};
		//RepoProb rep((float)0.5);
		ProdusValidator val;
		Cos coscump;
		ServiceProdus srv{ rep,val,coscump };
		UI ui{ srv };
		ui.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
