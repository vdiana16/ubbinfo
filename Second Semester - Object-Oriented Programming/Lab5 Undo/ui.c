#include <stdio.h>
#include <string.h>
#include "domainHeader.h"
#include "serviceOfertaHeader.h"
#include "UiHeader.h"

/*
 * Functie pentru afisarea meniului principal
 * Preconditii: None
 * Postconditii: None
 */
void displayMenu()
{
    printf("\n\n----------------------\n");
    printf("Alegeti tasta:\n0.Oprire aplicatie\n1.Adauga\n2.Acutalizare Oferta\n3.Sterge oferta\n4.Vizualizare sortata\n5.Afisare filtrate\n");
    printf("\n----------------------\n");
}

/*
 * A function that returns the menu option chosen by the user if the command is valid, -1 otherwise
 * Preconditions: None
 * Postconditions: user choise if valid, -1 otherwise
 */
int readUserInput()
{
    int userInput;
    printf("Introduceti tasta dorita: ");
    scanf("%d", &userInput);
    if(userInput < 0 || userInput > 5)
        return -1;
    return userInput;
}

/*
 * A functin that returns a const char* containing the type read if the user input is valid, NULL otherwise
 * Preconditions: None
 * Postconditions: return is Null if the value entered by the user is invalid, const char* that contains the required value
 */
