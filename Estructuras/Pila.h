// estructuras/Pila.h
#ifndef PILA_H
#define PILA_H

#include "Nodo.h"

template <typename T>
class Pila {
private:
    Nodo<T>* top;
    int size;

public:
    Pila() : top(nullptr), size(0) {}

    ~Pila() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int getSize() const {
        return size;
    }

    void push(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        nuevo->setSiguiente(top);
        top = nuevo;
        size++;
    }

    T pop() {
        if (isEmpty()) return T();

        Nodo<T>* temp = top;
        T valor = temp->getValor();
        top = top->getSiguiente();
        delete temp;
        size--;
        return valor;
    }

    T peek() const {
        return top->getValor();
    }

    Nodo<T>* getTop() const {
        return top;
    }
};

#endif // PILA_H