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

        // Cartas Numericas
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaNumero(coloresClaro[i], 0, coloresOscuro[i], 1));
            for (int n = 1; n <= 9; n++) {
                mazo.push(new CartaNumero(coloresClaro[i], n, coloresOscuro[i], n));
                mazo.push(new CartaNumero(coloresClaro[i], n, coloresOscuro[i], n));
            }
        }

        // Cartas de Accion
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaAccion(coloresClaro[i], "Salto",   coloresOscuro[i], "SaltoTodos"));
            mazo.push(new CartaAccion(coloresClaro[i], "Salto",   coloresOscuro[i], "SaltoTodos"));
            mazo.push(new CartaAccion(coloresClaro[i], "Reversa", coloresOscuro[i], "Reversa"));
            mazo.push(new CartaAccion(coloresClaro[i], "Reversa", coloresOscuro[i], "Reversa"));
            mazo.push(new CartaAccion(coloresClaro[i], "Mas1",    coloresOscuro[i], "Mas3"));
            mazo.push(new CartaAccion(coloresClaro[i], "Mas1",    coloresOscuro[i], "Mas3"));
        }

        // Cartas Negras
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaNegra("Comodin", "ColorEterno"));
            mazo.push(new CartaNegra("Mas2",    "Mas6"));
        }

        // Cartas Portal
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaFlip(coloresClaro[i], coloresOscuro[i]));
            mazo.push(new CartaFlip(coloresClaro[i], coloresOscuro[i]));
        }

        // Cartas Personalizadas
        for (int i = 0; i < 4; i++) {
            mazo.push(new CartaPersonalizada());
        }
    }

    std::cout << "Mazo generado con " << mazo.getSize() << " cartas." << std::endl;
}

void MotorJuego::barajarMazo() {
    // 1. Pasamos todo de la Pila a tu ListaEnlazada
    ListaEnlazada<Carta*> temp;
    while (!mazo.isEmpty()) {
        temp.insertarAlFinal(mazo.pop());
    }

    int n = temp.getSize();
    if (n < 2) return;

    // 2. Barajamos intercambiando solo los VALORES (punteros a carta)
    // Hacemos unas 200 pasadas para que quede bien mezclado
    for (int i = 0; i < 200; i++) {
        int pos1 = (rand() % n) + 1;
        int pos2 = (rand() % n) + 1;

        if (pos1 != pos2) {
            Nodo<Carta*>* nodo1 = temp.getAt(pos1);
            Nodo<Carta*>* nodo2 = temp.getAt(pos2);

            if (nodo1 != nullptr && nodo2 != nullptr) {
                // Intercambiamos las cartas, NO los nodos
                Carta* aux = nodo1->getValor();
                nodo1->setValor(nodo2->getValor());
                nodo2->setValor(aux);
            }
        }
    }

    // 3. Metemos las cartas de vuelta a la Pila
    for (int i = 1; i <= n; i++) {
        mazo.push(temp.getAt(i)->getValor());
    }

    std::cout << "✅ Mazo barajado con exito." << std::endl;
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

    // Primera carta del descarte (si es negra o Portal, buscar la primera válida)
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
        // Caso extremo: todas las cartas son negras/portal, usar la primera de todas formas
        if (primera != nullptr) descarte.push(primera);
    }

    // Devolver las cartas descartadas al fondo del mazo
    for (int i = temporales.getSize(); i >= 1; i--) {
        // Las metemos al final pasando por lista temporal inversa
    }
    // Reinsertar en orden correcto
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
    std::cout << "----------------------------------------" << std::endl;

    jugadores.getActual()->getValor()->mostrarMano();
}

void MotorJuego::ejecutarTurno(Jugador* jugador) {
    std::cout << "\nTurno de: " << jugador->getNombre() << std::endl;

    if (acumulacionActiva) {
        std::cout << "Hay " << cartasAcumuladas
            << " cartas acumuladas. Acumula o roba (0)." << std::endl;
    }

    int opcion;
    std::cout << "Elige carta (1-" << jugador->getCantidadCartas() << ") o 0 para robar: ";
    std::cin >> opcion;

    if (opcion == 0) {
        // Robar
        if (acumulacionActiva) {
            for (int i = 0; i < cartasAcumuladas; i++) {
                Carta* robada = mazo.pop();
                if (robada) robada->setLado(modoOscuro);
                jugador->agregarCarta(robada);
            }
            acumulacionActiva = false;
            cartasAcumuladas = 0;
            std::cout << jugador->getNombre() << " robo las cartas acumuladas." << std::endl;
        } else {
            Carta* robada = mazo.pop();
            if (robada) robada->setLado(modoOscuro);
            jugador->agregarCarta(robada);
            std::cout << jugador->getNombre() << " robo una carta." << std::endl;
        }

    } else if (opcion >= 1 && opcion <= jugador->getCantidadCartas()) {
        Carta* elegida = jugador->jugarCartaEnPosicion(opcion);
        Carta* enMesa  = descarte.peek();

        if (ValidadorFlip::esJugadaValida(elegida, enMesa, reglas, acumulacionActiva)) {
            descarte.push(elegida);
            aplicarEfecto(elegida, jugador);
        } else {
            std::cout << "Jugada no valida. Robas una carta." << std::endl;
            jugador->agregarCarta(elegida);
            jugador->agregarCarta(mazo.pop());
        }
    } else {
        std::cout << "Opcion invalida. Pierdes tu turno." << std::endl;
    }
}

