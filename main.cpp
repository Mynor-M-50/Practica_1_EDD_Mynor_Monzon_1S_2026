#include <iostream>
#include "Configuracion/ConfiguradorPartida.h"
#include "Motor/MotorJuego.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "        UNO FLIP - Estructuras         \n";
    std::cout << "========================================\n\n";

    ConfiguradorPartida configurador;
    configurador.configurarNuevaPartida();

    ReglasJuego reglas = configurador.getReglas();

    // ✅ Guardamos la lista en una variable primero, luego la pasamos
    ListaCircular<Jugador*> jugadores = configurador.getJugadores();
    MotorJuego motor(reglas, jugadores);

    motor.iniciarJuego();

    std::cout << "\nGracias por jugar :)\n";
    return 0;
}