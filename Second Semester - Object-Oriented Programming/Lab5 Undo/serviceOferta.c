//
// Created by danpe on 3/9/2024.
//
#include "serviceOfertaHeader.h"
#include <string.h>
#include "repoOfertaHeader.h"
#include "domainHeader.h"
#include "UiHeader.h"
#include <assert.h>
#include <stdlib.h>


/*
 * A method that validates the offer(the type of the offer is not "invalid") and adds it to the repository
 * Preconditions: srv->pointer to a service struct, offerToAdd-> an offer
 * Postcondition: the offer will be added to the repository associated to the service
 */
int addOfertaService(struct Service *srv, struct Oferta *offerToAdd)
{
    if(strcmp(offerToAdd->tip, "invalid") == 0)
    {
        destroyOffer(&offerToAdd);
        return -1;
    }
    add(&(srv->repo), offerToAdd);
    return 1;
}

/*
 * A function that modifies the price of the object with the specified id if the object exists, returns 0 otherwise
 * Preconditions: srv-> a service pointer, newPrice->the new price, idToModify-> the id of the offer to be modified
 * Postcondition: the price of the offer with the specified id will be equal to newPrice
 */
int modifyPrice(struct Service *srv, int newPrice, int idToModify)
{
    int returnCode = repoModifyPrice(&(srv->repo), newPrice, idToModify);
    if(returnCode == 0)
        return 0;
    return 1;
}

/*
 * A function that modifies the type of the object with the specified id if the object exists, returns 0 oterwise
 * Preconditions: srv-> a service pointer, newPrice->the new type, idToModify-> the id of the offer to be modified
 * Postcondition: the type of the offer with the specified id will be equal to newType
 */
int modifyType(struct Service *srv,const char* newValue, int idToModify)
{
    int returnCode = repoModifyType(&(srv->repo), newValue, idToModify);
    if (returnCode == 0)
        return 0;
    return 1;
}

/*
 * A function that modifies the date of the object with the specified id if the object exists, returns 0 otherwise
 * Preconditions: srv-> a service pointer, newDate->the new date, idToModify-> the id of the offer to be modified
 * Postcondition: the date of the offer with the specified id will be equal to newDate
 */
int modifyDate(struct Service *srv, struct Data newDate, int idToModify)
{
    int returnCode = repoModifyDate(&(srv->repo), newDate, idToModify);
    if(returnCode == 0)
        return 0;
    return 1;
}

/*
 * A function that modifies the destination of the object with the specified id if the object exists, returns 0 otherwise
 * Preconditions: srv-> a service pointer, newDestination->the new destination, idToModify-> the id of the offer to be modified
 * Postcondition: the destination of the offer with the specified id will be equal to newDestination
 */
int modifyDestination(struct Service *srv, char* newDestination, int idToModify)
{
    int returnCode = repoModifyDestination(&(srv->repo), newDestination, idToModify);
    if(returnCode == 0)
        return 0;
    return 1;
}

/*
 * A funtion that removes the offer with the specified id if the object exists, returns 0 otherwse
 * Precondition: srv->pointer to a service struct, idToDelete->id of the offer that will be deleted
 * Post condition: the offer with the id=idToDelete will be removed from the repository
 */
int deleteOffer(struct Service *srv, int idToDelete)
{
    int returnCode = repoDeleteOffer(&(srv->repo), idToDelete);
    if(returnCode == 0)
        return 0;
    return 1;
}

/*
 * A function that copies the elements of the list listaOriginala into listaCopie
 * Preconditions: listaCopie->oferta* listaOriginala->oferta*\
 * Postcondition: listaCopie will contain offers with the same values as the listaOriginala
 */
void creeazaCopieListaOferte(struct Oferta *    *listaCopie, struct Oferta **listaOriginala, int nrOfElements)
{
    for(int i = 0;  i < nrOfElements; i++)
    {
        listaCopie[i] = listaOriginala[i];
    }
}


/*
 * A function that checks if of1, and of2 are in a relationship of oder based on the price and destination
 * Returns 1 if of1 and of2 are in the relationship, 0 otherwise
 */
