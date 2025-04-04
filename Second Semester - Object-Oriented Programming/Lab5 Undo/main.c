#include "UiHeader.h"
#include "testsHeader.h"

int main()
{
    testAll();
    struct UI ui;
    initializeUI(&ui);
    startUI(&ui);
    UICleanup(&ui);
    return 0;
}

    
