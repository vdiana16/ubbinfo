//
// Created by danpe on 3/9/2024.
//
#include <stdlib.h>
#include "repoOfertaHeader.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*
 * A function that copies the value of the fields of the source offer into the destination offer
 * Preconditions: destination-> Oferta* to the object that will be assigned the fields of the source offer
 *                source-> an Oferta object
 *  Postcondition: All the fields of the destination object will be qual to those of the source object
 */
void assign(struct Oferta *destinatie, struct Oferta sursa)
{
    strcpy(destinatie->destinatie, sursa.destinatie);
    strcpy(destinatie->tip, sursa.tip);
    destinatie->dataPlecare.zi = sursa.dataPlecare.zi;
    destinatie->dataPlecare.luna = sursa.dataPlecare.luna;
    destinatie->dataPlecare.an = sursa.dataPlecare.an;
    destinatie->pret = sursa.pret;
    destinatie->id = sursa.id;
}

/*
 * A function that returns 1 if the specified id does not appear in the repository, 0 otherwise
 * Preconditions: id -> int representig the id to be checked, rep-> pointer to a repository
 * Post condition: returns 0 if the id already assigned to one of the offers, 1 otherwise
 */
int isValidId(int id, struct Repository *rep)
{
    for(int i = 0; i < rep->listaOferte.nrOfElements; i++)
    {
        if( rep->listaOferte.array[i]->id == id)
            return 0;
    }
    return 1;
}

int resize(struct VectorDinamicOferte *ve)
{
    struct Oferta **vectorNou = malloc( ( 2* ( ve->capacity) ) *sizeof( struct Oferta*));
    for( int i = 0; i < ve->nrOfElements; i++)
    {
        vectorNou[i] = ve->array[i];
    }
    ve->capacity *= 2;
    free(ve->array);
    ve->array = vectorNou;
    return 1;
}

/*
 * A function for adding an oferta type object into the repository
 * Precondition: repo is a pointer to a repository and ofertaToAdd is an offer
 * Post condition: the offerList will contain the offer specified
 */
int add(struct Repository *repo, struct Oferta *ofertaToAdd)
{
    if ( repo->listaOferte.capacity == repo->listaOferte.nrOfElements )
        resize(&( repo->listaOferte ));
    repo->listaOferte.array[repo->listaOferte.nrOfElements] = ofertaToAdd;
    int id = rand();
    while(!isValidId(id, repo))
    {
        id = rand();
    }
    repo->listaOferte.array[repo->listaOferte.nrOfElements]->id = id;
    repo->listaOferte.nrOfElements++;
    return 1;
}

/*
 * A function that returns the index of the offer with the specified id, -1 otherwise
 * Precodition: idToFind -> int, rep is a pointer to a repository
 * Postcondition: the function will return the index of the offer in the offerList of the repository if an obhect with the id exists, -1 otherwise
 */
int find(int idToFind, struct Repository *rep)
{
    for(int i = 0; i < rep->listaOferte.nrOfElements; i++)
    {
        if(rep->listaOferte.array[i]->id == idToFind)
            return i;
    }
    return -1;
}

/*
 * A function that modifies the type of the offer with the specified id if the offer exists, returns 0 otherwise
 * Precondition: rep-> Pointer to a repository, newType-> a const char* containg the new type, idToModify-> the id of the offer that needs to be modified
 * Post condition: the type of the object with id=idToModify will be newType
 */
int repoModifyType(struct Repository *rep, const char* newType, int idToModify)
{
    int indexToModify = find(idToModify, rep);
    if( indexToModify == -1)
        return 0;
    char *newTypeAddress = malloc(strlen(newType) + 1);
    strcpy(newTypeAddress, newType);
    free(rep->listaOferte.array[indexToModify]->tip);
    rep->listaOferte.array[indexToModify]->tip = newTypeAddress;
    return 1;
}

/*
 * A function that modifies the price of the offer with the specified id if the offer exists
 * Precondition: rep-> Pointer to a repository, newPrice-> an int that contains the value to be modified to, idToModify-> the id of the offer that needs to be modified
 * Post condition: the price of the object with id=idToModify will be newPrice
 */
int repoModifyPrice(struct Repository *rep, int newPrice, int idToModify)
{
    int indexToModify = find(idToModify, rep);
    if(indexToModify == -1)
        return 0;
    rep->listaOferte.array[indexToModify]->pret = newPrice;
    return 1;
}

