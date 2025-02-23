#include "Calculadora.h"
#include <stdexcept>
#include <algorithm>

double Calculadora::sumar(double a, double b) {
    return a + b;
}

double Calculadora::restar(double a, double b) {
    return a - b;
}

double Calculadora::multiplicar(double a, double b) {
    return a * b;
}

double Calculadora::dividir(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Error: División por cero.");
    }
    return a / b;
}

double Calculadora::potenciaLogaritmica(double base, int exponente) {
    if (exponente == 0) return 1;
    if (exponente == 1) return base;
    
    double temp = potenciaLogaritmica(base, exponente/2);
    if (exponente % 2 == 0)
        return temp * temp;
    else
        return base * temp * temp;
}

// O(n) - Suma de serie
double Calculadora::sumaSerie(const std::vector<double>& numeros) {
    double suma = 0;
    for (double num : numeros) {
        suma += num;
    }
    return suma;
}

// O(n log n) - Ordenamiento y suma
double Calculadora::sumaOrdenada(std::vector<double>& numeros) {
    std::sort(numeros.begin(), numeros.end()); // O(n log n)
    double suma = 0;
    for (double num : numeros) { // O(n)
        suma += num;
    }
    return suma;
}

// O(n²) - Multiplicación de matrices
std::vector<std::vector<double>> Calculadora::multiplicarMatrices(
    const std::vector<std::vector<double>>& matriz1,
    const std::vector<std::vector<double>>& matriz2) {
    
    int n = matriz1.size();
    std::vector<std::vector<double>> resultado(n, std::vector<double>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                resultado[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
    return resultado;
}

// O(2^n) - Fibonacci recursivo
double Calculadora::fibonacciExponencial(int n) {
    if (n <= 1) return n;
    return fibonacciExponencial(n-1) + fibonacciExponencial(n-2);
}