#include "CartaFlip.h"
#include <iostream>

CartaFlip::CartaFlip(Color cClaro, Color cOscuro)
    : Carta(cClaro, "Portal", cOscuro, "Portal") {}

void CartaFlip::mostrar() const {
    std::cout << getColorANSI(getColorActual())
        << "[" << (esLadoOscuro ? "OSCURO" : "CLARO") << "] "
        << "¡PORTAL! " << getColorNombre(getColorActual())
        << resetColor() << std::endl;
}

bool CartaFlip::esJugable(Carta* otra, bool acumulacionActiva) const {
    if (acumulacionActiva) return false;

    if (this->getColorActual() == otra->getColorActual()) return true;
    if (otra->getTipoActual() == "Portal") return true;

    return false;
}