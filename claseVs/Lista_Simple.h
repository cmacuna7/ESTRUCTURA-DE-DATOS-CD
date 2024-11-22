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
//#include "Nodo.cpp"
#include "Nodo.h"

using namespace std;

template<typename T>
class Lista_Simple {
private:
    Nodo<T>* cabeza;
public:
    Lista_Simple();
    void Insertar_cabeza(T);
    void Insertar_cola(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    void BuscarPorCaracter(char); // Nuevo método
    Lista_Simple<string> EliminarCaracter(char); // Nuevo método para crear una lista nueva sin el carácter
};

