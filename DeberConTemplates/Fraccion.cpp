/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Programar una suma de fracciones                         *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              08/10/2024                                               *
 * Fecha de modificacion:          09/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include <iostream>
#include "Fraccion.h"

// Función auxiliar para calcular el máximo común divisor mediante el algoritmo de Euclides
template <typename T>
T mcd(T a, T b) {
    while (b != 0) {
        T temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Constructor
template <typename T>
Fraction<T>::Fraction(T numerator, T denominator) : numerator(numerator), denominator(denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("El denominador no puede ser 0.");
    }
    simplify();
}

// Método privado para simplificar la fracción
template <typename T>
void Fraction<T>::simplify() {
    T divisor = mcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
}

// Getters
template <typename T>
T Fraction<T>::getNumerator() const {
    return numerator;
}

template <typename T>
T Fraction<T>::getDenominator() const {
    return denominator;
}

// Setters
template <typename T>
void Fraction<T>::setNumerator(T numerator) {
    this->numerator = numerator;
    simplify();
}

template <typename T>
void Fraction<T>::setDenominator(T denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("El denominador no puede ser 0.");
    }
    this->denominator = denominator;
    simplify();
}

// Método para sumar fracciones
template <typename T>
Fraction<T> Fraction<T>::sumar(const Fraction& other) const {
    T newNumerator = numerator * other.denominator + other.numerator * denominator;
    T newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

// Método para imprimir la fracción
template <typename T>
void Fraction<T>::print() const {
    std::cout << numerator << "/" << denominator << std::endl;
}
