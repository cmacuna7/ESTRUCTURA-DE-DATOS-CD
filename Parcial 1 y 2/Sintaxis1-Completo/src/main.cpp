#include <iostream>
#include "Matriz.h"  // Incluir la cabecera de la clase Matriz

int main() {
    Matriz<int> mat1(3);        // Crear una matriz de 3x3
    Matriz<int> mat2(3);        // Crear otra matriz de 3x3
    Matriz<int> resultado(3);   // Crear una matriz para almacenar el resultado

    // Configurar valores en mat1
    mat1.setElemento(0, 0, 1);
    mat1.setElemento(0, 1, 2);
    mat1.setElemento(0, 2, 3);
    mat1.setElemento(1, 0, 4);
    mat1.setElemento(1, 1, 5);
    mat1.setElemento(1, 2, 6);
    mat1.setElemento(2, 0, 7);
    mat1.setElemento(2, 1, 8);
    mat1.setElemento(2, 2, 9);

    // Configurar valores en mat2
    mat2.setElemento(0, 0, 9);
    mat2.setElemento(0, 1, 8);
    mat2.setElemento(0, 2, 7);
    mat2.setElemento(1, 0, 6);
    mat2.setElemento(1, 1, 5);
    mat2.setElemento(1, 2, 4);
    mat2.setElemento(2, 0, 3);
    mat2.setElemento(2, 1, 2);
    mat2.setElemento(2, 2, 1);

    // Sumar matrices recursivamente
    mat1.sumarMatricesRecursivamente(mat2, resultado);

    // Imprimir el resultado de la suma
    std::cout << "Resultado de la suma:" << std::endl;
    resultado.imprimir();  // Usar la función de impresión de la DLL

    return 0;
}
