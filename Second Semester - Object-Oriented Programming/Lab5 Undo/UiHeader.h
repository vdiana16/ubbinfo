//
// Created by danpe on 3/8/2024.
//

#ifndef UIHEADER_H
#define UIHEADER_H

#include "serviceOfertaHeader.h"

struct UI
{
    struct Service srv;
};
void startUI(struct UI *ui);
void afiseazaOferta(struct Oferta oferta);
void initializeUI(struct UI *ui);
void UICleanup(struct UI *ui);

#endif //UIHEADER_H
