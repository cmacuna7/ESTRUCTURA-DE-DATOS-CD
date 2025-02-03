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
#include "Validaciones.h"
#include "Fraccion.cpp"

// Función principal para probar la clase Fraction
int main() {
    try {
        int numerador1, numerador2, denominador1, denominador2;

        do {
            numerador1 = leerEntero("\nIngrese el numerador del primer numero: ");
            denominador1 = leerEntero("\nIngrese el denominador del primer numero: ");
            numerador2 = leerEntero("\nIngrese el numerador del segundo numero: ");
            denominador2 = leerEntero("\nIngrese el denominador del segundo numero: ");
            if (denominador1 == 0 || denominador2 == 0) {
                std::cout << "\nError: El denominador no puede ser 0.\n";
            }
        } while (denominador1 == 0 || denominador2 == 0);

        Fraction<int> frac1(numerador1, denominador1);
        Fraction<int> frac2(numerador2, denominador2);

        // Suma usando el método sumar
        Fraction<int> resultAdd = frac1.sumar(frac2);
        std::cout << "\nSuma: ";
        resultAdd.print();

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
