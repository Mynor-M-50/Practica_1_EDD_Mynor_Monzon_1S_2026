//
// Created by mynorm50 on 15/2/26.
//

#include "MotorJuego.h"
#include "../Cartas/CartaNumero.h"
#include "../Cartas/CartaAccion.h"
#include "../Cartas/CartaNegra.h"
#include "../Cartas/CartaFlip.h"
#include "../Cartas/Personalizadas/CartaPersonalizada.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

MotorJuego::MotorJuego(ReglasJuego reglas, ListaCircular<Jugador*>& jugadores) {
    this->reglas = reglas;
    this->jugadores = jugadores;  // Ahora NO es copia peligrosa
    this->juegoActivo = false;
    this->sentidoHorario = true;
    this->acumulacionActiva = false;
    this->cartasAcumuladas = 0;
    this->modoOscuro = false;
}

static int leerEntero(int min, int max) {
    int valor;
    while (true) {
        std::cin >> valor;
        if (std::cin.fail() || valor < min || valor > max) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada invalida. Ingresa un numero entre " << min << " y " << max << ": ";
        } else {
            std::cin.ignore(10000, '\n');
            return valor;
        }
    }
}

void MotorJuego::iniciarJuego() {
    srand(time(nullptr));

    generarMazo();
    barajarMazo();
    repartirCartas();

    juegoActivo = true;

    std::cout << "\n========================================" << std::endl;
    std::cout << "         ¡El juego ha comenzado!        " << std::endl;
    std::cout << "========================================" << std::endl;

    while (juegoActivo) {
        Jugador* actual = jugadores.getActual()->getValor();
        mostrarEstado();
        ejecutarTurno(actual);

        if (actual->getCantidadCartas() == 0) {
            std::cout << "\n¡" << actual->getNombre() << " ha ganado! ¡UNO!" << std::endl;
            juegoActivo = false;
        } else {
            siguienteTurno();
        }
    }
}

void MotorJuego::generarMazo() {
    Color coloresClaro[]  = { ROJO, AMARILLO, AZUL, VERDE };
    Color coloresOscuro[] = { ROSA, TURQUESA, NARANJA, VIOLETA };

    for (int m = 0; m < reglas.getNumMazos(); m++) {
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaNumero(coloresClaro[i], 0, coloresOscuro[i], 0));
            for (int n = 1; n <= 9; n++) {
                mazo.push(new CartaNumero(coloresClaro[i], n, coloresOscuro[i], n));
                if (n <= 7) { // 1-7 dos veces, 8-9 solo una vez
                    mazo.push(new CartaNumero(coloresClaro[i], n, coloresOscuro[i], n));
                }
            }
        }
        // Cartas de Accion
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaAccion(coloresClaro[i], "Salto",        coloresOscuro[i], "Salto a Todos"));
            mazo.push(new CartaAccion(coloresClaro[i], "Salto",        coloresOscuro[i], "Salto a Todos"));
            mazo.push(new CartaAccion(coloresClaro[i], "Reversa",      coloresOscuro[i], "Reversa"));
            mazo.push(new CartaAccion(coloresClaro[i], "Reversa",      coloresOscuro[i], "Reversa"));
            mazo.push(new CartaAccion(coloresClaro[i], "Mas 1 (+1)",   coloresOscuro[i], "Mas 3 (+3)"));
            mazo.push(new CartaAccion(coloresClaro[i], "Mas 1 (+1)",   coloresOscuro[i], "Mas 3 (+3)"));
        }

        // Cartas Negras
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaNegra("Comodin de Color", "ColorEterno"));
            mazo.push(new CartaNegra("Mas 2 (+2)",       "Mas 6 (+6)"));
        }

        // Cartas Portal / Flip
        if (reglas.getExpansionFlip()) {
            for (int i = 0; i < 4; i++) {
                mazo.push(new CartaFlip(coloresClaro[i], coloresOscuro[i]));
            }
        } else {
            // Sin Flip: agregamos 4 numericas extra
            for (int i = 0; i < 4; i++) {
                mazo.push(new CartaNumero(coloresClaro[i], 8, coloresOscuro[i], 8));
            }
        }

        // Cartas Personalizadas
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaPersonalizada());
        }
    }

    std::cout << "Mazo generado con " << mazo.getSize() << " cartas." << std::endl;
}

