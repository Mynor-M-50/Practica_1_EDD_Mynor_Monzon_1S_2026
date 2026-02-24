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
        // Mostramos el color elegido con su propio color ANSI
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
        // Solo puedes acumular si la carta en mesa también es de robo
        return (tipo == "Mas2" && tipoOtra == "Mas2") ||
                (tipo == "Mas6" && tipoOtra == "Mas6");
    }

    return true;
}

void CartaNegra::setColorElegido(Color c) { this->colorElegido = c; }
Color CartaNegra::getColorElegido() const { return colorElegido; }