const char *citireTip()
{
    getchar();
    char tip[15];
    printf("Alegeti tipul(munte,mare, city break): ");
    char *p;
    p = fgets(tip, 14, stdin);
    char *newline = strchr(tip, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
    if( p == NULL)
        return NULL;
    if(strcmp("mare", tip) == 0)
        return "mare";
    else if(strcmp("munte", tip) == 0)
        return "munte";
    else if(strcmp("city break", tip) == 0)
        return "city break";
    return NULL;
}

/*
 * A function that reads a date from the console
 */
struct Data citireData()
{
    struct Data dataPlecare;
    printf("Introduceti ziua: ");
    scanf("%d", &dataPlecare.zi);
    printf("Introduceti luna: ");
    scanf("%d", &dataPlecare.luna);
    printf("Introduceti anul: ");
    scanf("%d", &dataPlecare.an);
    return dataPlecare;
}


/*
 * A function that handles the Ui menu for adding an offer
 */
struct Oferta *addUI()
{
    const char *tipDorit = citireTip();
    char destinatie[25];
    int pret;
    struct Data dataPlecare;
    if(tipDorit != NULL)
    {
        printf("Introduceti destinatia: ");
        char *valid = fgets(destinatie, 24, stdin);
        char *newline = strchr(destinatie, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        if(valid == NULL)
        {
            printf("S-a intampinat o problema la citire");
            return createInvalidOffer();
        }
        else
        {
            dataPlecare = citireData();
            printf("Introduceti pretul: ");
            scanf("%d", &pret);
            return createOffer(pret, dataPlecare, destinatie, tipDorit);

        }
    }
    else
    {
        printf("Tipul introus este invalid\n");
        return createInvalidOffer();
    }

}

/*
 * A Function that displays an offer
 */
void afiseazaOferta(struct Oferta oferta)
{
    printf("\nID: %d\ntip: %s\ndestinatie: %s\npret: %d\ndata: %d/%d/%d\n", oferta.id, oferta.tip, oferta.destinatie, oferta.pret, oferta.dataPlecare.zi, oferta.dataPlecare.luna, oferta.dataPlecare.an);
}

void displayCurrentOffers(struct Service *srv)
{
    printf("\n----------------------\n");
    printf("----------------------");
    printf("\nCurrent offers:\n\n");
    for(int i = 0; i < srv->repo.listaOferte.nrOfElements; i++)
    {
        afiseazaOferta(*(srv->repo.listaOferte.array[i]));
        if(i <  srv->repo.listaOferte.nrOfElements-1)
            printf("\n----------------------\n");
    }
    printf("----------------------");
    printf("\n----------------------\n");

}

/*
 * A function that displays a list of offers
 */

void displayOfferList(struct Oferta** offerList, int nrOfElements)
{
    //NU UITA BAI PULA
    for(int i = 0; i < nrOfElements; i++)
    {
        afiseazaOferta(*(offerList[i]));
    }
}

/*
 * A function that displays the modificaion UI
 */
void actualizeaza(struct Service *srv)
{
    int idToModify, fieldToModify;
    displayCurrentOffers(srv);
    printf("\n\nAlegeti IDul ofertei pe care doriti sa o modificati: ");
    scanf("%d", &idToModify);
    printf("Choose what to modify: \n1.Modify type\n2.Modify price\n3.Modify date\n4.Modify destination\n");
    fieldToModify = readUserInput();
    if(fieldToModify == 1)
    {
            const char *newType = citireTip();
            if (newType == NULL)
            {
                printf("Specified type is not valid");
                return;
            }
            int returnCode = modifyType(srv, newType, idToModify);
            if(returnCode == 0)
                printf("Id-ul nu exista, nu s-a efectuat modificarea");
    }
    else if(fieldToModify == 2)
    {
        printf("Enter new price: ");
        int newPrice;
        scanf("%d", &newPrice);
        int returnCode = modifyPrice(srv, newPrice, idToModify);
        if(returnCode == 0)
            printf("Id-ul nu exista, nu s-a efectuat modificarea");
    }
    else if(fieldToModify == 4)
    {
        char newValue[25];
        printf("Enter the new destination: ");
        getchar();
        fgets(newValue, 24, stdin);
        char *newline = strchr(newValue, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        int returnCode = modifyDestination(srv, newValue, idToModify);
        if(returnCode == 0)
            printf("Id-ul nu exista, nu s-a efectuat modificarea");
    }
    else if(fieldToModify == 3)
    {
        struct Data dataNoua = citireData();
        int returnCode = modifyDate(srv, dataNoua, idToModify);
        if(returnCode == 0)
            printf("Id-ul nu exista, nu s-a efectuat modificarea");
    }
    displayCurrentOffers(srv);
}

/*
 * A function that displays the deletion UI
 */
void delete(struct Service *srv)
{
    int idToDelete;
    displayCurrentOffers(srv);
    printf("\n\nAlegeti IDul ofertei pe care doriti sa o stergeti: ");
    scanf("%d", &idToDelete);
    int responseCode = deleteOffer(srv, idToDelete);
    if(responseCode == 0)
        printf("Id-ul introdus este invalid");
    displayCurrentOffers(srv);
}


/*
 * A function that starts the UI menu for displaying the sorted list of offers
 */
void displaySorted(struct Service *srv)
{
    struct ListForDisplay sortedList = serviceSortList(srv, compare);
    displayOfferList(sortedList.listaOferte, sortedList.nrOfElements);
    freeListForDisplay(&sortedList);
}


/*
 * A function that starts the UI menu for filtering the offers
 */
void filter(struct Service *srv)
{
    int tipFiltru;
    printf("Alegeti tipul de filtru:\n1.Destinatie\n2.Tip\n3.Pret\n->");
    scanf("%d", &tipFiltru);
    if(tipFiltru < 1 || tipFiltru > 3)
        printf("Optiunea aleasa este invalida");
    if(tipFiltru == 1)
    {
        char filterDestination[25];
        printf("Ce destinatie doriti sa vedeti: ");
        getchar();
        fgets(filterDestination, 24, stdin);
        char *newline = strchr(filterDestination, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        struct ListForDisplay filteredList =  serviceFilterByDestination(srv, filterDestination);
        displayOfferList(filteredList.listaOferte, filteredList.nrOfElements);
        freeListForDisplay(&filteredList);
    }
    else if(tipFiltru == 2)
    {
        const char *tip = citireTip();
        struct ListForDisplay filteredList =  serviceFilterByType(srv, tip);
        displayOfferList(filteredList.listaOferte, filteredList.nrOfElements);
        freeListForDisplay(&filteredList);
    }
    else if(tipFiltru == 3)
    {
        int filterPrice;
        printf("Vizualizati Ofertele cu pretul mai mic sau egal cu: ");
        scanf("%d", &filterPrice);
        struct ListForDisplay filteredList = serviceFilterByPrice(srv, filterPrice);
        displayOfferList(filteredList.listaOferte, filteredList.nrOfElements);
        freeListForDisplay(&filteredList);
    }
}


/*
 * A function that handles the redirection of the UI according to the input given by the user
 */
void taskHandler(struct Service *srv, int currentKey)
{

    if (currentKey == 1)
    {
        struct Oferta *offer = addUI();
        addOfertaService(srv, offer);
        displayCurrentOffers(srv);
    }
    else if (currentKey == 2)
    {
        actualizeaza(srv);
    }
    else if(currentKey == 3)
    {
        delete(srv);
    }
    else if(currentKey == 4)
    {
        displaySorted(srv);
    }
    else if(currentKey == 5)
    {
        filter(srv);
    }
}

/*
 * The function that starts the UI
 */
void startUI(struct UI *ui)
{
    int currentKey = -1;
    while (currentKey != 0)
    {
        displayMenu();
        currentKey = readUserInput();
        if(currentKey == -1)
            printf("Tasta introdusa este invalida\n");
        else
            taskHandler(&(ui->srv), currentKey);
    }
}


void initializeUI(struct UI *ui)
{
    initializeService(&( ui->srv ));
}

void UICleanup(struct UI *ui)
{
    destroyService(&(ui->srv));
}