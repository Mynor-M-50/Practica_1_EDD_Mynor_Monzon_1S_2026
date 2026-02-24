#ifndef REGLAS_JUEGO_H
#define REGLAS_JUEGO_H

class ReglasJuego {
private:
    // --- Flags de Jugabilidad ---
    bool acumulacionActiva;
    bool retoMas4Activo;
    bool gritoUnoObligatorio;
    bool saltoTodosActivo;
    bool colorEternoActivo;

    // --- Configuración de Partida ---
    int numJugadores;
    int numMazos;
    int cartasIniciales;

    // --- Estado Global del Juego ---
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

    void setNumJugadores(int n); // Calcula numMazos automáticamente
    int getNumJugadores() const;
    int getNumMazos() const;
    int getCartasIniciales() const;

    bool esModoOscuro() const;
    void conmutarModo();
};

#endif