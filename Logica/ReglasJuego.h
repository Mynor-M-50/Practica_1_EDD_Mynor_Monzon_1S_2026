//
// Created by mynorm50 on 15/2/26.
//

#ifndef REGLAS_JUEGO_H
#define REGLAS_JUEGO_H

class ReglasJuego {
private:
    // flags de juego
    bool acumulacionActiva;
    bool retoMas4Activo;
    bool gritoUnoObligatorio;
    bool saltoTodosActivo;
    bool colorEternoActivo;
    bool expansionFlipActiva;

    // configuracion
    int numJugadores;
    int numMazos;
    int cartasIniciales;

    // estado del jueego
    bool modoOscuro;

public:
    ReglasJuego();

    void setAcumulacion(bool valor);
    bool getAcumulacion() const;

    void setRetoMas4(bool valor);
    bool getRetoMas4() const;

    void setGritoUno(bool valor);
    bool getGritoUno() const;

    void setSaltoTodos(bool valor);
    bool getSaltoTodos() const;

    void setColorEterno(bool valor);
    bool getColorEterno() const;

    void setNumJugadores(int n);
    int getNumJugadores() const;
    int getNumMazos() const;
    int getCartasIniciales() const;

    bool esModoOscuro() const;
    void conmutarModo();

    void setExpansionFlip(bool valor);
    bool getExpansionFlip() const;
};

#endif