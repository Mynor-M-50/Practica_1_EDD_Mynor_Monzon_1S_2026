//
// Created by mynorm50 on 15/2/26.
//

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

int getPesoColor(Color c) {
    switch(c) {
        case AZUL: case TURQUESA: return 1;
        case ROJO: case ROSA:     return 2;
        case VERDE: case VIOLETA: return 3;
        case AMARILLO: case NARANJA: return 4;
        case NEGRO:               return 5;
        default:                  return 6;
    }
}

void Jugador::ordenarMano() {
    int n = mano.getSize();
    if (n < 2) return;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= n - i; j++) {
            Carta* c1 = mano.getAt(j)->getValor();
            Carta* c2 = mano.getAt(j + 1)->getValor();

            bool intercambiar = false;

            //Comparar por peso de Color
            int p1 = getPesoColor(c1->getColorActual());
            int p2 = getPesoColor(c2->getColorActual());

            if (p1 > p2) {
                intercambiar = true;
            }
            // si son del mismo color, se compara por tipo/numero
            else if (p1 == p2) {
                if (c1->getTipoActual() > c2->getTipoActual()) {
                    intercambiar = true;
                }
            }

            if (intercambiar) {
                Nodo<Carta*>* n1 = mano.getAt(j);
                Nodo<Carta*>* n2 = mano.getAt(j + 1);
                Carta* aux = n1->getValor();
                n1->setValor(n2->getValor());
                n2->setValor(aux);
            }
        }
    }
}