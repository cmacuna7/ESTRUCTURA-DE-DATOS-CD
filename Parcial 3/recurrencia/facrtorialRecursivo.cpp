#include <iostream>
#include <chrono>

using namespace std;

// Función recursiva para calcular el factorial de un número
int factorial(int n) {
    // Caso base: cuando n es 0 o 1, el factorial es 1
    if (n == 0 || n == 1) 
        return 1;

    // Llamada recursiva: n * factorial(n-1)
    // Aquí se aplica la recurrencia: T(n) = T(n-1) + O(1)
    return n * factorial(n - 1);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    int num;
    cout << "Ingrese un numero: ";
    cin >> num;
    cout << "El factorial de " << num << " es: " << factorial(num) << endl;

    // Captura el tiempo de finalización
    auto end = std::chrono::high_resolution_clock::now();
    // Calcula la duración en milisegundos
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de ejecucion: " << duration.count() << " ms" << std::endl;
    return 0;
}

/*
=== ANÁLISIS DE LA RECURSIVIDAD ===

1. **Ecuación de recurrencia**:
   La función factorial se llama a sí misma con un número menor en cada paso.
   Esto genera la siguiente ecuación de recurrencia:

   T(n) = T(n-1) + O(1)

   - T(n) representa el tiempo que tarda en ejecutarse la función factorial(n).
   - T(n-1) es el tiempo que tarda en calcular factorial(n-1).
   - O(1) es el tiempo constante de la multiplicación y la comparación.
   */