int compare(struct Oferta of1, struct Oferta of2)
{
    if(of1.pret < of2.pret)
        return 1;
    else if(of1.pret == of2.pret && strcmp(of1.destinatie, of2.destinatie) > 0)
        return 1;
    return 0;
}

/*
 * A function that returns a ListForDisplay struct containg the provided services list sorted descending by price, ascending by destination
 * Preconditions: srv is a Service Pointer
 * Post condition: The ListForDisplay returned contains the list associated to the service sorted
 */
struct ListForDisplay serviceSortList(struct Service *srv, int(*cmp)(struct Oferta, struct Oferta))
{
    struct Oferta **listaDeSortat = malloc(srv->repo.listaOferte.nrOfElements * sizeof ( struct Oferta * ));
    creeazaCopieListaOferte(listaDeSortat, srv->repo.listaOferte.array, srv->repo.listaOferte.nrOfElements);
    for(int i = 0; i < srv->repo.listaOferte.nrOfElements; i++)
    {
        for(int j = i+1; j < srv->repo.listaOferte.nrOfElements; j++)
        {
            if( !cmp(*listaDeSortat[i], *listaDeSortat[j]) )
            {
                //swap
                struct Oferta *ofertatemp;
                ofertatemp = listaDeSortat[i];
                listaDeSortat[i] = listaDeSortat[j];
                listaDeSortat[j] = ofertatemp;
            }
        }
    }
    struct ListForDisplay sortedList;
    sortedList.listaOferte = listaDeSortat;
    sortedList.nrOfElements = srv->repo.listaOferte.nrOfElements;
    return sortedList;
}


/*
 * A function that returns a ListForDisplay struct containg only the instances of the objects in the repo that have the destination field equal to the provided desiredDestiantion
 * Preconditions: srv -> Service pointer, desiredDestination -> char pointer
 * Post condition: the returned ListForDisplay contains a list with the instances that verify the condition
 */
struct ListForDisplay serviceFilterByDestination(struct Service *srv, char *desiredDestination)
{
    struct Oferta **oferte = malloc(srv->repo.listaOferte.nrOfElements * ( sizeof (struct Oferta *)));
    int nrOfElems = 0;
    for(int i = 0; i< srv->repo.listaOferte.nrOfElements; i++)
    {
        if(strcmp(srv->repo.listaOferte.array[i]->destinatie, desiredDestination) == 0)
            oferte[nrOfElems++] = srv->repo.listaOferte.array[i];
    }
    struct ListForDisplay uiList;
    uiList.listaOferte = oferte;
    uiList.nrOfElements = nrOfElems;
    return uiList;
}


/*
 * A function that returns a ListForDisplay struct containg only the instances of the objects in the repo that have the type field equal to the provided desiredType
 * Preconditions: srv -> Service pointer, desiredType -> char pointer
 * Post condition: the returned ListForDisplay contains a list with the instances that verify the condition
 */
struct ListForDisplay serviceFilterByType(struct Service *srv, const char *desiredType)
{
    struct Oferta **oferte = malloc(srv->repo.listaOferte.nrOfElements * ( sizeof (struct Oferta *)));
    int nrOfElems = 0;
    for(int i = 0; i< srv->repo.listaOferte.nrOfElements; i++)
    {
        if(strcmp(srv->repo.listaOferte.array[i]->tip, desiredType) == 0)
            oferte[nrOfElems++] = srv->repo.listaOferte.array[i];
    }
    struct ListForDisplay uiList;
    uiList.listaOferte = oferte;
    uiList.nrOfElements = nrOfElems;
    return uiList;
}

/*
 * A function that returns a ListForDisplay struct containg only the instances of the objects in the repo that have the price field <= to the provided price
 * Preconditions: srv -> Service pointer, price -> int
 * Post condition: the returned ListForDisplay contains a list with the instances that verify the condition
 */
