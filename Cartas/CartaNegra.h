//
// Created by mynorm50 on 10/2/26.
//

#ifndef CARTA_NEGRA_H
#define CARTA_NEGRA_H

#include "Carta.h"

class CartaNegra : public Carta {
private:
    Color colorElegido;

public:
    CartaNegra(std::string tClaro, std::string tOscuro);

    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;

    void setColorElegido(Color c);
    Color getColorElegido() const;
};

#endif