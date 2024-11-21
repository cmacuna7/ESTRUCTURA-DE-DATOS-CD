#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Validaciones {
private:
    Validaciones() {}

public:
    static Validaciones& getInstance() {
        static Validaciones instancia;
        return instancia;
    }

    bool validarCedula(const string& cedula) {
        if (cedula.length() != 10) {
            return false;
        }

        if (!all_of(cedula.begin(), cedula.end(), ::isdigit)) {
            return false;
        }

        int digitos[10];
        for (int i = 0; i < 10; i++) {
            digitos[i] = cedula[i] - '0';
        }

        int provincia = digitos[0] * 10 + digitos[1];
        if (provincia < 1 || (provincia > 24 && provincia != 30)) {
            return false;
        }

        if (digitos[2] < 0 || digitos[2] > 6) {
            return false;
        }

        int suma = 0;
        for (int i = 0; i < 9; i++) {
            if (i % 2 == 0) { 
                int doble = digitos[i] * 2;
                suma += (doble > 9) ? doble - 9 : doble;
            } else { 
                suma += digitos[i];
            }
        }

        int digitoVerificador = (10 - (suma % 10)) % 10;

        return digitoVerificador == digitos[9];
    }
};

#endif
