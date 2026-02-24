#include "ValidadorFlip.h"
#include "../Cartas/CartaNumero.h"
#include "../Cartas/CartaNegra.h"

bool ValidadorFlip::esJugadaValida(Carta* cartaA, Carta* cartaB, const ReglasJuego& reglas, bool acumulacionActiva) {

    // 1. Cartas negras siempre jugables (la que se quiere jugar)
    if (cartaA->getColorActual() == NEGRO) return true;

    // 2. Si la carta en mesa es negra, comparar contra color elegido
    CartaNegra* mesaNegra = dynamic_cast<CartaNegra*>(cartaB);
    if (mesaNegra != nullptr) {
        Color elegido = mesaNegra->getColorElegido();
        if (elegido != NEGRO) {
            return cartaA->getColorActual() == elegido;
        }
        return true; // Si no eligió color aún, cualquier carta vale
    }

    // 3. Acumulación
    if (acumulacionActiva && reglas.getAcumulacion()) {
        std::string tipo = cartaA->getTipoActual();
        std::string tipoMesa = cartaB->getTipoActual();
        if (tipo == "Mas2" || tipo == "Mas4" || tipo == "Mas1" || tipo == "Mas3" || tipo == "Mas6") {
            return tipo == tipoMesa;
        }
        return false;
    }

    // 4. Validación normal
    if (coincidenColor(cartaA, cartaB)) return true;
    if (coincidenTipo(cartaA, cartaB)) return true;

    return false;
}

bool ValidadorFlip::coincidenColor(Carta* a, Carta* b) {
    return a->getColorActual() == b->getColorActual();
}

bool ValidadorFlip::coincidenTipo(Carta* a, Carta* b) {
    if (a->getTipoActual() != b->getTipoActual()) return false;

    // Si ambas son números, verificamos que el número sea el mismo
    CartaNumero* numA = dynamic_cast<CartaNumero*>(a);
    CartaNumero* numB = dynamic_cast<CartaNumero*>(b);

    if (numA != nullptr && numB != nullptr) {
        return (numA->getNumeroActual() == numB->getNumeroActual());
    }

    return true; // Mismo tipo no numérico (Salto, Reversa, Portal, etc.)
}

bool ValidadorFlip::esCartaEspecial(Carta* a) {
    std::string tipo = a->getTipoActual();
    return (tipo == "Salto" || tipo == "Reversa" || tipo == "SaltoTodos" ||
            tipo == "Mas1"  || tipo == "Mas2"    || tipo == "Mas3"       ||
            tipo == "Mas4"  || tipo == "Mas6"    || tipo == "Portal"     ||
            tipo == "ColorEterno" || tipo == "PistolaLaser" || tipo == "CanonLaser");
}