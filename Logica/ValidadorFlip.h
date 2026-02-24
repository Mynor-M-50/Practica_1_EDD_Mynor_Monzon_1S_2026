//
// Created by mynorm50 on 15/2/26.
//

#ifndef VALIDADOR_FLIP_H
#define VALIDADOR_FLIP_H

#include "../Cartas/Carta.h"
#include "ReglasJuego.h"

class ValidadorFlip {
public:
    static bool esJugadaValida(Carta* cartaA, Carta* cartaB, const ReglasJuego& reglas, bool acumulacionActiva);

    static bool coincidenColor(Carta* a, Carta* b);
    static bool coincidenTipo(Carta* a, Carta* b);
    static bool esCartaEspecial(Carta* a);
};

#endif