//
// Created by mynorm50 on 15/2/26.
//

#include "ReglasJuego.h"

ReglasJuego::ReglasJuego() {
    this->acumulacionActiva = true;
    this->retoMas4Activo = true;
    this->gritoUnoObligatorio = true;
    this->saltoTodosActivo = true;
    this->colorEternoActivo = true;

    this->numJugadores = 2;
    this->numMazos = 1;
    this->cartasIniciales = 7;

    this->modoOscuro = false;

    this->expansionFlipActiva = true; // la dejo por defecto activa
}

void ReglasJuego::setAcumulacion(bool valor) { acumulacionActiva = valor; }
bool ReglasJuego::getAcumulacion() const { return acumulacionActiva; }

void ReglasJuego::setRetoMas4(bool valor) { retoMas4Activo = valor; }
bool ReglasJuego::getRetoMas4() const { return retoMas4Activo; }

void ReglasJuego::setGritoUno(bool valor) { gritoUnoObligatorio = valor; }
bool ReglasJuego::getGritoUno() const { return gritoUnoObligatorio; }

void ReglasJuego::setSaltoTodos(bool valor) { saltoTodosActivo = valor; }
bool ReglasJuego::getSaltoTodos() const { return saltoTodosActivo; }

void ReglasJuego::setColorEterno(bool valor) { colorEternoActivo = valor; }
bool ReglasJuego::getColorEterno() const { return colorEternoActivo; }

void ReglasJuego::setNumJugadores(int n) {
    numJugadores = n;
    numMazos = ((n - 1) / 6) + 1;
}
int ReglasJuego::getNumJugadores() const { return numJugadores; }
int ReglasJuego::getNumMazos() const { return numMazos; }
int ReglasJuego::getCartasIniciales() const { return cartasIniciales; }

bool ReglasJuego::esModoOscuro() const { return modoOscuro; }
void ReglasJuego::conmutarModo() { modoOscuro = !modoOscuro; }

void ReglasJuego::setExpansionFlip(bool valor) { expansionFlipActiva = valor; }
bool ReglasJuego::getExpansionFlip() const { return expansionFlipActiva; }