#include "ConfiguradorPartida.h"
#include <iostream>
#include <string>

ConfiguradorPartida::ConfiguradorPartida() {}

void ConfiguradorPartida::configurarNuevaPartida() {
    int opcion;
    std::cout << "=== CONFIGURACION DE UNO FLIP ===\n";

    // 1. Configurar Reglas con "Switches" (0 o 1)
    std::cout << "¿Activar acumulacion de cartas (+2, +4, etc)? (1: Si, 0: No): ";
    std::cin >> opcion;
    reglas.setAcumulacion(opcion == 1);

    std::cout << "¿Activar reto de legalidad para +4? (1: Si, 0: No): ";
    std::cin >> opcion;
    reglas.setRetoMas4(opcion == 1);

    std::cout << "¿Penalizar por no decir UNO? (1: Si, 0: No): ";
    std::cin >> opcion;
    reglas.setGritoUno(opcion == 1);

    // 2. Configurar Jugadores
    int n;
    std::cout << "Numero de jugadores (2-10): ";
    std::cin >> n;
    if (n < 2) n = 2;
    if (n > 10) n = 10;
    reglas.setNumJugadores(n);

    for (int i = 0; i < n; i++) {
        std::string nombre;
        std::cout << "Nombre del jugador " << (i + 1) << ": ";
        std::cin >> nombre;
        jugadores.insertar(new Jugador(nombre));
    }

    std::cout << "\n¡Partida configurada con " << reglas.getNumMazos() << " mazos!\n";
}

ReglasJuego ConfiguradorPartida::getReglas() const { return reglas; }
ListaCircular<Jugador*> ConfiguradorPartida::getJugadores() const { return jugadores; }