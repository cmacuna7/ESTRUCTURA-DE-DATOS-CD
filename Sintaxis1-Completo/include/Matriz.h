#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include "MatrizHelper.h"  // Incluimos la DLL para usar sus funciones

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

    // Imprimir matriz usando la DLL
    void imprimir() const;

    // Sumar matrices recursivamente
    void sumarMatricesRecursivamente(const Matriz<T>& otraMatriz, Matriz<T>& resultado);
};

#include "Matriz.tpp"  // Incluimos el archivo cpp para definir las funciones

#endif  // MATRIZ_H
