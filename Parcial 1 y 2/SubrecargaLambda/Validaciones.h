#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
#include <limits>

// Función para leer un número entero con validación
int leerEntero() {
    int valor;
    while (true) {
        std::cin >> valor;
        if (std::cin.fail()) {
            std::cin.clear(); // Limpiar el error de la entrada
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar el resto de la entrada
            std::cout << "Por favor, ingrese un numero valido: ";
        } else {
            return valor;
        }
    }
}

// Función para esperar que el usuario presione Enter
void esperarEnter() {
    std::cout << "Presione Enter para continuar..." << std::endl;
    std::cin.ignore(); // Ignorar cualquier entrada previa
    std::cin.get();    // Esperar por el Enter
}

#endif
