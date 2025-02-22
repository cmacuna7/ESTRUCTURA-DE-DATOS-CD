#include <iostream>
#include "Calculadora.h"

using namespace std;

int main() {
    int opcion;
    double num1, num2, resultado;

    do {
        cout << "\nCalculadora - Operaciones Básicas\n";
        cout << "1. Sumar\n";
        cout << "2. Restar\n";
        cout << "3. Multiplicar\n";
        cout << "4. Dividir\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion >= 1 && opcion <= 4) {
            cout << "Ingrese el primer número: ";
            cin >> num1;
            cout << "Ingrese el segundo número: ";
            cin >> num2;
        }

        try {
            switch (opcion) {
                case 1:
                    resultado = Calculadora::sumar(num1, num2);
                    cout << "Resultado: " << resultado << endl;
                    break;
                case 2:
                    resultado = Calculadora::restar(num1, num2);
                    cout << "Resultado: " << resultado << endl;
                    break;
                case 3:
                    resultado = Calculadora::multiplicar(num1, num2);
                    cout << "Resultado: " << resultado << endl;
                    break;
                case 4:
                    resultado = Calculadora::dividir(num1, num2);
                    cout << "Resultado: " << resultado << endl;
                    break;
                case 5:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opción no válida. Intente nuevamente.\n";
            }
        } catch (const exception &e) {
            cout << e.what() << endl;
        }

    } while (opcion != 5);

    return 0;
}
