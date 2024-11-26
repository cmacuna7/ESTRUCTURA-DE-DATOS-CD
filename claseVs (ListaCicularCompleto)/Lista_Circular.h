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
#include "Nodo.h"

using namespace std;

template<typename T>
class Lista_Circular {
private:
    Nodo<T>* cabeza;
public:
    Lista_Circular();
    void Insertar_cabeza(T);
    void Insertar_cola(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    void BuscarPorCaracter(char); 
    Lista_Circular<string> ModificarCaracter(char borrar, char reemplazar = '\0');
    Lista_Circular<string> EliminarCaracter(char);
};
