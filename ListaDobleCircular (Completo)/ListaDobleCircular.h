#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include "Nodo.h"
#include <iostream>
#include <string>
#include <algorithm> // Para std::replace

using namespace std;

template <typename T>
class ListaCircular {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    // Constructor
    ListaCircular() : cabeza(nullptr), cola(nullptr) {}

    // Destructor
    ~ListaCircular();

    // Métodos de la lista
    void insertar(T dato);
    void mostrar();
    void buscarPorCaracter(char caracter);
    void borrarCaracter(char caracter); 
    void reemplazarCaracter(char viejo, char nuevo); 

    // Métodos que devuelven listas auxiliares
    ListaCircular<T> eliminarCaracterEnAuxiliar(char caracter);
    ListaCircular<T> reemplazarCaracterEnAuxiliar(char viejo, char nuevo);
};

#endif
