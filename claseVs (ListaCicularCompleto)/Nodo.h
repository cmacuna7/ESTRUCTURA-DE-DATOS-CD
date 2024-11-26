/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              21/11/2024                                          *
 * Fecha de modificacion:          21/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#pragma once
#include <string>

template<typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente;
public:
    Nodo(T _dato);
    void setDato(T _dato);
    T getDato();
    void setSiguiente(Nodo* _siguiente);
    Nodo* getSiguiente();
};
