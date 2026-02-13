cmake_minimum_required(VERSION 4.1)
project(Practica_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Practica_1
        main.cpp
        Configuracion/ConfiguradorPartida.cpp
        Configuracion/ConfiguradorPartida.h
        Estructuras/Nodo.cpp
        Estructuras/Nodo.h
        Estructuras/Pila.cpp
        Estructuras/Pila.h
        Estructuras/ListaEnlazada.cpp
        Estructuras/ListaEnlazada.h
        Estructuras/ListaCircular.cpp
        Estructuras/ListaCircular.h
        Jugador/Jugador.cpp
        Jugador/Jugador.h
        Logica/ReglasJuego.cpp
        Logica/ReglasJuego.h
        Logica/ValidadorFlip.cpp
        Logica/ValidadorFlip.h
        Motor/MotorJuego.cpp
        Motor/MotorJuego.h
        Cartas/Carta.cpp
        Cartas/Carta.h
        Cartas/CartaNumero.cpp
        Cartas/CartaNumero.h
        Cartas/CartaAccion.cpp
        Cartas/CartaAccion.h
        Cartas/CartaNegra.cpp
        Cartas/CartaNegra.h
        Cartas/CartaFlip.cpp
        Cartas/CartaFlip.h
        Cartas/Personalizadas/CartaPersonalizada1.cpp
        Cartas/Personalizadas/CartaPersonalizada1.h
        Cartas/Personalizadas/CartaPersonalizada2.cpp
        Cartas/Personalizadas/CartaPersonalizada2.h)
