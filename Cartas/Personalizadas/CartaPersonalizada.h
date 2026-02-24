//
// Created by mynorm50 on 19/2/26.
//
#ifndef CARTA_PERSONALIZADA_H
#define CARTA_PERSONALIZADA_H

#include "../CartaNegra.h"

class CartaPersonalizada : public CartaNegra {
public:
    // Lado Claro - Pistola Laser | Lado Oscuro - Canon Laser
    CartaPersonalizada();

    void mostrar() const;
};

#endif