//
// Created by mynorm50 on 10/2/26.
//

#include "CartaNegra.h"
#include <iostream>

CartaNegra::CartaNegra(std::string tClaro, std::string tOscuro)
    : Carta(NEGRO, tClaro, NEGRO, tOscuro) {
    this->colorElegido = NEGRO;
}

void CartaNegra::mostrar() const {
    std::cout << getColorANSI(NEGRO)
        << "[" << (esLadoOscuro ? "OSCURO" : "CLARO") << "] "
        << "Especial: " << getTipoActual();
    if (colorElegido != NEGRO) {
        // color elegido con su propio color ANSI
        std::cout << " (Color elegido: "
            << getColorANSI(colorElegido) << getColorNombre(colorElegido)
            << getColorANSI(NEGRO) << ")";
    }
    std::cout << resetColor() << std::endl;
}

bool CartaNegra::esJugable(Carta* otra, bool acumulacionActiva) const {
    if (acumulacionActiva) {
        std::string tipo = getTipoActual();
        std::string tipoOtra = otra->getTipoActual();
        // Solo se podra acumular si la carta en mesa tambien es de robar
        return (tipo == "Mas 2 (+2)" && tipoOtra == "Mas 2 (+2)") ||
                (tipo == "Mas 6 (+6)" && tipoOtra == "Mas 6 (+6)");
    }

    return true;
}

void CartaNegra::setColorElegido(Color c) { this->colorElegido = c; }
Color CartaNegra::getColorElegido() const { return colorElegido; }