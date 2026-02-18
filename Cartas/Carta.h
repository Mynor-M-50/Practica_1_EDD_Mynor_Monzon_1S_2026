#ifndef CARTA_H
#define CARTA_H

#include <string>

enum Color { ROJO, AMARILLO, AZUL, VERDE, NEGRO, ROSA, TURQUESA, NARANJA, VIOLETA, NINGUNO };

class Carta {
protected:
    Color colorClaro;
    Color colorOscuro;
    bool esLadoOscuro;
    std::string tipo;

public:
    Carta(Color claro, Color oscuro, std::string tipo);
    virtual ~Carta() {}

    virtual void mostrar() const = 0;
    virtual bool esJugable(Carta* otra, bool acumulacionActiva) const = 0;

    Color getColorActual() const;
    std::string getTipo() const;
    bool getEsLadoOscuro() const;
    void setLado(bool oscuro);
};

#endif