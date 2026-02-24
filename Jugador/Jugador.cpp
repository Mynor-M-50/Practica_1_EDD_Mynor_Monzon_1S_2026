#include "Jugador.h"
#include <iostream>

Jugador::Jugador(std::string nombre) {
    this->nombre = nombre;
    this->dijoUno = false;
    this->activo = true;
}

std::string Jugador::getNombre() const { return nombre; }
void Jugador::setNombre(std::string nuevoNombre) { nombre = nuevoNombre; }

bool Jugador::getDijoUno() const { return dijoUno; }
void Jugador::setDijoUno(bool valor) { dijoUno = valor; }

bool Jugador::estaActivo() const { return activo; }
void Jugador::setActivo(bool valor) { activo = valor; }

int Jugador::getCantidadCartas() const {
    return mano.getSize();
}

void Jugador::agregarCarta(Carta* carta) {
    mano.insertarAlFinal(carta);
}

Carta* Jugador::jugarCartaEnPosicion(int posicion) {
    Nodo<Carta*>* nodo = mano.getAt(posicion);
    if (nodo != nullptr) {
        Carta* c = nodo->getValor();
        mano.deleteAt(posicion);
        return c;
    }
    return nullptr;
}

Carta* Jugador::verCartaEnPosicion(int posicion) {
    Nodo<Carta*>* nodo = mano.getAt(posicion);
    if (nodo != nullptr) {
        return nodo->getValor();
    }
    return nullptr;
}

void Jugador::mostrarMano() const {
    std::cout << "Mano de " << nombre << ":" << std::endl;
    for (int i = 1; i <= mano.getSize(); i++) {
        std::cout << i << ". ";
        mano.getAt(i)->getValor()->mostrar();
    }
}