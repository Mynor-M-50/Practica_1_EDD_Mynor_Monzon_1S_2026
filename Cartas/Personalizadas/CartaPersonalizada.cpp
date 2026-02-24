#include "CartaPersonalizada.h"
#include <iostream>

CartaPersonalizada::CartaPersonalizada()
    : CartaNegra("PistolaLaser", "CanonLaser") {
    // El constructor de CartaNegra ya pone los colores en NEGRO
}

void CartaPersonalizada::mostrar() const {
    if (!esLadoOscuro) {
        std::cout << "\033[1;37m"  // Blanco brillante (se ve bien en terminal negra)
            << "[CLARO] ¡PISTOLA LASER! (Roba 7 a uno)";
    } else {
        std::cout << getColorANSI(VIOLETA)
            << "[OSCURO] ¡CANON LASER! (Roba 5 a TODOS)";
    }

    if (getColorElegido() != NEGRO) {
        std::cout << " (Color: " << getColorNombre(getColorElegido()) << ")";
    }
    
    std::cout << resetColor() << std::endl;
}