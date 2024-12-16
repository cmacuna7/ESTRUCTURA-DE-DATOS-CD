#include <iostream>
#include <string>
#include "conversion.cpp"
#include "validaciones.cpp"

using namespace std;

int main() {
    string infix;
    string prefix;
    string postfix;

    while (true) {
        int opcion;
        cout << "\nMenu:\n";
        cout << "1. Ingresar expresion infija\n";
        cout << "2. Mostrar expresion infija\n";
        cout << "3. Convertir a prefijo\n";
        cout << "4. Convertir a posfijo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "Ingrese la expresion infija (sin espacios, con formato adecuado): ";
                getline(cin, infix);

                if (infix.find(' ') != string::npos) {
                    cout << "Error: La expresion no debe contener espacios. Intenta de nuevo." << endl;
                    infix = "";
                } else if (!isValidExpression(infix)) {
                    cout << "La expresion ingresada no es valida. Intenta de nuevo." << endl;
                    infix = "";
                } else {
                    cout << "Expresion infija registrada correctamente." << endl;
                }
                break;
            }
            case 2: {
                if (infix.empty()) {
                    cout << "Error: No se ha ingresado una expresion infija." << endl;
                } else {
                    cout << "Expresion infija: " << infix << endl;
                }
                break;
            }
            case 3: {
                if (infix.empty()) {
                    cout << "Error: No se ha ingresado una expresion infija." << endl;
                } else {
                    prefix = infixToPrefix(infix);
                    cout << "Expresion prefija: " << prefix << endl;
                }
                break;
            }
            case 4: {
                if (infix.empty()) {
                    cout << "Error: No se ha ingresado una expresion infija." << endl;
                } else {
                    postfix = infixToPostfix(infix);
                    cout << "Expresion posfija: " << postfix << endl;
                }
                break;
            }
            case 5:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opcion invalida. Intenta de nuevo." << endl;
        }
    }

    return 0;
}
