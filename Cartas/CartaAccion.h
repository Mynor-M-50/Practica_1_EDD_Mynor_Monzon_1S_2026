//
// Created by mynorm50 on 10/2/26.
//

#ifndef CARTA_ACCION_H
#define CARTA_ACCION_H

#include "Carta.h"

class CartaAccion : public Carta {
public:
    CartaAccion(Color cClaro, std::string tClaro, Color cOscuro, std::string tOscuro);

    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;
};

#endif