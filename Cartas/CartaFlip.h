#ifndef CARTA_FLIP_H
#define CARTA_FLIP_H

#include "Carta.h"

class CartaFlip : public Carta {
public:
    // Esta carta es "Portal" en ambos lados, pero cambia de color
    CartaFlip(Color cClaro, Color cOscuro);
    
    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;
};

#endif