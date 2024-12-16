#ifndef PILA_H
#define PILA_H

#include <vector>
#include <stdexcept>

// Clase genérica para una pila
template <typename T>
class Pila {
private:
    std::vector<T> elementos;
public:
    // Insertar un elemento en la pila
    void push(T elemento);
    // Eliminar el elemento en la parte superior
    void pop();
    // Obtener el elemento en la parte superior
    T top() const;
    // Verificar si la pila está vacía
    bool empty() const;
};

#include "pila.cpp" // Incluir la implementación para clases templadas

#endif // PILA_H
