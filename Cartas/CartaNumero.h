#ifndef CARTA_NUMERO_H
#define CARTA_NUMERO_H

#include "Carta.h"

class CartaNumero : public Carta {
private:
    int numeroClaro;
    int numeroOscuro;

public:
    CartaNumero(Color cClaro, int nClaro, Color cOscuro, int nOscuro);
    
    void mostrar() const;
    bool esJugable(Carta* otra, bool acumulacionActiva) const;
    
    int getNumeroActual() const;
};

#endif