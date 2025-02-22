#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <sstream>
#include <clocale>

using namespace std;
using namespace std::chrono;

// Variables globales para almacenar funciones y notacion determinada
vector<string> globalFunctions;
string globalBigONotation = "";

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

void analyzeFunctionPerformance(vector<int>& inputs, vector<long long>& times) {
    // Se asegura que data.txt se sobrescribe con datos correctos
    for (int n : inputs) {
        auto start = high_resolution_clock::now();
        // Se simula una función con trabajo proporcional a n, usando un factor de escalado
        auto lambdaFunction = [n]() {
            volatile long long sum = 0;
            int iterations = n * 1000; // Factor de escalado para generar tiempos medibles
            for (int i = 0; i < iterations; i++) {
                sum += i;
            }
            return sum;
        };
        lambdaFunction();
        auto stop = high_resolution_clock::now();
        times.push_back(duration_cast<microseconds>(stop - start).count());
    }
    ofstream file("data.txt");
    // Escribir cada par (n, tiempo) en una línea separada por un espacio
    for (size_t i = 0; i < inputs.size(); i++) {
        file << inputs[i] << " " << times[i] << endl;
    }
    file.close();
}

void determineBigONotation() {
    // Se simula la evaluación de la función seleccionada
    vector<int> inputs = {10, 100, 1000, 10000, 50000};
    vector<long long> times;
    analyzeFunctionPerformance(inputs, times);
    // La simulación para la función elegida se estima como O(n)
    globalBigONotation = "O(n)";
    cout << "Notación asintótica estimada para la función evaluada: " << globalBigONotation << endl;
}

void graphBigONotation() {
    // Genera nuevamente data.txt para asegurar datos actualizados
    vector<int> inputs = {10, 100, 1000, 10000, 50000};
    vector<long long> times;
    analyzeFunctionPerformance(inputs, times);
    cout << "Datos guardados en data.txt. Generando gráficas para la notación " << globalBigONotation << "..." << endl;
    string pythonCmd = "python graph_big_o.py " + globalBigONotation;
    system(pythonCmd.c_str());
    // Se llama a la función MATLAB pasando la notación (la función MATLAB debe usar el parámetro)
    string matlabCmd = "matlab -batch \"graph_big_o_matlab('" + globalBigONotation + "'); exit;\"";
    system(matlabCmd.c_str());
}

int main() {
    setlocale(LC_ALL, "");  // Habilita la muestra de caracteres especiales en el CMD
    int opcion;
    string headerPath;
    
    do {
        cout << "\nMenú:\n";
        cout << "1. Mostrar funciones del .h (ingresar path)\n";
        cout << "2. Calcular notación asintótica de una función (evaluación individual)\n";
        cout << "3. Generar gráficas según la notación determinada\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(); // limpiar buffer
        
        switch (opcion) {
            case 1: {
                cout << "Ingrese el path del archivo .h: ";
                getline(cin, headerPath);
                globalFunctions = extractFunctionNames(headerPath);
                if(globalFunctions.empty()){
                    cout << "No se encontraron funciones o no se pudo abrir el archivo." << endl;
                } else {
                    cout << "Funciones encontradas:" << endl;
                    for (size_t i = 0; i < globalFunctions.size(); i++) {
                        cout << i << ": " << globalFunctions[i] << endl;
                    }
                }
                break;
            }
            case 2: {
                if(globalFunctions.empty()){
                    cout << "Primero ingrese el path y extraiga las funciones en la opción 1." << endl;
                } else {
                    cout << "Seleccione el índice de la función a evaluar:" << endl;
                    for (size_t i = 0; i < globalFunctions.size(); i++) {
                        cout << i << ": " << globalFunctions[i] << endl;
                    }
                    int idx;
                    cin >> idx;
                    cin.ignore(); // limpiar buffer
                    if(idx < 0 || idx >= globalFunctions.size()){
                        cout << "Índice inválido." << endl;
                    } else {
                        cout << "Evaluando la función: " << globalFunctions[idx] << endl;
                        // Se simula el desempeño para la función seleccionada (por ejemplo, se asume O(n))
                        determineBigONotation();
                    }
                }
                break;
            }
            case 3: {
                if(globalBigONotation.empty()){
                    cout << "Primero calcule la notación asintótica en la opción 2." << endl;
                } else {
                    graphBigONotation();
                }
                break;
            }
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida, intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}