void MotorJuego::barajarMazo() {
    ListaEnlazada<Carta*> temp;
    while (!mazo.isEmpty()) {
        temp.insertarAlFinal(mazo.pop());
    }

    int n = temp.getSize();
    if (n < 2) return;

    /* Barajamos intercambiando solo los VALORES (punteros a carta)
    y hacemos unas 200 pasadas para que quede bien mezclado */

    for (int i = 0; i < 200; i++) {
        int pos1 = (rand() % n) + 1;
        int pos2 = (rand() % n) + 1;

        if (pos1 != pos2) {
            Nodo<Carta*>* nodo1 = temp.getAt(pos1);
            Nodo<Carta*>* nodo2 = temp.getAt(pos2);

            if (nodo1 != nullptr && nodo2 != nullptr) {
                // Intercambiamos las cartas sin intercambiar nodo
                Carta* aux = nodo1->getValor();
                nodo1->setValor(nodo2->getValor());
                nodo2->setValor(aux);
            }
        }
    }

    // metemos las cartas de vuelta a la Pila
    for (int i = 1; i <= n; i++) {
        mazo.push(temp.getAt(i)->getValor());
    }

    std::cout << "Mazo barajado con exito." << std::endl;
}

void MotorJuego::repartirCartas() {
    int cartasIniciales = reglas.getCartasIniciales();
    int totalJugadores  = reglas.getNumJugadores();

    for (int c = 0; c < cartasIniciales; c++) {
        for (int j = 0; j < totalJugadores; j++) {
            Jugador* jugador = jugadores.getActual()->getValor();
            jugador->agregarCarta(mazo.pop());
            jugadores.avanzar();
        }
    }

    // primera carta del descarte (si es negra o Portal, buscar la primera que pueda ser aceptada)
    ListaEnlazada<Carta*> temporales;
    Carta* primera = mazo.pop();

    while (primera != nullptr &&
        (primera->getColorActual() == NEGRO || primera->getTipoActual() == "Portal")) {
        temporales.insertarAlFinal(primera);
        if (mazo.isEmpty()) break;
        primera = mazo.pop();
    }

    if (primera != nullptr && primera->getColorActual() != NEGRO && primera->getTipoActual() != "Portal") {
        descarte.push(primera);
    } else {
        // un Caso extremo: todas las cartas son negras/portal, usar la primera de todas formas
        if (primera != nullptr) descarte.push(primera);
    }

    // devolver las cartas descartadas al fondo del mazo
    for (int i = temporales.getSize(); i >= 1; i--) {
        // Las metemos al final pasando por lista temporal inversa
    }
    // Re insertar en orden correcto
    Nodo<Carta*>* t = temporales.getHead();
    while (t != nullptr) {
        mazo.push(t->getValor());
        t = t->getSiguiente();
    }

    std::cout << "Cartas repartidas." << std::endl;
}

void MotorJuego::mostrarEstado() {
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Carta en mesa: ";
    descarte.peek()->mostrar();
    std::cout << "Modo: " << (modoOscuro ? "OSCURO" : "CLARO") << std::endl;
    std::cout << "Mazo: [" << mazo.getSize() << " cartas] | ";
    std::cout << "Descarte: [" << descarte.getSize() << " cartas]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    Jugador* actual = jugadores.getActual()->getValor();
    actual->ordenarMano();
    actual->mostrarMano();
}