void MotorJuego::aplicarEfecto(Carta* carta, Jugador* jugadorActual) {
    std::string tipo = carta->getTipoActual();

    if (tipo == "Salto") {
        std::cout << "Salto! El siguiente jugador pierde su turno." << std::endl;
        siguienteTurno();

    } else if (tipo == "SaltoTodos") {
        std::cout << "Salto a TODOS! Vuelves a jugar." << std::endl;
        // No avanzamos, el mismo jugador repite

    } else if (tipo == "Reversa") {
        sentidoHorario = !sentidoHorario;
        std::cout << "Reversa! Cambia la direccion." << std::endl;

    } else if (tipo == "Mas1" || tipo == "Mas2" || tipo == "Mas3" || tipo == "Mas6") {
        int cantidad = 0;
        if      (tipo == "Mas1") cantidad = 1;
        else if (tipo == "Mas2") cantidad = 2;
        else if (tipo == "Mas3") cantidad = 3;
        else if (tipo == "Mas6") cantidad = 6;

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

    } else if (tipo == "Comodin" || tipo == "ColorEterno") {
        std::cout << "Elige un color:" << std::endl;
        if (!modoOscuro) {
            std::cout << "1. Rojo  2. Amarillo  3. Azul  4. Verde" << std::endl;
        } else {
            std::cout << "1. Rosa  2. Turquesa  3. Naranja  4. Violeta" << std::endl;
        }
        int c; std::cin >> c;
        if (c < 1 || c > 4) c = 1;

        CartaNegra* negra = dynamic_cast<CartaNegra*>(carta);
        if (negra != nullptr) {
            Color claro[]  = { ROJO, AMARILLO, AZUL, VERDE };
            Color oscuro[] = { ROSA, TURQUESA, NARANJA, VIOLETA };
            negra->setColorElegido(modoOscuro ? oscuro[c-1] : claro[c-1]);
        }

    } else if (tipo == "Portal") {
        voltearJuego();

    } else if (tipo == "PistolaLaser" || tipo == "CanonLaser") {
        CartaPersonalizada* p = dynamic_cast<CartaPersonalizada*>(carta);
        if (p == nullptr) return;

        if (!modoOscuro) {
            // Lado Claro: 7 cartas a un jugador
            Jugador* objetivo = elegirJugador();
            for (int i = 0; i < 7; i++) {
                Carta* robada = mazo.pop();
                if (robada) robada->setLado(modoOscuro);
                objetivo->agregarCarta(robada);
            }
            std::cout << objetivo->getNombre() << " roba 7 cartas (Pistola Laser)." << std::endl;

            std::cout << "Elige color (1.Rojo 2.Amarillo 3.Azul 4.Verde): ";
            int c; std::cin >> c;
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
                        Carta* robada = mazo.pop();
                        if (robada) robada->setLado(modoOscuro);
                        jug->agregarCarta(robada);
                    }
                }
                jugadores.avanzar();
            }

            std::cout << "Elige color (1.Rosa 2.Turquesa 3.Naranja 4.Violeta): ";
            int c; std::cin >> c;
            if (c < 1 || c > 4) c = 1;
            Color oscuro[] = { ROSA, TURQUESA, NARANJA, VIOLETA };
            p->setColorElegido(oscuro[c-1]);
        }
    }
}

void MotorJuego::voltearJuego() {
    modoOscuro = !modoOscuro;
    reglas.conmutarModo();

    // 1) Voltear MAZO
    for (Nodo<Carta*>* n = mazo.getTop(); n != nullptr; n = n->getSiguiente()) {
        if (n->getValor() != nullptr) n->getValor()->setLado(modoOscuro);
    }

    // 2) Voltear DESCARTE
    for (Nodo<Carta*>* n = descarte.getTop(); n != nullptr; n = n->getSiguiente()) {
        if (n->getValor() != nullptr) n->getValor()->setLado(modoOscuro);
    }

    // 3) Voltear MANOS de todos los jugadores
    Nodo<Jugador*>* jn = jugadores.getHead();
    int total = reglas.getNumJugadores();

    for (int i = 0; i < total; i++) {
        Jugador* j = jn->getValor();
        // Recorremos la lista enlazada interna "mano" mediante verCartaEnPosicion
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
    std::cin >> opcion;
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