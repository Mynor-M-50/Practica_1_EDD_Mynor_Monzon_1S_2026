#include "Carta.h"

Carta::Carta(Color cClaro, std::string tClaro, Color cOscuro, std::string tOscuro) {
    this->colorClaro = cClaro;
    this->tipoClaro = tClaro;
    this->colorOscuro = cOscuro;
    this->tipoOscuro = tOscuro;
    this->esLadoOscuro = false;
}

Color Carta::getColorActual() const {
    return esLadoOscuro ? colorOscuro : colorClaro;
}

std::string Carta::getTipoActual() const {
    return esLadoOscuro ? tipoOscuro : tipoClaro;
}

bool Carta::getEsLadoOscuro() const {
    return esLadoOscuro;
}

void Carta::setLado(bool oscuro) {
    this->esLadoOscuro = oscuro;
}

std::string Carta::resetColor() {
    return "\033[0m";
}

std::string Carta::getColorANSI(Color c) {
    switch (c) {
        case ROJO:     return "\033[31m";
        case VERDE:    return "\033[32m";
        case AMARILLO: return "\033[33m";
        case AZUL:     return "\033[34m";
        case ROSA:     return "\033[35m";
        case TURQUESA: return "\033[36m";
        case NARANJA:  return "\033[38;5;208m"; // Color extendido para Naranja
        case VIOLETA:  return "\033[38;5;93m";  // Color extendido para Violeta
        case NEGRO:    return "\033[37m";       // Blanco/Gris para cartas negras
        default:       return "\033[0m";
    }
}

std::string Carta::getColorNombre(Color c) {
    switch (c) {
        case ROJO:     return "Rojo";
        case AMARILLO: return "Amarillo";
        case AZUL:     return "Azul";
        case VERDE:    return "Verde";
        case ROSA:     return "Rosa";
        case TURQUESA: return "Turquesa";
        case NARANJA:  return "Naranja";
        case VIOLETA:  return "Violeta";
        case NEGRO:    return "Negro";
        default:       return "Ninguno";
    }
}