/*
 * A function that modifies the destination of the offer with the specified id if the offer exists
 * Precondition: rep-> Pointer to a repository, newDestination-> a const char* containg the new destination, idToModify-> the id of the offer that needs to be modified
 * Post condition: the destination of the object with id=idToModify will be newDestination
 */
int repoModifyDestination(struct Repository *rep, const char* newDestination, int idToModify)
{
    int indexToModify = find(idToModify, rep);
    if( indexToModify == -1)
        return 0;
    char *newDestinationAddress = malloc(strlen(newDestination)+1);
    strcpy(newDestinationAddress, newDestination);
    free(rep->listaOferte.array[indexToModify]->destinatie);
    rep->listaOferte.array[indexToModify]->destinatie = newDestinationAddress;
    return 1;
}

/*
 * A function that modifies the date of the offer with the specified id if the offer exists
 * Precondition: rep-> Pointer to a repository, newDate-> a Data object, idToModify-> the id of the offer that needs to be modified
 * Post condition: the date of the object with id=idToModify will be newDate
 */
int repoModifyDate(struct Repository *rep, struct Data newDate, int idToModify)
{
    int indexToModify = find(idToModify, rep);
    if( indexToModify == -1)
        return 0;
    rep->listaOferte.array[indexToModify]->dataPlecare.an = newDate.an;
    rep->listaOferte.array[indexToModify]->dataPlecare.luna = newDate.luna;
    rep->listaOferte.array[indexToModify]->dataPlecare.zi = newDate.zi;
    return 1;
}

/*
 * A function that deletes the object with the specified id if the id is valid, return 0 otherwise
 * Precondition: rep-> pointer to a repository, idToDelete-> id of the offer that will be deleted
 * Post condition: the object with the specified id will not be in the offerList attribute of the repository
 */
int repoDeleteOffer(struct Repository *rep, int idToDelete)
{
    int indexToDelete = find(idToDelete, rep);

    if( indexToDelete == -1)
        return 0;
    destroyOffer(&rep->listaOferte.array[indexToDelete]);
    if(indexToDelete != rep->listaOferte.nrOfElements-1)
        for(int i = indexToDelete+1; i < rep->listaOferte.nrOfElements; i++)
            rep->listaOferte.array[i-1] = rep->listaOferte.array[i];
    rep->listaOferte.nrOfElements--;

    return 1;
}

void initializeRepository(struct Repository *rep)
{
    rep->listaOferte.array = malloc(sizeof (struct Oferta *));
    rep->listaOferte.nrOfElements = 0;
    rep->listaOferte.capacity = 1;
}

void destroyRepository(struct Repository *rep)
{
    for(int i = 0; i < rep->listaOferte.nrOfElements; i++)
    {
        destroyOffer(&(rep->listaOferte.array[i]));
    }
    free(rep->listaOferte.array);
}


void testAssign()
{
    struct Oferta dest, source;
    source.pret = 50;
    dest.pret = 0;
    dest.tip = malloc(15);
    dest.destinatie = malloc(15);
    source.tip = malloc(15);
    source.destinatie = malloc(15);
    strcpy(dest.tip, "0");
    strcpy(dest.destinatie, "0");
    strcpy(source.tip, "Mare");
    strcpy(source.destinatie, "Bali");
    assign(&dest, source);
    assert(strcmp(dest.tip, "Mare") == 0);
    assert(strcmp(dest.destinatie, "Bali") == 0);
    assert(dest.pret == 50);
    free(dest.tip);
    free(dest.destinatie);
    free(source.tip);
    free(source.destinatie);
}

void testIsValidId()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Repository rep;
    initializeRepository(&rep);
    struct Oferta *oferta = createOffer(0, data, "", "Test");
    add(&rep, oferta);
    assert(isValidId(rep.listaOferte.array[0]->id, &rep) == 0);
    assert(isValidId((rep.listaOferte.array[0]->id) +1, &rep) == 1);
    destroyRepository(&rep);
}

void testAdd()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    struct Repository rep;
    initializeRepository(&rep);
    add(&rep, of);
    assert(find(rep.listaOferte.array[0]->id, &rep) == 0);
    destroyRepository(&rep);
}

