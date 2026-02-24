//
// Created by mynorm50 on 15/2/26.
//

#include "ValidadorFlip.h"
#include "../Cartas/CartaNumero.h"
#include "../Cartas/CartaNegra.h"

bool ValidadorFlip::esJugadaValida(Carta* cartaA, Carta* cartaB, const ReglasJuego& reglas, bool acumulacionActiva) {

    // Cartas negras siempre jugable
    if (cartaA->getColorActual() == NEGRO) return true;

    // si carta es negra, comparar contra color elegido
    CartaNegra* mesaNegra = dynamic_cast<CartaNegra*>(cartaB);
    if (mesaNegra != nullptr) {
        Color elegido = mesaNegra->getColorElegido();
        if (elegido != NEGRO) {
            return cartaA->getColorActual() == elegido;
        }
        return true;
    }

    // Acumulacin
    if (acumulacionActiva && reglas.getAcumulacion()) {
        std::string tipo = cartaA->getTipoActual();
        std::string tipoMesa = cartaB->getTipoActual();
        if (tipo == "Mas 2 (+2)" || tipo == "Mas4 (+4)" || tipo == "Mas 1 (+1)" || tipo == "Mas 3 (+3)" || tipo == "Mas 6 (+6)") {
            return tipo == tipoMesa;
        }
        return false;
    }

    // validacion
    if (coincidenColor(cartaA, cartaB)) return true;
    if (coincidenTipo(cartaA, cartaB)) return true;

    return false;
}

bool ValidadorFlip::coincidenColor(Carta* a, Carta* b) {
    return a->getColorActual() == b->getColorActual();
}

bool ValidadorFlip::coincidenTipo(Carta* a, Carta* b) {
    if (a->getTipoActual() != b->getTipoActual()) return false;

    // Si ambss son numeros, verificamos que el numero sea el mismo
    CartaNumero* numA = dynamic_cast<CartaNumero*>(a);
    CartaNumero* numB = dynamic_cast<CartaNumero*>(b);

    if (numA != nullptr && numB != nullptr) {
        return (numA->getNumeroActual() == numB->getNumeroActual());
    }

    return true;
}

bool ValidadorFlip::esCartaEspecial(Carta* a) {
    std::string tipo = a->getTipoActual();
    return (tipo == "Salto" || tipo == "Reversa" || tipo == "SaltoTodos" ||
            tipo == "Mas 1 (+1)"  || tipo == "Mas 2 (+2)"    || tipo == "Mas 3 (+3)"       ||
            tipo == "Mas 4 (+4)"  || tipo == "Mas 6 (+6)"    || tipo == "Portal"     ||
            tipo == "ColorEterno" || tipo == "PistolaLaser" || tipo == "CanonLaser");
}