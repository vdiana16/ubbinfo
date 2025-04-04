#include "laborator10oop.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include "tests.h"
#include "service.h"
#include "coscump.h"
#include "repository.h"
#include "produsgui.h"
#include "cosgui.h"
#include "filerepository.h"
#include "exceptions.h"

int main(int argc, char *argv[])
{
    Teste teste;
    teste.runTeste();
    FileRepositoryProdus rep("listaproduse.txt");
    ProdusValidator val;
    Cos coscump;
    ServiceProdus srv(rep, val, coscump);
    QApplication a(argc, argv);
    GUI w1(srv,coscump);
    w1.show();
    return a.exec();
}
