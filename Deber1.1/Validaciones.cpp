#include "Validaciones.h"
#include <limits>
#include <conio.h> // Para getch()

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stoi;
using std::stof;
using std::stod;

int Validaciones::leerEntero(const string& mensaje) {
    string input = "";
    char c;
    cout << mensaje;
    while (true) {
        c = getch();
        if (c == 13 && !input.empty()) { // Enter y al menos un dígito
            break;
        } else if (isdigit(c)) {
            input += c;
            cout << c;
        } else if (c == 8 && !input.empty()) { // Backspace
            input.pop_back();
            cout << "\b \b";
        }
    }
    return stoi(input);
}

float Validaciones::leerFlotante(const string& mensaje) {
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

double Validaciones::leerDoble(const string& mensaje) {
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
    return stod(input);
}

char Validaciones::leerCaracter(const string& mensaje) {
    char c;
    cout << mensaje;
    c = getch();
    cout << c << endl;
    return c;
}

bool Validaciones::leerBooleano(const string& mensaje) {
    char c;
    cout << mensaje << " (s/n): ";
    while (true) {
        c = getch();
        if (c == 's' || c == 'S') {
            cout << c << endl;
            return true;
        } else if (c == 'n' || c == 'N') {
            cout << c << endl;
            return false;
        }
    }
}

string Validaciones::leerCadena(const string& mensaje) {
    string input;
    cout << mensaje;
    getline(cin, input);
    return input;
}