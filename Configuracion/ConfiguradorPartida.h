//
// Created by mynorm50 on 15/2/26.
//

#ifndef CONFIGURADOR_PARTIDA_H
#define CONFIGURADOR_PARTIDA_H

#include "../Logica/ReglasJuego.h"
#include "../Estructuras/ListaCircular.h"
#include "../Jugador/Jugador.h"

class ConfiguradorPartida {
private:
    ReglasJuego reglas;
    ListaCircular<Jugador*> jugadores;

public:
    ConfiguradorPartida();
    
    void configurarNuevaPartida();

    ReglasJuego getReglas() const;
    ListaCircular<Jugador*> getJugadores() const;
};

#endif