#include "MatrizHelper.h"

// Función para imprimir una matriz
void imprimirMatriz(const std::vector<std::vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (const auto& elem : fila) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Función para obtener un elemento de la matriz
int getElemento(const std::vector<std::vector<int>>& matriz, int fila, int columna) {
    if (fila < 0 || fila >= matriz.size() || columna < 0 || columna >= matriz[fila].size()) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return matriz[fila][columna];
}

// Función para establecer un elemento en la matriz
void setElemento(std::vector<std::vector<int>>& matriz, int fila, int columna, int valor) {
    if (fila < 0 || fila >= matriz.size() || columna < 0 || columna >= matriz[fila].size()) {
        throw std::out_of_range("Índice fuera de rango");
    }
    matriz[fila][columna] = valor;
}