void MotorJuego::ejecutarTurno(Jugador* jugador) {
    std::cout << "\nTurno de: " << jugador->getNombre() << std::endl;
    jugador->setDijoUno(false);

    if (acumulacionActiva) {
        std::cout << "Hay " << cartasAcumuladas
            << " cartas acumuladas. Acumula o roba (0)." << std::endl;
    }

    bool turnoTerminado = false;
    while (!turnoTerminado) {
        int opcion;
        std::cout << "Elige carta (1-" << jugador->getCantidadCartas() << ") o 0 para robar: ";
        opcion = leerEntero(0, jugador->getCantidadCartas());

        if (opcion == 0) {
            // robar manualmente
            if (acumulacionActiva) {
                for (int i = 0; i < cartasAcumuladas; i++) {
                    if (mazo.isEmpty()) reponerMazo();
                    Carta* robada = mazo.pop();
                    if (robada) robada->setLado(modoOscuro);
                    jugador->agregarCarta(robada);
                }
                acumulacionActiva = false;
                cartasAcumuladas = 0;
                std::cout << jugador->getNombre() << " robo las cartas acumuladas." << std::endl;
            } else {
                if (mazo.isEmpty()) reponerMazo();
                Carta* robada = mazo.pop();
                if (robada) robada->setLado(modoOscuro);
                jugador->agregarCarta(robada);
                std::cout << jugador->getNombre() << " robo una carta." << std::endl;
            }
            turnoTerminado = true;

        } else if (opcion >= 1 && opcion <= jugador->getCantidadCartas()) {
            Carta* elegida = jugador->jugarCartaEnPosicion(opcion);
            Carta* enMesa  = descarte.peek();

            if (ValidadorFlip::esJugadaValida(elegida, enMesa, reglas, acumulacionActiva)) {
                descarte.push(elegida);
                aplicarEfecto(elegida, jugador);

                if (jugador->getCantidadCartas() == 1) {
                    int opcionUno;
                    std::cout << jugador->getNombre() << ", tienes UNA carta. Quieres gritar UNO? (1 = Si / 2 = No): ";
                    opcionUno = leerEntero(1, 2);
                    if (opcionUno == 1) {
                        jugador->setDijoUno(true);
                        std::cout << "¡" << jugador->getNombre() << " grito UNO!\n";
                    }
                }

                turnoTerminado = true;
            } else {
                // Carta no válida: regresa a la mano, el jugador vuelve a elegir
                std::cout << " Jugada no valida, elige otra carta o presiona 0 para robar." << std::endl;
                jugador->agregarCarta(elegida);
            }
        } else {
            std::cout << "Opcion no valida, intenta de nuevo." << std::endl;
        }
    }
    if (jugador->getCantidadCartas() == 1 && !jugador->getDijoUno()) {
        std::cout << jugador->getNombre() << " no dijo UNO. Roba 2 cartas como penalizacion.\n";
        for (int i = 0; i < 2; i++) {
            if (mazo.isEmpty()) reponerMazo();
            Carta* p = mazo.pop();
            if (p) {
                p->setLado(modoOscuro);
                jugador->agregarCarta(p);
            }
        }
    }
}

