#include <iostream>
using namespace std;

template <typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;

public:
    // Constructor
    Nodo(T dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}

    // Destructor
    ~Nodo() {}

    // Getters
    T getDato() const {
        return dato;
    }

    Nodo* getSiguiente() const {
        return siguiente;
    }

    Nodo* getAnterior() const {
        return anterior;
    }

    // Setters
    void setDato(T dato) {
        this->dato = dato;
    }

    void setSiguiente(Nodo* siguiente) {
        this->siguiente = siguiente;
    }

    void setAnterior(Nodo* anterior) {
        this->anterior = anterior;
    }
};