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

    void pop() {
        if (isEmpty()) return;

        Nodo<T>* temp = top;
        top = top->getSiguiente();
        delete temp;
        size--;
    }

    T peek() const {
        return top->getValor();
    }
};

#endif // PILA_H