void MotorJuego::aplicarEfecto(Carta* carta, Jugador* jugadorActual) {
    std::string tipo = carta->getTipoActual();

    if (tipo == "Salto") {
        std::cout << "Salto! - El siguiente jugador pierde su turno." << std::endl;
        siguienteTurno();

    } else if (tipo == "Salto a Todos") {
        std::cout << "Salto a TODOS! - Vuelves a jugar." << std::endl;
        // No avanzamos

    } else if (tipo == "Reversa") {
        sentidoHorario = !sentidoHorario;
        std::cout << "Reversa! - Cambia la direccion." << std::endl;

    } else if (tipo == "Mas 1 (+1)" || tipo == "Mas 2 (+2)" || tipo == "Mas 3 (+3)" || tipo == "Mas 6 (+6)") {
        int cantidad = 0;
        if      (tipo == "Mas 1 (+1)") cantidad = 1;
        else if (tipo == "Mas 2 (+2)") cantidad = 2;
        else if (tipo == "Mas 3 (+3)") cantidad = 3;
        else if (tipo == "Mas 6 (+6)") cantidad = 6;

        if (reglas.getAcumulacion()) {
            acumulacionActiva = true;
            cartasAcumuladas += cantidad;
            std::cout << "Acumulacion activa: " << cartasAcumuladas << " cartas." << std::endl;
        } else {
            siguienteTurno();
            Jugador* siguiente = jugadores.getActual()->getValor();
            for (int i = 0; i < cantidad; i++) {
                Carta* robada = mazo.pop();
                if (robada) robada->setLado(modoOscuro);
                siguiente->agregarCarta(robada);
            }
            std::cout << siguiente->getNombre() << " roba " << cantidad << " cartas." << std::endl;
        }

    } else if (tipo == "Comodin de Color" || tipo == "ColorEterno") {
        std::cout << "Elige un color:" << std::endl;
        if (!modoOscuro) {
            std::cout << "1. Rojo  2. Amarillo  3. Azul  4. Verde" << std::endl;
        } else {
            std::cout << "1. Rosa  2. Turquesa  3. Naranja  4. Violeta" << std::endl;
        }

        int c = leerEntero(1, 4);
        Color claro[]  = { ROJO, AMARILLO, AZUL, VERDE };
        Color oscuro[] = { ROSA, TURQUESA, NARANJA, VIOLETA };
        Color elegido = modoOscuro ? oscuro[c-1] : claro[c-1];

        CartaNegra* negra = dynamic_cast<CartaNegra*>(carta);
        if (negra != nullptr) {
            negra->setColorElegido(elegido);
        }

        // Lógica especial del color eterno
        if (modoOscuro && tipo == "ColorEterno") {
            siguienteTurno();
            Jugador* victima = jugadores.getActual()->getValor();
            std::cout << victima->getNombre() << " debe robar hasta encontrar el color elegido..." << std::endl;

            bool encontrado = false;
            while (!encontrado) {
                if (mazo.isEmpty()) reponerMazo();
                Carta* robada = mazo.pop();
                if (robada) {
                    robada->setLado(modoOscuro);
                    victima->agregarCarta(robada);
                    // Si la carta robada tiene el color que eligió el jugador anterior, para.
                    if (robada->getColorActual() == elegido) {
                        encontrado = true;
                        std::cout << "¡Encontro una carta " << (c==1?"Rosa":c==2?"Turquesa":c==3?"Naranja":"Violeta") << "!" << std::endl;
                    }
                } else {
                    break;
                }
            }
        }

    } else if (tipo == "Portal") {
        if (reglas.getExpansionFlip()) {
            voltearJuego();
            std::cout << "¡El juego ha sido volteado al lado Oscuro!\n";
        } else {
            std::cout << "Carta Portal jugada, pero la expansion FLIP esta desactivada.\n";
        }

    } else if (tipo == "PistolaLaser" || tipo == "CanonLaser") {
        CartaPersonalizada* p = dynamic_cast<CartaPersonalizada*>(carta);
        if (p == nullptr) return;

        if (!modoOscuro) {
            // Lado Claro: 7 cartas a un jugador
            Jugador* objetivo = elegirJugador();
            for (int i = 0; i < 7; i++) {
                if (mazo.isEmpty()) reponerMazo();
                Carta* robada = mazo.pop();
                if (robada) robada->setLado(modoOscuro);
                objetivo->agregarCarta(robada);
            }
            std::cout << objetivo->getNombre() << " roba 7 cartas (Pistola Laser)." << std::endl;

            std::cout << "Elige color (1.Rojo 2.Amarillo 3.Azul 4.Verde): ";
            int c;
            c = leerEntero(1, 4);
            if (c < 1 || c > 4) c = 1;
            Color claro[] = { ROJO, AMARILLO, AZUL, VERDE };
            p->setColorElegido(claro[c-1]);

        } else {
            // Lado Oscuro: 5 cartas a todos
            std::cout << "Canon Laser! Todos roban 5 cartas." << std::endl;
            int total = reglas.getNumJugadores();
            for (int j = 0; j < total; j++) {
                Jugador* jug = jugadores.getActual()->getValor();
                if (jug != jugadorActual) {
                    for (int i = 0; i < 5; i++) {
                        if (mazo.isEmpty()) reponerMazo();
                        Carta* robada = mazo.pop();
                        if (robada) robada->setLado(modoOscuro);
                        jug->agregarCarta(robada);
                    }
                }
                jugadores.avanzar();
            }

            std::cout << "Elige color (1.Rosa 2.Turquesa 3.Naranja 4.Violeta): ";
            int c;
            c = leerEntero(1, 4);
            if (c < 1 || c > 4) c = 1;
            Color oscuro[] = { ROSA, TURQUESA, NARANJA, VIOLETA };
            p->setColorElegido(oscuro[c-1]);
        }
    }
}

