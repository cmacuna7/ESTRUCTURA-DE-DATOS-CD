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
int mcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Constructor
Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("El denominador no puede ser 0.");
    }
    simplify();
}

// Método privado para simplificar la fracción
void Fraction::simplify() {
    int divisor = mcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
}

// Getters
int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

// Setters
void Fraction::setNumerator(int numerator) {
    this->numerator = numerator;
    simplify();
}

void Fraction::setDenominator(int denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("El denominador no puede ser 0.");
    }
    this->denominator = denominator;
    simplify();
}

// Método para sumar fracciones
Fraction Fraction::sumar(const Fraction& other) const {
    int newNumerator = numerator * other.denominator + other.numerator * denominator;
    int newDenominator = denominator * other.denominator;
    return Fraction(newNumerator, newDenominator);
}

// Método para imprimir la fracción
void Fraction::print() const {
    std::cout << numerator << "/" << denominator << std::endl;
}
