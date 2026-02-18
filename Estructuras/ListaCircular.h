// estructuras/ListaCircular.h
#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class ListaCircular {
private:
    Nodo<T>* head;

public:
    ListaCircular() : head(nullptr) {}

    ~ListaCircular() {
        if (isEmpty()) return;

        Nodo<T>* actual = head->getSiguiente();
        while (actual != head) {
            Nodo<T>* temp = actual;
            actual = actual->getSiguiente();
            delete temp;
        }
        delete head;
        head = nullptr;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getSize() const {
        if (isEmpty()) return 0;

        int size = 1;
        Nodo<T>* actual = head;
        while (actual->getSiguiente() != head) {
            actual = actual->getSiguiente();
            size++;
        }
        return size;
    }

    Nodo<T>* getHead() const {
        return head;
    }

    Nodo<T>* getTail() const {
        if (isEmpty()) return nullptr;

        Nodo<T>* actual = head;
        while (actual->getSiguiente() != head) {
            actual = actual->getSiguiente();
        }
        return actual;
    }

    // Insertar al inicio
    void insertFirst(const T& value) {
        Nodo<T>* newNode = new Nodo<T>(value);

        if (isEmpty()) {
            head = newNode;
            head->setSiguiente(head);
            return;
        }

        Nodo<T>* tail = getTail();
        newNode->setSiguiente(head);
        head = newNode;
        tail->setSiguiente(head);
    }

    // Insertar al final
    void insertLast(const T& value) {
        if (isEmpty()) {
            insertFirst(value);
            return;
        }

        Nodo<T>* tail = getTail();
        Nodo<T>* newNode = new Nodo<T>(value);
        newNode->setSiguiente(head);
        tail->setSiguiente(newNode);
    }

    // Insertar en posición
    void insertAt(const T& value, int position) {
        if (isEmpty() || position <= 1) {
            insertFirst(value);
            return;
        }

        int size = getSize();
        if (position > size + 1) {
            // Si quieres, podrías hacer insertLast(value)
            insertLast(value);
            return;
        }

        Nodo<T>* prev = getAt(position - 1);
        Nodo<T>* newNode = new Nodo<T>(value);
        newNode->setSiguiente(prev->getSiguiente());
        prev->setSiguiente(newNode);
    }

    // Obtener nodo en posición
    Nodo<T>* getAt(int position) const {
        if (isEmpty()) return nullptr;

        int size = getSize();
        if (position < 1 || position > size) return nullptr;

        Nodo<T>* actual = head;
        int currentPosition = 1;

        while (currentPosition < position) {
            actual = actual->getSiguiente();
            currentPosition++;
        }
        return actual;
    }

    void deleteFirst() {
        if (isEmpty()) return;

        if (head->getSiguiente() == head) {
            delete head;
            head = nullptr;
            return;
        }

        Nodo<T>* tail = getTail();
        Nodo<T>* temp = head;
        head = head->getSiguiente();
        tail->setSiguiente(head);
        delete temp;
    }

    void deleteLast() {
        if (isEmpty()) return;

        if (head->getSiguiente() == head) {
            delete head;
            head = nullptr;
            return;
        }

        Nodo<T>* actual = head;
        while (actual->getSiguiente()->getSiguiente() != head) {
            actual = actual->getSiguiente();
        }

        Nodo<T>* tail = actual->getSiguiente();
        actual->setSiguiente(head);
        delete tail;
    }

    void deleteAt(int position) {
        if (isEmpty()) return;

        int size = getSize();
        if (position < 1 || position > size) return;

        if (position == 1) {
            deleteFirst();
            return;
        }

        Nodo<T>* prev = getAt(position - 1);
        Nodo<T>* nodeToDelete = prev->getSiguiente();
        prev->setSiguiente(nodeToDelete->getSiguiente());
        delete nodeToDelete;
    }

    // Recorre cierta cantidad de vuelta
    void printDebug(int turns) const {
        if (isEmpty()) {
            std::cout << "Lista circular vacía\n";
            return;
        }

        Nodo<T>* actual = head;
        int currentTurn = 0;

        while (currentTurn < turns) {
            std::cout << actual->getValor() << " -> ";
            if (actual->getSiguiente() == head) {
                currentTurn++;
                std::cout << " (vuelta " << currentTurn << ") ";
            }
            actual = actual->getSiguiente();
        }
        std::cout << std::endl;
    }
};

#endif // LISTA_CIRCULAR_H