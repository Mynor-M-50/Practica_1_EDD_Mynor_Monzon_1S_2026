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
    
    // El método principal que hace las preguntas por consola
    void configurarNuevaPartida();

    // Getters para que el MotorJuego obtenga lo configurado
    ReglasJuego getReglas() const;
    ListaCircular<Jugador*> getJugadores() const;
};

#endif