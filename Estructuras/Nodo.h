#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
    T valor;
    Nodo<T>* siguiente;

public:
    Nodo(const T& valor) : valor(valor), siguiente(nullptr) {}

    T getValor() const {
        return valor;
    }

    void setValor(const T& nuevoValor) {
        valor = nuevoValor;
    }

    Nodo<T>* getSiguiente() const {
        return siguiente;
    }

    void setSiguiente(Nodo<T>* sig) {
        siguiente = sig;
    }
};

#endif // NODO_H