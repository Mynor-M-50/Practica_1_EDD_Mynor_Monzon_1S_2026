#ifndef CARTA_PERSONALIZADA_H
#define CARTA_PERSONALIZADA_H

#include "../CartaNegra.h"

class CartaPersonalizada : public CartaNegra {
public:
    // Lado Claro: Pistola Laser | Lado Oscuro: Canon Laser
    CartaPersonalizada();

    void mostrar() const;
    // esJugable y setColorElegido ya los hereda de CartaNegra!
};

#endif