#include "Matriz.h"

// Constructor
template <typename T>
Matriz<T>::Matriz(int dimension) : dimension(dimension) {
    matriz.resize(dimension, std::vector<T>(dimension, 0));
}

// Destructor
template <typename T>
Matriz<T>::~Matriz() {}

// Getter para obtener un elemento de la matriz
template <typename T>
T Matriz<T>::getElemento(int fila, int columna) const {
    return matriz[fila][columna];
}

// Setter para establecer un elemento de la matriz
template <typename T>
void Matriz<T>::setElemento(int fila, int columna, T valor) {
    matriz[fila][columna] = valor;
}

// Getter para obtener la dimensión
template <typename T>
int Matriz<T>::getDimension() const {
    return dimension;
}

// Imprimir matriz
template <typename T>
void Matriz<T>::imprimir() const {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Suma recursiva de matrices usando lambdas
template <typename T>
void Matriz<T>::sumarMatricesRecursivamente(const Matriz<T>& otraMatriz, Matriz<T>& resultado) {
    // Lambda recursiva
    std::function<void(int, int)> recursiva = [&](int fila, int columna) {
        if (fila >= dimension) return;  // Condición base

        // Sumar los elementos correspondientes
        resultado.setElemento(fila, columna, this->getElemento(fila, columna) + otraMatriz.getElemento(fila, columna));

        // Recursión: Si hay más columnas, sigue
        if (columna + 1 < dimension) {
            recursiva(fila, columna + 1);  // Llamada recursiva
        } else {
            // Si ya no hay más columnas, ir a la siguiente fila
            recursiva(fila + 1, 0);  // Llamada recursiva para la siguiente fila
        }
    };

    // Llamada inicial a la función recursiva
    recursiva(0, 0);
}