/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Validaciones                                        *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              21/11/2024                                          *
 * Fecha de modificacion:          21/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/

#include "Validaciones.h"

template<typename T>
Validaciones<T>::Validaciones() {}

template<typename T>
T Validaciones<T>::ingresar(const std::string& msj, const std::string& tipo) {
    char cad[100]; // Buffer para almacenar entrada
    char c;
    int i = 0;
    T valor;
    std::cout << msj;

    while ((c = getch()) != 13) { // 13 es Enter
        if (tipo == "entero") {
            if (isdigit(c)) {
                std::cout << c;
                cad[i++] = c;
            } else if (c == 8 && i > 0) { // Backspace
                std::cout << "\b \b";
                i--;
            }
        } else if (tipo == "flotante" || tipo == "double") {
            if (isdigit(c) || (c == '.' && strchr(cad, '.') == nullptr)) {
                std::cout << c;
                cad[i++] = c;
            } else if (c == 8 && i > 0) { // Backspace
                std::cout << "\b \b";
                i--;
            }
        } else if (tipo == "string") {
            if (isalpha(c)) {
                std::cout << c;
                cad[i++] = c;
            } else if (c == 8 && i > 0) { // Backspace
                std::cout << "\b \b";
                i--;
            }
        } else if (tipo == "char") {
            if (isalnum(c)) {  // Acepta tanto letras como números
                std::cout << c;
                valor = c;
                break;
            } else {
                std::cout << "Caracter no valido. Intente nuevamente.\n";
            }
        }
    }
    cad[i] = '\0'; // Termina la cadena

    if (tipo == "entero") {
        return valor = std::atoi(cad);
    } else if (tipo == "flotante") {
        return valor = std::stof(cad); // Conversión directa a float
    } else if (tipo == "double") {
        return valor = std::stod(cad); // Conversión directa a double
    } else if (tipo == "string") {
        return valor = std::string(cad);
    } else if (tipo == "char") {
        return valor; // Ya asignado anteriormente
    }

    throw std::invalid_argument("Tipo no válido en función ingresar.");
}

template<typename T>
bool Validaciones<T>::validarCedula(const std::string& cedula) {
    if (cedula.length() != 10) return false;

    for (char c : cedula) {
        if (!isdigit(c)) return false;
    }

    int provincia = std::stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;

    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int digitoVerificacion = (suma % 10 == 0) ? 0 : 10 - (suma % 10);
    return digitoVerificacion == (cedula[9] - '0');
}