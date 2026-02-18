#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "../estructuras/ListaEnlazada.h"
#include "../cartas/Carta.h"

using namespace std; // Para no usar std:: cada vez

class Jugador {
private:
    string nombre;
    ListaEnlazada<Carta*> mano; // Mi propia estructura
    bool dijoUno;
    bool activo;

public:
    Jugador(string nombre);

    string getNombre();
    void setNombre(string nuevoNombre);

    bool getDijoUno();
    void setDijoUno(bool valor);

    bool estaActivo();
    void setActivo(bool valor);

    int getCantidadCartas();

    // Métodos de la mano
    void agregarCarta(Carta* carta);
    Carta* jugarCartaEnPosicion(int posicion);
    Carta* verCartaEnPosicion(int posicion);

    // Lógica
    bool tieneCartaJugable(Carta* cartaEnMesa, bool acumulacionActiva);

    void mostrarMano();
};

#endif