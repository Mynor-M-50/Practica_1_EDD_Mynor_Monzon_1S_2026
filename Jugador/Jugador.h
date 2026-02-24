#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "../Estructuras/ListaEnlazada.h"
#include "../Cartas/Carta.h"

class Jugador {
private:
    std::string nombre;
    ListaEnlazada<Carta*> mano;
    bool dijoUno;
    bool activo;

public:
    Jugador(std::string nombre);

    std::string getNombre() const;
    void setNombre(std::string nuevoNombre);

    bool getDijoUno() const;
    void setDijoUno(bool valor);

    bool estaActivo() const;
    void setActivo(bool valor);

    int getCantidadCartas() const;

    // Métodos de la mano
    void agregarCarta(Carta* carta);
    Carta* jugarCartaEnPosicion(int posicion);
    Carta* verCartaEnPosicion(int posicion);

    // Lógica
    void mostrarMano() const;
};

#endif