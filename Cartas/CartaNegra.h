#ifndef CARTA_NEGRA_H
#define CARTA_NEGRA_H

#include "Carta.h"

class CartaNegra : public Carta {
private:
    Color colorElegido;

public:
    CartaNegra(std::string tipoClaro, std::string tipoOscuro);

    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;
    
    void setColorElegido(Color c);
};

#endif