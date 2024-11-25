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

template <typename T>
Validaciones<T>::Validaciones() {}

template <typename T>
T Validaciones<T>::ingresar(char* msj, char* tipo) {
    char cad[50];
    char c;
    int i = 0;
    T valor;
    printf("%s", msj);

    while ((c = getch()) != 13) {
        if (tipo == "entero") {
            if (c >= '0' && c <= '9') {
                printf("%c", c);
                cad[i++] = c;
            } else if (c == 8 && i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (tipo == "flotante" || tipo == "double") {
            if ((c >= '0' && c <= '9') || c == '.') {
                printf("%c", c);
                cad[i++] = c;
            } else if (c == 8 && i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (tipo == "string") {
            do {
                i = 0;
                printf("%s", msj);
                while ((c = getch()) != 13) {
                    if (isalpha(c) || c == ' ') {
                        printf("%c", c);
                        cad[i++] = c;
                    } else if (c == 8 && i > 0) {
                        printf("\b \b");
                        i--;
                    }
                }
                cad[i] = '\0';
                if (!validarNombre(cad)) {
                    printf("\nEntrada invalida. Solo se permiten letras y espacios. Intente nuevamente.\n");
                }
            } while (!validarNombre(cad));
            for (int j = 0; cad[j] != '\0'; j++) {
                valor = valor + cad[j];
            }
            return valor;
        } else if (tipo == "char") {
            if (isalpha(c)) {
                printf("%c", c);
                valor = c;
                break;
            } else if (c == 8) {
                printf("\b \b");
            }
        }
    }
    cad[i] = '\0';
    if (tipo == "entero") {
        return valor = atoi(cad);
    } else if (tipo == "flotante") {
        return valor = atof(cad);
    } else if (tipo == "double") {
        return valor = atof(cad);
    } else if (tipo == "string") {
        return valor = cad;
    } else if (tipo == "char") {
        return valor;
    }
}

template <typename T>
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

template <typename T>
bool Validaciones<T>::validarNombre(const std::string& nombre) {
    if (nombre.empty()) {
        return false; // No puede estar vacío
    }
    for (char c : nombre) {
        if (!isalpha(c) && c != ' ') {
            return false; // Solo permite letras y espacios
        }
    }
    return true; // Es un nombre válido
}
