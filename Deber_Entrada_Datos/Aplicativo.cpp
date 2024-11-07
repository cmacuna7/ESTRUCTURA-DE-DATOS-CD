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
int leerEntero() {
    string input = "";
    char c;
    cout << "\nIngrese un valor entero: ";
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
float leerFlotante() {
    string input = "";
    char c;
    bool hasDot = false;
    cout << "\nIngrese un valor flotante: ";
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

// Función para leer un valor double, similar a float
double leerDoble() {
    string input = "";
    char c;
    bool hasDot = false;
    cout << "\nIngrese un valor de doble precision: ";
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

// Función para leer un carácter, permite solo un carácter
char leerCaracter() {
    char c;
    char caracter = '\0'; // Caracter vacío inicial
    cout << "\nIngrese un caracter: ";
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

// Función para leer un valor booleano (0 o 1)
bool leerBooleano() {
    string input = "";
    char c;
    cout << "Ingrese un valor booleano (0 para falso, 1 para verdadero): ";
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
string leerCadena() {
}

int main() {
    int entero = leerEntero();
    float flotante = leerFlotante();
    double doble = leerDoble();
    char caracter = leerCaracter();
    bool booleano = leerBooleano();
    string cadena = leerCadena();

    cout << "\nValores ingresados:\n";
    cout << "Entero: " << entero << endl;
    cout << "Flotante: " << flotante << endl;
    cout << "Doble: " << doble << endl;
    cout << "Caracter: " << caracter << endl;
    cout << "Booleano: " << (booleano ? "verdadero" : "falso") << endl;
    cout << "Cadena: " << cadena << endl;

    return 0;
}
