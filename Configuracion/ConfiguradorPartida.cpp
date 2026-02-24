//
// Created by mynorm50 on 15/2/26.
//

#include "ConfiguradorPartida.h"
#include <iostream>
#include <string>

ConfiguradorPartida::ConfiguradorPartida() {}

static int leerEntero(int min, int max) {
    int valor;
    while (true) {
        std::cin >> valor;
        if (std::cin.fail() || valor < min || valor > max) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Es una entrada invalida. Ingresa un numero entre " << min << " y " << max << ": ";
        } else {
            std::cin.ignore(10000, '\n');
            return valor;
        }
    }
}

void ConfiguradorPartida::configurarNuevaPartida() {
    int opcion;
    std::cout << "=== Configuracion Del Juego UNO ===\n";

    // 1. Configurar Regla
    std::cout << "¿Activar la acumulacion de cartas (+2, +4, etc)? (1: Si, 0: No): ";
    opcion = leerEntero(0, 1);
    reglas.setAcumulacion(opcion == 1);

    /* std::cout << "¿Activar reto de legalidad para +4? (1: Si, 0: No): ";
    std::cin >> opcion;
    reglas.setRetoMas4(opcion == 1); */

    std::cout << "¿Penalizacion por no decir UNO? (1: Si, 0: No): ";
    opcion = leerEntero(0, 1);
    reglas.setGritoUno(opcion == 1);

    std::cout << "¿DEsea activar la expansion UNO FLIP (Cartas de doble cara)? (1: Si, 0: No): ";
    opcion = leerEntero(0, 1);
    reglas.setExpansionFlip(opcion == 1);

    // 2. Configurar Jugadores
    int n;
    std::cout << "Ingrese un numero de jugadores (minimo 2): ";
    while (true) {
        std::cin >> n;
        if (std::cin.fail() || n < 2) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada invalida. Ingresa un numero mayor o igual a 2: ";
        } else {
            std::cin.ignore(10000, '\n');
            break;
        }
    }
    reglas.setNumJugadores(n);

    for (int i = 0; i < n; i++) {
        std::string nombre;
        std::cout << "Ingrese noombre del jugador " << (i + 1) << ": ";
        std::cin >> nombre;
        jugadores.insertar(new Jugador(nombre));
    }

    std::cout << "\nPartida configurada con " << reglas.getNumMazos() << " mazos!\n";
}

ReglasJuego ConfiguradorPartida::getReglas() const { return reglas; }
ListaCircular<Jugador*> ConfiguradorPartida::getJugadores() const { return jugadores; }