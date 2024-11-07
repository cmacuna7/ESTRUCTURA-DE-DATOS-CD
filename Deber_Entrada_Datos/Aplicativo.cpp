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
}

// Función para leer un carácter, permite solo un carácter
char leerCaracter() {
}

// Función para leer un valor booleano (0 o 1)
bool leerBooleano() {
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
