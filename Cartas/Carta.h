#ifndef CARTA_H
#define CARTA_H

#include <string>

// Enums para lógica interna
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

    // Getters comunes
    Color getColorActual() const;
    std::string getTipoActual() const;
    bool getEsLadoOscuro() const;
    void setLado(bool oscuro);

    // Utilidad para colores en consola
    static std::string getColorANSI(Color c);
    static std::string getColorNombre(Color c);
    static std::string resetColor();
};

#endif