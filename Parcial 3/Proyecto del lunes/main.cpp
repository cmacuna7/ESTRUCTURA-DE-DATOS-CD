#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace std::chrono;

vector<string> extractFunctionNames(const string& filePath) {
    vector<string> functionNames;
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return functionNames;
    }
    
    string line;
    regex functionRegex(R"((\w+)\s+(\w+)\s*\(([^)]*)\)\s*;)");
    smatch match;
    
    while (getline(file, line)) {
        if (regex_search(line, match, functionRegex)) {
            functionNames.push_back(match[2]);
        }
    }
    
    file.close();
    return functionNames;
}

void analyzeFunctionPerformance() {
    vector<int> inputs = {10, 100, 1000, 10000, 50000};
    vector<long long> times;
    
    for (int n : inputs) {
        auto start = high_resolution_clock::now();
        
        // Simulación de una función lambda
        auto lambdaFunction = [n]() {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += i;
            }
            return sum;
        };
        
        lambdaFunction();
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        times.push_back(duration.count());
    }
    
    ofstream file("data.txt");
    for (size_t i = 0; i < inputs.size(); i++) {
        file << inputs[i] << " " << times[i] << endl;
    }
    file.close();
    
    cout << "Datos guardados en data.txt. Generando gráficos..." << endl;
    system("python graph_big_o.py");
    system("matlab -batch \"run('graph_big_o_matlab.m'); exit;\"");
}

int main() {
    string filePath = "C:/ESPE/1992-ESTRUCTURA DE DATOS/ESTRUCTURA-DE-DATOS-CD/Parcial 3/Calculadora/Calculadora.h";
    int opcion;
    
    do {
        cout << "\nMenú:\n";
        cout << "1. Mostrar funciones del .h\n";
        cout << "2. Mostrar gráficas en Python y MATLAB\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                vector<string> functions = extractFunctionNames(filePath);
                cout << "Funciones encontradas:" << endl;
                for (const auto& func : functions) {
                    cout << "- " << func << endl;
                }
                break;
            }
            case 2:
                analyzeFunctionPerformance();
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida, intente de nuevo." << endl;
        }
    } while (opcion != 3);

    return 0;
}
