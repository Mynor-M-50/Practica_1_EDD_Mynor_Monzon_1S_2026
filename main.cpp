//
// Created by mynorm50 on 1/2/26.
//

#include <iostream>
#include "Configuracion/ConfiguradorPartida.h"
#include "Motor/MotorJuego.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "         Bienvenido al juego UNO        \n";
    std::cout << "        (Con la expansion UNO FLIP)     \n";
    std::cout << "========================================\n\n";

    ConfiguradorPartida configurador;
    configurador.configurarNuevaPartida();

    ReglasJuego reglas = configurador.getReglas();

    // guardamos la lista en una variable primero, luego la pasamos

    ListaCircular<Jugador*> jugadores = configurador.getJugadores();
    MotorJuego motor(reglas, jugadores);

    motor.iniciarJuego();

    std::cout << "\nGracias por jugar :)\n";
    return 0;
}