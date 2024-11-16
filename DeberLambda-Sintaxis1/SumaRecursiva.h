#include "Matriz.h"
#include <functional>  // Para usar std::function

// Función para realizar la suma recursiva
template <typename T>
void sumaRecursiva(const Matriz<T>& mat1, const Matriz<T>& mat2, Matriz<T>& resultado) {
    // Lambda recursiva para sumar las matrices
    std::function<void(int, int)> recursiva = [&](int fila, int columna) {
        if (fila >= mat1.getDimension()) return;  // Condición base

        // Sumar los elementos correspondientes
        resultado.setElemento(fila, columna, mat1.getElemento(fila, columna) + mat2.getElemento(fila, columna));

        // Recursión: Si hay más columnas, sigue
        if (columna + 1 < mat1.getDimension()) {
            recursiva(fila, columna + 1);  // Llamada recursiva
        } else {
            // Si ya no hay más columnas, ir a la siguiente fila
            recursiva(fila + 1, 0);  // Llamada recursiva para la siguiente fila
        }
    };

    // Llamada inicial a la función recursiva
    recursiva(0, 0);
}