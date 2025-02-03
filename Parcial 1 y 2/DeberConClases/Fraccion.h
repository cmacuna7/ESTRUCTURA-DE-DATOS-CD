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

class Fraction {
private:
    int numerator;   // Numerador
    int denominator; // Denominador

    void simplify(); // Método privado para simplificar la fracción

public:
    // Constructor
    Fraction(int numerator, int denominator);

    // Getters
    int getNumerator() const;
    int getDenominator() const;

    // Setters
    void setNumerator(int numerator);
    void setDenominator(int denominator);

    // Método para sumar fracciones
    Fraction sumar(const Fraction& other) const;

    // Método para imprimir la fracción
    void print() const;
};
