#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* head;
    int size;

public:
    ListaEnlazada() : head(nullptr), size(0) {}

    ~ListaEnlazada() {
        while (!isEmpty()) {
            deleteFirst();
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    Nodo<T>* getHead() const {
        return head;
    }

    // Insertar al final
    void insertarAlFinal(const T& valor) {
        if (head == nullptr) {
            head = new Nodo<T>(valor);
        } else {
            Nodo<T>* actual = head;
            while (actual->getSiguiente() != nullptr) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(new Nodo<T>(valor));
        }
        size++;
    }

    // Insertar al inicio
    void insertarAlInicio(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        nuevo->setSiguiente(head);
        head = nuevo;
        size++;
    }

    // Eliminar primero
    void deleteFirst() {
        if (isEmpty()) return;

        Nodo<T>* temp = head;
        head = head->getSiguiente();
        delete temp;
        size--;
    }

    // Eliminar por posición
    void deleteAt(int position) {
        if (isEmpty() || position < 1 || position > size) return;

        if (position == 1) {
            deleteFirst();
            return;
        }

        Nodo<T>* anterior = head;
        int index = 1;
        while (index < position - 1) {
            anterior = anterior->getSiguiente();
            index++;
        }

        Nodo<T>* aEliminar = anterior->getSiguiente();
        anterior->setSiguiente(aEliminar->getSiguiente());
        delete aEliminar;
        size--;
    }

    // Obtener nodo en posición
    Nodo<T>* getAt(int position) const {
        if (position < 1 || position > size) return nullptr;

        Nodo<T>* actual = head;
        int index = 1;
        while (index < position) {
            actual = actual->getSiguiente();
            index++;
        }
        return actual;
    }

    // Búsqueda genérica usando un predicado (lambda)
    template <typename Predicado>
    Nodo<T>* buscar(Predicado pred) const {
        Nodo<T>* actual = head;
        while (actual != nullptr) {
            if (pred(actual->getValor())) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    // Solo para comprobar
    void imprimirDebug() const {
        Nodo<T>* actual = head;
        while (actual != nullptr) {
            std::cout << actual->getValor() << " -> ";
            actual = actual->getSiguiente();
        }
        std::cout << "NULL\n";
    }
};

#endif // LISTA_ENLAZADA_H