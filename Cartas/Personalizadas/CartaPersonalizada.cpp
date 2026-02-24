//
// Created by mynorm50 on 19/2/26.
//
#include "CartaPersonalizada.h"
#include <iostream>

CartaPersonalizada::CartaPersonalizada()
    : CartaNegra("PistolaLaser", "CanonLaser") {
}

void CartaPersonalizada::mostrar() const {
    if (!esLadoOscuro) {
        std::cout << "\033[1;37m"  // Blanco brillante (se ve bien en terminal negra)
            << "[CLARO] ¡PISTOLA LASER! (El jugador elegido roba 7 cartas!)";
    } else {
        std::cout << getColorANSI(VIOLETA)
            << "[OSCURO] ¡CANON LASER! (Todos los jugadores roban 5 cartas!)";
    }

    if (getColorElegido() != NEGRO) {
        std::cout << " (Color: " << getColorNombre(getColorElegido()) << ")";
    }
    
    std::cout << resetColor() << std::endl;
}