struct ListForDisplay serviceFilterByPrice(struct Service *srv, int price)
{
    struct Oferta **oferte = malloc(srv->repo.listaOferte.nrOfElements * ( sizeof (struct Oferta *)));
    int nrOfElems = 0;
    for(int i = 0; i< srv->repo.listaOferte.nrOfElements; i++)
    {
        if(srv->repo.listaOferte.array[i]->pret <=  price)
            oferte[nrOfElems++] = srv->repo.listaOferte.array[i];
    }

    struct ListForDisplay uiList;
    uiList.listaOferte = oferte;
    uiList.nrOfElements = nrOfElems;
    return uiList;
}

/*
 * A function that checks is the files of two offers are the same(not the id field)
 * Precondition: oferta1, oferta2 -> Oferta
 * Post condition: The function returns 1 if the fields are equal, 0 otherwise
 */
int offersAreEqual(struct Oferta oferta1, struct Oferta oferta2)
{
    if(oferta1.pret != oferta2.pret)
        return 0;
    if(strcmp(oferta1.destinatie, oferta2.destinatie) != 0)
        return 0;
    if(strcmp(oferta1.tip, oferta2.tip) != 0)
        return 0;
    if((oferta1.dataPlecare.an != oferta2.dataPlecare.an) || (oferta1.dataPlecare.luna != oferta2.dataPlecare.luna) || (oferta1.dataPlecare.zi != oferta2.dataPlecare.zi))
        return 0;
    return 1;
}

/*
 * O functie care returneaza o structura de tip oferta care are campul tip ="invalid"
 * Precodnitii: None
 * Postconditii: Obiectul returnat este de tip oferta si are campul tip="invalid"
 */
struct Oferta *createInvalidOffer()
{
    struct Data date;
    date.an = 0;
    date.luna = 0;
    date.an = 0;
    struct Oferta *invalidOffer = createOffer(0, date, "", "invalid");
    return invalidOffer;
}


/*
 * A function that initializes the fileds of a Service struct
 */
void initializeService(struct Service *srv)
{
    initializeRepository(&( srv->repo));
}


/*
 * A method for deallocating all the memory held up by a service
 */
void destroyService(struct Service *srv)
{
    destroyRepository(&(srv->repo));
}


/*
 * A method for freeing up all the memory used by a listForDisplay struct
 */
void freeListForDisplay(struct ListForDisplay *ldToFree)
{
    free(ldToFree->listaOferte);
    ldToFree->listaOferte = NULL;
    ldToFree->nrOfElements = 0;
}


void testFreeListForDisplay()
{
    struct ListForDisplay ld;
    ld.listaOferte = malloc(10*sizeof (struct Oferta *));
    freeListForDisplay(&ld);
    assert(ld.listaOferte == NULL);
    assert(ld.nrOfElements == 0);
}

void testAddOfertaService()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    assert(srv.repo.listaOferte.nrOfElements == 0);
    assert(addOfertaService(&srv, of) == 1);
    assert(srv.repo.listaOferte.nrOfElements == 1);
    struct Oferta *of2 = createOffer(0, data, "", "invalid");
    assert(addOfertaService(&srv, of2) == -1);
    destroyService(&srv);
}

void testModifyPriceService()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    addOfertaService(&srv, of);
    assert(srv.repo.listaOferte.array[0]->pret == 0);
    assert(modifyPrice(&srv, 500, srv.repo.listaOferte.array[0]->id+1) == 0);
    modifyPrice(&srv, 500, srv.repo.listaOferte.array[0]->id);
    assert(srv.repo.listaOferte.array[0]->pret == 500);
    destroyService(&srv);
}

void testModifyType()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    addOfertaService(&srv, of);
    assert(strcmp(srv.repo.listaOferte.array[0]->tip, "Test") == 0);
    assert(modifyType(&srv, "TESTTYPE", srv.repo.listaOferte.array[0]->id+1) == 0);
    modifyType(&srv, "TESTTYPE", srv.repo.listaOferte.array[0]->id);
    assert( strcmp(srv.repo.listaOferte.array[0]->tip, "TESTTYPE") == 0);
    destroyService(&srv);
}

