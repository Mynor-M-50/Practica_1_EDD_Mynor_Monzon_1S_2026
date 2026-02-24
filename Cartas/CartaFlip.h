//
// Created by mynorm50 on 12/2/26.
//

#ifndef CARTA_FLIP_H
#define CARTA_FLIP_H

#include "Carta.h"

class CartaFlip : public Carta {
public:
    // Carta "Portal" en ambos lados, cambia de colo
    CartaFlip(Color cClaro, Color cOscuro);
    
    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;
};

#endif