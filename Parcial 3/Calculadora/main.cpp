#include <iostream>
#include <vector>
#include "Calculadora.cpp"

using namespace std;

void mostrarMenu() {
    cout << "\nCalculadora - Operaciones\n";
    cout << "Operaciones Básicas O(1):\n";
    cout << "1. Sumar\n";
    cout << "2. Restar\n";
    cout << "3. Multiplicar\n";
    cout << "4. Dividir\n";
    cout << "\nOperaciones Avanzadas:\n";
    cout << "5. Potencia (O(log n))\n";
    cout << "6. Suma Serie (O(n))\n";
    cout << "7. Suma Ordenada (O(n log n))\n";
    cout << "8. Multiplicar Matrices (O(n²))\n";
    cout << "9. Fibonacci (O(2^n))\n";
    cout << "10. Salir\n";
}

int main() {
    int opcion;
    double num1, num2, resultado;

    do {
        mostrarMenu();
        cout << "Seleccione una opción: ";
        cin >> opcion;

        try {
            switch (opcion) {
                case 1: case 2: case 3: case 4: {
                    cout << "Ingrese el primer número: ";
                    cin >> num1;
                    cout << "Ingrese el segundo número: ";
                    cin >> num2;
                    
                    switch (opcion) {
                        case 1: resultado = Calculadora::sumar(num1, num2); break;
                        case 2: resultado = Calculadora::restar(num1, num2); break;
                        case 3: resultado = Calculadora::multiplicar(num1, num2); break;
                        case 4: resultado = Calculadora::dividir(num1, num2); break;
                    }
                    cout << "Resultado: " << resultado << endl;
                    break;
                }
                case 5: {
                    double base;
                    int exponente;
                    cout << "Ingrese la base: ";
                    cin >> base;
                    cout << "Ingrese el exponente: ";
                    cin >> exponente;
                    resultado = Calculadora::potenciaLogaritmica(base, exponente);
                    cout << "Resultado: " << resultado << endl;
                    break;
                }
                case 6: {
                    vector<double> numeros;
                    int n;
                    cout << "Ingrese la cantidad de números: ";
                    cin >> n;
                    cout << "Ingrese los números:\n";
                    for (int i = 0; i < n; i++) {
                        double num;
                        cin >> num;
                        numeros.push_back(num);
                    }
                    resultado = Calculadora::sumaSerie(numeros);
                    cout << "Suma de la serie: " << resultado << endl;
                    break;
                }
                case 7: {
                    vector<double> numeros;
                    int n;
                    cout << "Ingrese la cantidad de números: ";
                    cin >> n;
                    cout << "Ingrese los números:\n";
                    for (int i = 0; i < n; i++) {
                        double num;
                        cin >> num;
                        numeros.push_back(num);
                    }
                    resultado = Calculadora::sumaOrdenada(numeros);
                    cout << "Suma ordenada: " << resultado << endl;
                    break;
                }
                case 8: {
                    int n;
                    cout << "Ingrese el tamaño de las matrices cuadradas: ";
                    cin >> n;
                    vector<vector<double>> matriz1(n, vector<double>(n));
                    vector<vector<double>> matriz2(n, vector<double>(n));
                    
                    cout << "Ingrese los elementos de la primera matriz:\n";
                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                            cin >> matriz1[i][j];
                    
                    cout << "Ingrese los elementos de la segunda matriz:\n";
                    for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                            cin >> matriz2[i][j];
                    
                    auto resultado = Calculadora::multiplicarMatrices(matriz1, matriz2);
                    cout << "Resultado de la multiplicación:\n";
                    for (const auto& fila : resultado) {
                        for (double elem : fila)
                            cout << elem << " ";
                        cout << endl;
                    }
                    break;
                }
                case 9: {
                    int n;
                    cout << "Ingrese el número para calcular Fibonacci (advertencia: números grandes pueden tardar mucho): ";
                    cin >> n;
                    resultado = Calculadora::fibonacciExponencial(n);
                    cout << "Fibonacci(" << n << ") = " << resultado << endl;
                    break;
                }
                case 10:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opción no válida. Intente nuevamente.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (opcion != 10);

    return 0;
}