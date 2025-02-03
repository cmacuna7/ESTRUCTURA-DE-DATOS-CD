/***********************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                  *
 * Proposito:                      Sumar matrices                      *
 * Autor:                          Abner Arboleda                      *
 * Fecha de creacion:              14/11/2024                          *
 * Fecha de modificacion:          14/11/2024                          *
 * Materia:                        Estructura de datos                 *
 * NRC :                           1992                                *
 ***********************************************************************/

#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <iostream>
#include <functional>  // Para usar std::function

template <typename T>
class Matriz {
private:
    std::vector<std::vector<T>> matriz;
    int dimension;

public:
    // Constructor
    Matriz(int dimension);

    // Destructor
    ~Matriz();

    // Getter para obtener un elemento de la matriz
    T getElemento(int fila, int columna) const;

    // Setter para establecer un elemento de la matriz
    void setElemento(int fila, int columna, T valor);

    // Getter para obtener la dimensión
    int getDimension() const;

    // Imprimir matriz
    void imprimir() const;

    // Método para sumar dos matrices de manera recursiva
    void sumarMatricesRecursivamente(const Matriz<T>& otraMatriz, Matriz<T>& resultado);
};

#include "Matriz.cpp"  // Incluir la implementación después de la declaración

#endif  // MATRIZ_H
