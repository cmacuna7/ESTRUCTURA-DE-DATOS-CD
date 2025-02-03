/************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                               *
 * Proposito:                      Ingreso de Datos                                 *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz *                      *
 * Fecha de creacion:              06/11/2024                                       *
 * Fecha de modificacion:          08/11/2024                                       *
 * Materia:                        Estructura de datos                              *
 * NRC :                           1992                                             *
 ***********************************************************************************/

#include <iostream>
#include <conio.h> // Para getch()
#include <string>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stoi;
using std::stof;
using std::stod;

// Función para leer un número entero, solo acepta dígitos
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
        if (isprint(c) && caracter == '\0') { // Acepta solo un carácter imprimible
            caracter = c;
            cout << c;
        } else if (c == 8 && caracter != '\0') { // Backspace permite borrar el carácter
            cout << "\b \b";
            caracter = '\0'; // Restablece el carácter para permitir otro ingreso
        } else if (c == 13 && caracter != '\0') { // Enter para confirmar el carácter
            cout << endl;
            return caracter;
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

int main() {
    int entero = leerEntero("\nIngrese un valor entero: ");
    float flotante = leerFlotante("\nIngrese un valor flotante: ");
    double doble = leerDoble("\nIngrese un valor de doble: ");
    char caracter = leerCaracter("\nIngrese un caracter: ");
    bool booleano = leerBooleano("Ingrese un valor booleano (0 para falso, 1 para verdadero): ");
    string cadena = leerCadena("\nIngrese una cadena de texto: ");

    cout << "\nValores ingresados:\n";
    cout << "Entero: " << entero << endl;
    cout << "Flotante: " << flotante << endl;
    cout << "Doble: " << doble << endl;
    cout << "Caracter: " << caracter << endl;
    cout << "Booleano: " << (booleano ? "verdadero" : "falso") << endl;
    cout << "Cadena: " << cadena << endl;

    return 0;
}