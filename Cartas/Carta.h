//
// Created by mynorm50 on 10/2/26.
//

#ifndef CARTA_H
#define CARTA_H

#include <string>

enum Color { ROJO, AMARILLO, AZUL, VERDE, ROSA, TURQUESA, NARANJA, VIOLETA, NEGRO, NINGUNO };

class Carta {
protected:
    Color colorClaro;
    Color colorOscuro;
    std::string tipoClaro;
    std::string tipoOscuro;
    bool esLadoOscuro;

public:
    Carta(Color cClaro, std::string tClaro, Color cOscuro, std::string tOscuro);
    virtual ~Carta() {}

    virtual void mostrar() const = 0;
    virtual bool esJugable(Carta* otra, bool acumulacionActiva) const = 0;

    // getters
    Color getColorActual() const;
    std::string getTipoActual() const;
    bool getEsLadoOscuro() const;
    void setLado(bool oscuro);

    // Utilidad para mis colores en la consola
    static std::string getColorANSI(Color c);
    static std::string getColorNombre(Color c);
    static std::string resetColor();
};

#endif