void testModifyDate()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    addOfertaService(&srv, of);
    struct Data newDate;
    newDate.an = 1;
    newDate.luna = 1;
    newDate.zi = 1;
    assert(modifyDate(&srv, newDate, srv.repo.listaOferte.array[0]->id+1) == 0);
    modifyDate(&srv, newDate, srv.repo.listaOferte.array[0]->id);
    assert(srv.repo.listaOferte.array[0]->dataPlecare.an == 1);
    assert(srv.repo.listaOferte.array[0]->dataPlecare.luna == 1);
    assert(srv.repo.listaOferte.array[0]->dataPlecare.zi == 1);
    destroyService(&srv);
}

void testModifyDestination()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    addOfertaService(&srv, of);
    assert(modifyType(&srv, "Diana", srv.repo.listaOferte.array[0]->id+1) == 0);
    modifyDestination(&srv, "Diana", srv.repo.listaOferte.array[0]->id);
    assert( strcmp(srv.repo.listaOferte.array[0]->destinatie, "Diana") == 0);
    destroyService(&srv);
}

void testDeleteOffer()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    addOfertaService(&srv, of);
    assert(deleteOffer(&srv, srv.repo.listaOferte.array[0]->id+1) == 0);
    deleteOffer(&srv, srv.repo.listaOferte.array[0]->id);
    assert(srv.repo.listaOferte.nrOfElements == 0);
    destroyService(&srv);
}

void testCreeazaCopieListaOferte()
{
    struct Oferta **listaOriginala, **listaCopie;
    struct Oferta of1, of2;
    listaOriginala = malloc(2*sizeof (struct Oferta *));
    listaCopie = malloc(2*sizeof (struct Oferta *));
    listaOriginala[0] = &of1;
    listaOriginala[1] = &of2;
    creeazaCopieListaOferte(listaCopie, listaOriginala, 2);
    assert(listaCopie[0] == &of1);
    assert(listaCopie[1] == &of2);
    free(listaOriginala);
    free(listaCopie);
}

void testServiceSortList()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 1;
    data.luna = 1;
    data.zi = 1;
    struct Oferta * of = createOffer(1000, data, "Bali", "Mare");
    struct Oferta * of2 = createOffer(500, data, "Aali", "Munte");
    struct Oferta * of3 = createOffer(500, data, "Cali", "Munte");
    addOfertaService(&srv, of);
    addOfertaService(&srv, of2);
    addOfertaService(&srv, of3);
    struct ListForDisplay ld = serviceSortList(&srv, compare);
    assert(ld.listaOferte[0] == of3);
    assert(ld.listaOferte[1] == of2);
    assert(ld.listaOferte[2] == of);
    free(ld.listaOferte);
    destroyService(&srv);
}

void testCreateInvalidOffer()
{
    struct Oferta *of = createInvalidOffer();
    assert(strcmp(of->tip, "invalid") == 0);

    destroyOffer(&of);
}

void testServiceFilterByDestination()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 1;
    data.luna = 1;
    data.zi = 1;
    struct Oferta *of;
    of = createOffer(1, data, "Mali", "Mare");
    addOfertaService(&srv, of);
    struct ListForDisplay ld1 = serviceFilterByDestination(&srv, "Mali");
    assert(ld1.nrOfElements == 1);
    struct ListForDisplay ld2 = serviceFilterByDestination(&srv, "Telefonatorul");
    assert(ld2.nrOfElements == 0);
    free(ld1.listaOferte);
    free(ld2.listaOferte);
    destroyService(&srv);
}

void testServiceFilterByType()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 1;
    data.luna = 1;
    data.zi = 1;
    struct Oferta *of;
    of = createOffer(1, data, "Mali", "Mare");
    addOfertaService(&srv, of);
    struct ListForDisplay ld1 = serviceFilterByType(&srv, "Mare");
    assert(ld1.nrOfElements == 1);
    struct ListForDisplay ld2 = serviceFilterByType(&srv, "Goggins");
    assert(ld2.nrOfElements == 0);
    free(ld1.listaOferte);
    free(ld2.listaOferte);
    destroyService(&srv);
}