void testFind()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    struct Repository rep;
    initializeRepository(&rep);
    add(&rep, of);
    assert(find(rep.listaOferte.array[0]->id, &rep) == 0);
    assert(find(rep.listaOferte.array[0]->id + 1, &rep) == -1);
    destroyRepository(&rep);

}

void testRepoModifyType()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    struct Repository rep;
    initializeRepository(&rep);
    add(&rep, of);
    assert(repoModifyType(&rep,"Munte", rep.listaOferte.array[0]->id + 1) == 0);
    repoModifyType(&rep, "Munte", rep.listaOferte.array[0]->id);
    assert(strcmp(rep.listaOferte.array[0]->tip, "Munte") == 0);
    destroyRepository(&rep);
}

void testRepoModifyPrice()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    struct Repository rep;
    initializeRepository(&rep);
    add(&rep, of);
    assert(repoModifyPrice(&rep,100, rep.listaOferte.array[0]->id + 1) == 0);
    repoModifyPrice(&rep, 100, rep.listaOferte.array[0]->id);
    assert(rep.listaOferte.array[0]->pret == 100);
    destroyRepository(&rep);
}

void testRepoModifyDestination()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    struct Repository rep;
    initializeRepository(&rep);
    add(&rep, of);
    assert(repoModifyDestination(&rep,"TESTDEST", rep.listaOferte.array[0]->id + 1) == 0);
    repoModifyDestination(&rep, "TESTDEST", rep.listaOferte.array[0]->id);
    assert(strcmp(rep.listaOferte.array[0]->destinatie, "TESTDEST") == 0);
    destroyRepository(&rep);
}

void testRepoModifyDate()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Data newDate;
    newDate.zi = 20;
    newDate.luna = 2;
    newDate.an = 3000;
    struct Oferta *of = createOffer(0, data, "", "Test");
    struct Repository rep;
    initializeRepository(&rep);
    add(&rep, of);
    repoModifyDate(&rep, newDate, rep.listaOferte.array[0]->id);
    assert((rep.listaOferte.array[0]->dataPlecare.zi == 20) && (rep.listaOferte.array[0]->dataPlecare.luna == 2) && (rep.listaOferte.array[0]->dataPlecare.an == 3000));
    destroyRepository(&rep);
}

void testRepoDeleteOffer()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Data data2;
    data2.an = 1;
    data2.luna = 1;
    data2.zi = 1;
    struct Data data3;
    data3.an = 2;
    data3.luna = 2;
    data3.zi = 2;
    struct Repository rep;
    initializeRepository(&rep);
    struct Oferta *oferta, *oferta2, *oferta3;
    oferta = createOffer(0, data, "", "Test");
    oferta2 = createOffer(1, data2, "1", "Test2");
    oferta3 = createOffer(0, data3, "2", "Test3");
    add(&rep, oferta);
    add(&rep, oferta2);
    add(&rep, oferta3);
    repoDeleteOffer(&rep, rep.listaOferte.array[0]->id);
    assert(rep.listaOferte.nrOfElements == 2);
    destroyRepository(&rep);
}

void testResize()
{
    struct Data data;
    data.an = 0;
    data.luna = 0;
    data.zi = 0;
    struct Oferta *of = createOffer(0, data, "", "Test");
    struct Repository rep;
    initializeRepository(&rep);
    add(&rep, of);
    struct Oferta **oldAddress = rep.listaOferte.array;
    int oldCapacity = rep.listaOferte.capacity;
    resize(&rep.listaOferte);
    assert(rep.listaOferte.capacity == 2*oldCapacity);
    assert(rep.listaOferte.array != oldAddress);
    destroyRepository(&rep);
}

void testInitializeRepository()
{
    struct Repository rep;
    initializeRepository(&rep);
    assert(rep.listaOferte.capacity == 1);
    assert(rep.listaOferte.nrOfElements == 0);
    destroyRepository(&rep);
}

void testRepo()
{
    testAssign();
    testIsValidId();
    testAdd();
    testFind();
    testRepoModifyType();
    testRepoModifyPrice();
    testRepoModifyDestination();
    testRepoModifyDate();
    testRepoDeleteOffer();
    testResize();
    testInitializeRepository();
}

//void inutil() {
//    struct Data data;
//    data.an = 0;
//    data.luna = 0;
//    data.zi = 0;
//    struct Oferta *of = createOffer(0, data, "", "Test");
//    destroyOffer(of);
//}