/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista doble circular                 *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              25/11/2024                                          *
 * Fecha de modificacion:          25/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 ***************************************************************************************/
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

public:
    // Constructor
    ListaCircular() : cabeza(nullptr){}

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

    // Nuevo método para obtener el nodo cabeza
    Nodo<T>* getCabeza() const;
};

#endif
