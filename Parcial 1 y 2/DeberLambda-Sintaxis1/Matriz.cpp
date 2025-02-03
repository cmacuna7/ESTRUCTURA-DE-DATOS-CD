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

template <typename T>
void Matriz<T>::sumarMatricesRecursivamente(const Matriz<T>& otraMatriz, Matriz<T>& resultado) {
    // Lambda recursiva con template implícito
    auto recursiva = [](auto fila, auto columna, auto& self, const Matriz<T>& mat1, const Matriz<T>& mat2, Matriz<T>& res) {
        if (fila >= mat1.getDimension()) return;

        // Sumar los elementos correspondientes
        res.setElemento(fila, columna, mat1.getElemento(fila, columna) + mat2.getElemento(fila, columna));

        // Recursión: Si hay más columnas, sigue
        if (columna + 1 < mat1.getDimension()) {
            self(fila, columna + 1, self, mat1, mat2, res);  // Llamada recursiva
        } else {
            self(fila + 1, 0, self, mat1, mat2, res);  // Ir a la siguiente fila
        }
    };

    // Llamada inicial a la función recursiva
    recursiva(0, 0, recursiva, *this, otraMatriz, resultado);
}