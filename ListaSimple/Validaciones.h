#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <string>
#include <limits>
#include <cctype>
#include <unistd.h>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stoi;
using std::stof;
using std::stod;

int leerEntero(const string& mensaje);
float leerFlotante(const string& mensaje);
double leerDoble(const string& mensaje);
char leerCaracter(const string& mensaje);
bool leerBooleano(const string& mensaje);
string leerCadena(const string& mensaje);

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

    int leerEntero(const string& mensaje) {
    string input = "";
    char c;
    cout << mensaje;
    while (true) {
        c = getch();
        if (c == 13 && !input.empty()) { // Enter y al menos un dígito
            break;
        } else if (c >= '0' && c <= '9') { // Solo dígitos permitidos
            input += c;
            cout << c; // Muestra el carácter en pantalla
        } else if (c == 8 && !input.empty()) { // Backspace
            input.pop_back();
            cout << "\b \b"; // Borra el último carácter en pantalla
        }
    }
    return stoi(input);
}

// Función para leer un número flotante, solo acepta dígitos y un punto decimal
float leerFlotante(const string& mensaje) {
    string input = "";
    char c;
    bool hasDot = false;
    cout << mensaje;
    while (true) {
        c = getch();
        if (c == 13 && !input.empty()) { // Enter y al menos un dígito
            break;
        } else if (c >= '0' && c <= '9') { // Solo dígitos permitidos
            input += c;
            cout << c;
        } else if (c == '.' && !hasDot) { // Solo un punto decimal permitido
            input += c;
            hasDot = true;
            cout << c;
        } else if (c == 8 && !input.empty()) { // Backspace
            if (input.back() == '.') hasDot = false;
            input.pop_back();
            cout << "\b \b";
        }
    }
    return stof(input);
}

// Función para leer un valor de doble precisión, similar a float
double leerDoble(const string& mensaje) {
    string input = "";
    char c;
    bool hasDot = false;
    cout << mensaje;
    while (true) {
        c = getch();
        if (c == 13 && !input.empty()) {
            break;
        } else if (c >= '0' && c <= '9') {
            input += c;
            cout << c;
        } else if (c == '.' && !hasDot) {
            input += c;
            hasDot = true;
            cout << c;
        } else if (c == 8 && !input.empty()) {
            if (input.back() == '.') hasDot = false;
            input.pop_back();
            cout << "\b \b";
        }
    }
    return stod(input);
}

// Función para leer un carácter, permite solo un carácter y borrar
char leerCaracter(const string& mensaje) {
   char c;
    char caracter = '\0'; // Caracter vacío inicial
    cout << mensaje;

    while (true) {
        c = getch();
        if (isprint(c) && c != ' ' && caracter == '\0') { // Acepta solo un carácter imprimible, pero no espacio
            caracter = c;
            cout << c;
        } else if (c == 8 && caracter != '\0') { // Backspace permite borrar el carácter
            cout << "\b \b";
            caracter = '\0'; // Restablece el carácter para permitir otro ingreso
        } else if (c == 13 && caracter != '\0') { // Enter para confirmar el carácter
            cout << endl;
            return caracter;
        } else if (c == ' ') { // Si el carácter es espacio, no hace nada y permite seguir
            continue;
        }
    }
}

// Función para leer un valor booleano (0 o 1), permite borrar y Enter
bool leerBooleano(const string& mensaje) {
    string input = "";
    char c;
    cout << mensaje;

    while (true) {
        c = getch();
        if ((c == '0' || c == '1') && input.empty()) { // Solo permite 0 o 1
            input = c;
            cout << c;
        } else if (c == 13 && !input.empty()) { // Enter para confirmar
            return input == "1";
        } else if (c == 8 && !input.empty()) { // Backspace para borrar
            input.pop_back();
            cout << "\b \b";
        }
    }
}

// Función para leer una cadena de texto (string)
string leerCadena(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    while (valor.empty()) {
        cout << "\nError: La cadena no debe estar vacia. Intente de nuevo.\n";
        cout << mensaje;
        getline(cin, valor);
    }
    return valor;
}

string leerCadenaSinNumero(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);

    // Verificar que la cadena no esté vacía y que contenga solo letras
    while (valor.empty() || !valor.empty()) {
        bool esValida = true;

        // Verificar si la cadena contiene solo letras
        for (char c : valor) {
            if (!isalpha(c)) { // Si encontramos un carácter que no es letra
                esValida = false;
                break;
            }
        }

        // Si la cadena está vacía o no es válida, se muestra el mensaje de error y se vuelve a pedir el valor
        if (valor.empty() || !esValida) {
            cout << "\nError: La cadena debe contener solo letras y no estar vacia. Intente de nuevo.\n";
            cout << mensaje;
            getline(cin, valor);
        } else {
            break; // Si la cadena es válida, salimos del bucle
        }
    }
    return valor;
}


};

#endif
