#ifndef CARTA_FLIP_H
#define CARTA_FLIP_H

#include "Carta.h"

class CartaFlip : public Carta {
public:
    CartaFlip(Color cClaro, Color cOscuro);
    
    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;
};

#endif