void testServiceFilterByPrice()
{
    struct Service srv;
    initializeService(&srv);
    struct Data data;
    data.an = 1;
    data.luna = 1;
    data.zi = 1;
    struct Oferta *of;
    of = createOffer(1, data, "Mali", "Mare");
    addOfertaService(&srv, of);
    struct ListForDisplay ld1 = serviceFilterByPrice(&srv, 5);
    assert(ld1.nrOfElements == 1);
    struct ListForDisplay ld2 = serviceFilterByPrice(&srv, 0);
    assert(ld2.nrOfElements == 0);
    free(ld1.listaOferte);
    free(ld2.listaOferte);
    destroyService(&srv);

}

void testOffersAreEqual()
{
    struct Oferta oferta, oferta2, oferta3;
    oferta.tip = malloc(15);
    oferta.destinatie = malloc(15);
    oferta2.tip = malloc(15);
    oferta2.destinatie = malloc(15);
    oferta3.tip = malloc(15);
    oferta3.destinatie = malloc(15);
    oferta.dataPlecare.zi = 10;
    oferta.dataPlecare.luna = 1;
    oferta.dataPlecare.an = 2030;
    strcpy(oferta.tip, "Mare");
    strcpy(oferta.destinatie, "Bali");
    oferta.pret = 1000;
    oferta2.dataPlecare.zi = 5;
    oferta2.dataPlecare.luna = 2;
    oferta2.dataPlecare.an = 2035;
    strcpy(oferta2.tip, "Munte");
    strcpy(oferta2.destinatie, "Aali");
    oferta2.pret = 500;
    oferta3.dataPlecare.zi = 10;
    oferta3.dataPlecare.luna = 1;
    oferta3.dataPlecare.an = 2030;
    strcpy(oferta3.tip, "Mare");
    strcpy(oferta3.destinatie, "Bali");
    oferta3.pret = 1000;
    assert(offersAreEqual(oferta, oferta2) == 0);
    assert(offersAreEqual(oferta, oferta3) == 1);
    oferta2.pret = 1000;
    strcpy(oferta3.tip, "City break");
    assert(offersAreEqual(oferta3, oferta) == 0);
    assert(offersAreEqual(oferta, oferta2) == 0);
    oferta.pret = 10;
    oferta2.pret = 10;
    strcpy(oferta.destinatie, "a");
    strcpy(oferta2.destinatie, "a");
    strcpy(oferta.tip, "b");
    strcpy(oferta2.tip, "b");
    assert(offersAreEqual(oferta, oferta2) == 0);
    free(oferta.tip);
    free(oferta.destinatie);
    free(oferta2.tip);
    free(oferta2.destinatie);
    free(oferta3.tip);
    free(oferta3.destinatie);
}

void testCompare()
{
    struct Oferta of1, of2;
    of1.pret = 100;
    of2.pret = 200;
    assert(compare(of1, of2) == 1);
    of1.destinatie = malloc(10);
    of2.destinatie = malloc(10);
    of2.pret = 100;
    strcpy(of1.destinatie, "Sare");
    strcpy(of2.destinatie, "Moare");
    assert(compare(of1, of2) == 1);
    strcpy(of1.destinatie, "Mare");
    strcpy(of2.destinatie, "Soare");
    assert(compare(of1, of2) == 0);
    free(of1.destinatie);
    free(of2.destinatie);
}

/*
 * O functie care testeaza toate functionalitatile implementate in service
 */
void testService()
{
    testAddOfertaService();
    testModifyPriceService();
    testModifyType();
    testModifyDate();
    testModifyDestination();
    testDeleteOffer();
    testDeleteOffer();
    testCreeazaCopieListaOferte();
    testServiceSortList();
    testServiceFilterByDestination();
    testServiceFilterByType();
    testServiceFilterByPrice();
    testCreateInvalidOffer();
    testOffersAreEqual();
    testFreeListForDisplay();
    testCompare();
}
