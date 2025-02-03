#ifndef MATRIZHELPER_H
#define MATRIZHELPER_H

#include <vector>
#include <iostream>

// Macro para manejar exportación e importación
#ifdef MATRIZHELPERDLL_EXPORTS
#define MATRIZHELPER_API __declspec(dllexport)
#else
#define MATRIZHELPER_API __declspec(dllimport)
#endif

// Declaración de las funciones de la DLL
extern "C" {
    MATRIZHELPER_API void imprimirMatriz(const std::vector<std::vector<int>>& matriz);
    MATRIZHELPER_API void setElemento(std::vector<std::vector<int>>& matriz, int fila, int columna, int valor);
    MATRIZHELPER_API int getElemento(const std::vector<std::vector<int>>& matriz, int fila, int columna);
}

#endif  // MATRIZHELPER_H
