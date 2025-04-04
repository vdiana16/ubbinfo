//
// Created by danpe on 3/9/2024.
//

#ifndef SERVICEOFERTAHEADER_H
#define SERVICEOFERTAHEADER_H

#include "repoOfertaHeader.h"

struct Service
{
    struct Repository repo;
};

struct ListForDisplay
{
    struct Oferta **listaOferte;
    int nrOfElements;
};

int addOfertaService(struct Service *srv, struct Oferta *offerToAdd);

int modifyDestination(struct Service *srv, char *newValue, int idToModify);
int modifyDate(struct Service *srv, struct Data newDate, int idToModify);
int modifyType(struct Service *srv, const char *newValue, int idToModify);
int modifyPrice(struct Service *srv, int price, int idToModify);
int deleteOffer(struct Service *srv, int idToModify);
struct ListForDisplay serviceSortList(struct Service *srv, int(*f)(struct Oferta, struct Oferta));
struct ListForDisplay serviceFilterByDestination(struct Service *srv, char *desiredDestination);
struct ListForDisplay serviceFilterByType(struct Service *srv, const char *desiredType);
struct ListForDisplay serviceFilterByPrice(struct Service *srv, int price);
struct Oferta *createInvalidOffer();
void initializeService(struct Service *srv);
void freeListForDisplay(struct ListForDisplay *ldToFree);
void destroyService(struct Service *srv);
int compare(struct Oferta of1, struct Oferta of2);

void testService();

#endif //SERVICEOFERTAHEADER_H
