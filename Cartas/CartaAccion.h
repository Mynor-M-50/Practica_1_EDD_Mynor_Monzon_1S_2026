#ifndef CARTA_ACCION_H
#define CARTA_ACCION_H

#include "Carta.h"

class CartaAccion : public Carta {
public:
    CartaAccion(Color cClaro, std::string tipoClaro, Color cOscuro, std::string tipoOscuro);

    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;
};

#endif