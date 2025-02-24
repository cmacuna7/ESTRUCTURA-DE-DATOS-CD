#ifndef CALCULADORA_H
#define CALCULADORA_H
#include <vector>

class Calculadora {
public:
    // Funciones O(1)
    static double sumar(double a, double b);
    static double restar(double a, double b);
    static double multiplicar(double a, double b);
    static double dividir(double a, double b);

    // Función O(log n) - Potencia usando divide y vencerás
    static double potenciaLogaritmica(double base, int exponente);

    // Función O(n) - Suma de serie
    static double sumaSerie(const std::vector<double>& numeros);

    // Función O(n log n) - Ordenamiento y suma
    static double sumaOrdenada(std::vector<double>& numeros);

    // Función O(n²) - Multiplicación de matrices
    static std::vector<std::vector<double>> multiplicarMatrices(const std::vector<std::vector<double>>& matriz1, const std::vector<std::vector<double>>& matriz2);

    // Función O(2^n) - Fibonacci recursivo
    static double fibonacciExponencial(int n);

    // Funcion O(n!) - Permutaciones
    static std::vector<std::vector<int>> permutaciones(int n);
};

#endif // CALCULADORA_H