void MotorJuego::voltearJuego() {
    modoOscuro = !modoOscuro;
    reglas.conmutarModo();

    // Voltear Mazo
    for (Nodo<Carta*>* n = mazo.getTop(); n != nullptr; n = n->getSiguiente()) {
        if (n->getValor() != nullptr) n->getValor()->setLado(modoOscuro);
    }

    // Voltear descarte
    for (Nodo<Carta*>* n = descarte.getTop(); n != nullptr; n = n->getSiguiente()) {
        if (n->getValor() != nullptr) n->getValor()->setLado(modoOscuro);
    }

    // Voltear manos de todos los jugadores
    Nodo<Jugador*>* jn = jugadores.getHead();
    int total = reglas.getNumJugadores();

    for (int i = 0; i < total; i++) {
        Jugador* j = jn->getValor();
        // recorremos la lista enlazada interna "mano" mediante verCartaEnPosicion
        for (int k = 1; k <= j->getCantidadCartas(); k++) {
            Carta* c = j->verCartaEnPosicion(k);
            if (c != nullptr) c->setLado(modoOscuro);
        }
        jn = jn->getSiguiente();
    }

    std::cout << "PORTAL! El juego cambia a modo "
        << (modoOscuro ? "OSCURO" : "CLARO") << std::endl;
}

Jugador* MotorJuego::elegirJugador() {
    std::cout << "Elige un jugador objetivo:" << std::endl;
    int total = reglas.getNumJugadores();

    // Mostramos todos los jugadores desde el head
    Nodo<Jugador*>* temp = jugadores.getHead();
    for (int i = 0; i < total; i++) {
        std::cout << i + 1 << ". " << temp->getValor()->getNombre() << std::endl;
        temp = temp->getSiguiente();
    }

    int opcion;
    opcion = leerEntero(1, total);
    if (opcion < 1 || opcion > total) opcion = 1;

    temp = jugadores.getHead();
    for (int i = 0; i < opcion - 1; i++) {
        temp = temp->getSiguiente();
    }
    return temp->getValor();
}

void MotorJuego::siguienteTurno() {
    if (sentidoHorario) {
        jugadores.avanzar();
    } else {
        jugadores.retroceder();
    }
}

void MotorJuego::reponerMazo() {
    if (descarte.getSize() <= 1) {
        std::cout << "¡ALERTA! No hay mas cartas en el descarte para reponer el mazo." << std::endl;
        return;
    }

    std::cout << "--- Reponiendo mazo desde el descarte... ---" << std::endl;

    // Guardamos la carta de arriba (la que está en juego)
    Carta* cartaEnJuego = descarte.pop();

    // pasamos lo del descarte al mazo
    while (!descarte.isEmpty()) {
        Carta* c = descarte.pop();
        //si la carta era un Comodín/Negra, reseteamos su color elegido
        CartaNegra* negra = dynamic_cast<CartaNegra*>(c);
        if (negra) negra->setColorElegido(NEGRO);

        mazo.push(c);
    }

    // devolvemos la carta en juego al descarte
    descarte.push(cartaEnJuego);

    // barajamos el nuev mazo
    barajarMazo();
}