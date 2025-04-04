//
// Created by danpe on 3/8/2024.
//

#ifndef DOMAINHEADER_H
#define DOMAINHEADER_H

/*
 * Struct used to store a date
 */
struct Data
{
    int zi;
    int luna;
    int an;
};

/*
 * Stuct used to store an offer
 */
struct Oferta
{
    char *tip;
    char *destinatie;
    struct Data dataPlecare;
    int pret;
    int id;
};

struct Oferta *createOffer(int price, struct Data date, char * destination, const char * type);
void destroyOffer(struct Oferta **offerToDistroy);
int getOfferPrice(const struct Oferta * of);
char *getOfferDestination(const struct Oferta * of);
char *getOfferType(const struct Oferta * of);
struct Data getOfferDate(const struct Oferta * of);
void testDomain();

#endif //DOMAINHEADER_H
