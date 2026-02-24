#ifndef MOTOR_JUEGO_H
#define MOTOR_JUEGO_H

#include "../Estructuras/ListaCircular.h"
#include "../Estructuras/ListaEnlazada.h"
#include "../Estructuras/Pila.h"
#include "../Jugador/Jugador.h"
#include "../Cartas/Carta.h"
#include "../Logica/ReglasJuego.h"
#include "../Logica/ValidadorFlip.h"

class MotorJuego {
private:
    ListaCircular<Jugador*> jugadores;
    Pila<Carta*> mazo;
    Pila<Carta*> descarte;
    ReglasJuego reglas;

    bool juegoActivo;
    bool sentidoHorario;
    bool acumulacionActiva;
    int cartasAcumuladas;
    bool modoOscuro;

    void generarMazo();
    void barajarMazo();
    void repartirCartas();
    void ejecutarTurno(Jugador* jugador);
    void aplicarEfecto(Carta* carta, Jugador* jugadorActual);
    void siguienteTurno();
    void voltearJuego();
    Jugador* elegirJugador();
    void mostrarEstado();

public:
    MotorJuego(ReglasJuego reglas, ListaCircular<Jugador*>& jugadores);
    void iniciarJuego();
};

#endif