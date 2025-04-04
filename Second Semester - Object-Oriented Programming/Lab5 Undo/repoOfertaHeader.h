//
// Created by danpe on 3/9/2024.
//

#ifndef REPOOFERTAHEADER_H
#define REPOOFERTAHEADER_H

#include "domainHeader.h"

struct VectorDinamicOferte
{
    struct Oferta **array;
    int nrOfElements;
    int capacity;
};

struct Repository
{
    struct  VectorDinamicOferte listaOferte;
};

int add(struct Repository *repo, struct Oferta *ofertaToAdd);
int repoModifyType(struct Repository *rep, const char* newType, int idToModify);
int repoModifyPrice(struct Repository *rep, int newPrice, int idToModify);
int repoModifyDestination(struct Repository *rep, const char* newDestination, int idToModify);
int repoModifyDate(struct Repository *rep, struct Data newDate, int idToModify);
int repoDeleteOffer(struct Repository *rep, int idToDelete);
void assign(struct Oferta *destinatie, struct Oferta sursa);
void initializeRepository(struct Repository *rep);
void testRepo();
void destroyRepository(struct Repository *rep);

#endif //REPOOFERTAHEADER_H
