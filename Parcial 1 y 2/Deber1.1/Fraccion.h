/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Programar una suma de fracciones                         *
 * Autor:                          Abner Arboleda, Christian Acuña, Ch ristian Bonifaz      *
 * Fecha de creacion:              08/10/2024                                               *
 * Fecha de modificacion:          09/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include <iostream>

// Plantilla de la clase Fracción
template <typename T>
class Fraction {
private:
    T numerator;   // Numerador
    T denominator; // Denominador

    void simplify(); // Método privado para simplificar la fracción

public:
    // Constructor
    Fraction(T numerator, T denominator);

    // Getters
    T getNumerator() const;
    T getDenominator() const;

    // Setters
    void setNumerator(T numerator);
    void setDenominator(T denominator);

    // Sobrecarga de operadores
    Fraction operator+(const Fraction& other) const;

    // Método para imprimir la fracción
    void print() const;
};
