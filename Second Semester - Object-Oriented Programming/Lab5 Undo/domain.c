//
// Created by danpe on 3/13/2024.
//
//
// Created by danpe on 3/13/2024.
//
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "domainHeader.h"


/*
 * A function that instantiates an Oferta with the specified attributes on the heap and returns a pointer to the specific offer
 */
struct Oferta *createOffer(int price, struct Data date, char * destination,const char * type)
{
    struct Oferta *offer;
    offer = (struct Oferta *) malloc(sizeof(struct Oferta));
    offer->dataPlecare.an = date.an;
    offer->dataPlecare.luna = date.luna;
    offer->dataPlecare.zi =  date.zi;
    offer->tip = malloc(strlen(type) + 1);
    offer->destinatie = malloc(strlen(destination) + 1);
    strcpy(offer->tip, type);
    strcpy(offer->destinatie, destination);
    offer->pret = price;
    return offer;
}

/*
 * A function for freeing an Offer allocated on the heap
 */
void destroyOffer(struct Oferta **offerToDistroy)
{
    free(( *offerToDistroy )->tip);
    free(( *offerToDistroy )->destinatie);
    free( *offerToDistroy );
    *offerToDistroy = NULL;
}

int getOfferPrice(const struct Oferta * of)
{
    return of->pret;
}

char *getOfferDestination(const struct Oferta * of)
{
    return of->destinatie;
}

char *getOfferType(const struct Oferta * of)
{
    return of->tip;
}

struct Data getOfferDate(const struct Oferta * of)
{
    return of->dataPlecare;
}

void testCreateOffer()
{
    struct Data date;
    date.an = 2012;
    date.luna = 12;
    date.zi = 12;
    struct Oferta *of = createOffer(100, date, "Praga", "city break");
    assert(of->pret == 100);
    assert(strcmp(of->tip, "city break") == 0);
    assert(strcmp(of->destinatie, "Praga") == 0);
    destroyOffer(&of);
}

void testDestroyOffer()
{
    struct Data date;
    date.an = 2012;
    date.luna = 12;
    date.zi = 12;
    struct Oferta *of = createOffer(100, date, "Praga", "city break");
    assert(of != NULL);
    destroyOffer(&of);
    assert(of == NULL);
}

void testGetters()
{
    struct Data date;
    date.an = 2012;
    date.luna = 12;
    date.zi = 12;
    struct Oferta *of = createOffer(100, date, "Praga", "city break");
    assert(getOfferPrice(of) == 100);
    assert(strcmp( getOfferDestination(of), "Praga" ) == 0);
    assert(strcmp( getOfferType(of), "city break" ) == 0);
    assert((getOfferDate(of).zi == 12) && (getOfferDate(of).luna == 12) && (getOfferDate(of).an == 2012));
    destroyOffer(&of);
}



void testDomain()
{
    testCreateOffer();
    testDestroyOffer();
    testGetters();
}


