#include <iostream>
#include "Matriz.h"

int main() {
    Matriz<int> mat1(3);
    Matriz<int> mat2(3);
    Matriz<int> resultado(3);

    // Configurar valores en mat1 y mat2
    mat1.setElemento(0, 0, 1);
    mat1.setElemento(0, 1, 2);
    mat1.setElemento(0, 2, 3);
    mat1.setElemento(1, 0, 4);
    mat1.setElemento(1, 1, 5);
    mat1.setElemento(1, 2, 6);
    mat1.setElemento(2, 0, 7);
    mat1.setElemento(2, 1, 8);
    mat1.setElemento(2, 2, 9);

    mat2.setElemento(0, 0, 9);
    mat2.setElemento(0, 1, 8);
    mat2.setElemento(0, 2, 7);
    mat2.setElemento(1, 0, 6);
    mat2.setElemento(1, 1, 5);
    mat2.setElemento(1, 2, 4);
    mat2.setElemento(2, 0, 3);
    mat2.setElemento(2, 1, 2);
    mat2.setElemento(2, 2, 1);

    
    // Llamar al método miembro para sumar las matrices
    mat1.sumarMatricesRecursivamente(mat2, resultado);  // Usamos el método de la clase `Matriz`

    // Imprimir resultado
    resultado.imprimir();

    return 0;
}
