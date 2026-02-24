#include "CartaAccion.h"
#include <iostream>

CartaAccion::CartaAccion(Color cClaro, std::string tClaro, Color cOscuro, std::string tOscuro)
    : Carta(cClaro, tClaro, cOscuro, tOscuro) {}

void CartaAccion::mostrar() const {
    std::cout << getColorANSI(getColorActual())
        << "[" << (esLadoOscuro ? "OSCURO" : "CLARO") << "] "
        << "Accion: " << getTipoActual()
        << resetColor() << std::endl;
}

bool CartaAccion::esJugable(Carta* otra, bool acumulacionActiva) const {
    if (acumulacionActiva) {
        std::string tipo = getTipoActual();
        if (tipo == "Mas1" || tipo == "Mas3") {
            return (tipo == otra->getTipoActual());
        }
        return false;
    }

    if (this->getColorActual() == otra->getColorActual()) return true;
    if (this->getTipoActual() == otra->getTipoActual()) return true;

    return false;
}