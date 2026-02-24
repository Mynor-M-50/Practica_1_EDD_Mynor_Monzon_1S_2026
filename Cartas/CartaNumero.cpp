//
// Created by mynorm50 on 10/2/26.
//

#include "CartaNumero.h"
#include <iostream>

CartaNumero::CartaNumero(Color cClaro, int nClaro, Color cOscuro, int nOscuro)
    : Carta(cClaro, "Numero", cOscuro, "Numero") {
    this->numeroClaro = nClaro;
    this->numeroOscuro = nOscuro;
}

void CartaNumero::mostrar() const {
    std::cout << getColorANSI(getColorActual())
        << "[" << (esLadoOscuro ? "OSCURO" : "CLARO") << "] "
        << "Numero: " << getNumeroActual()
        << resetColor() << std::endl;
}

bool CartaNumero::esJugable(Carta* otra, bool acumulacionActiva) const {
    if (acumulacionActiva) return false;

    if (this->getColorActual() == otra->getColorActual()) return true;

    CartaNumero* otraNum = dynamic_cast<CartaNumero*>(otra);
    if (otraNum != nullptr) {
        if (this->getNumeroActual() == otraNum->getNumeroActual()) return true;
    }

    return false;
}

int CartaNumero::getNumeroActual() const {
    return esLadoOscuro ? numeroOscuro : numeroClaro;
}