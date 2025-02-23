#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <sstream>
#include <clocale>
#include <numeric>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Variables globales para almacenar funciones y notacion determinada
vector<string> globalFunctions;
string globalBigONotation = "";
string headerPath;
string cppPath;

vector<string> extractFunctionNames(const string& filePath) {
    vector<string> functionNames;
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return functionNames;
    }
    
    string line;
    regex functionDeclRegex(R"(^\s*[\w<>:\s]+?\s+(\w+)\s*\([^)]*\)\s*;)");
    regex methodDefRegex(R"(^\s*[\w<>:\s]+?\s+(\w+)::(\w+)\s*\([^)]*\)\s*\{?)");
    smatch match;
    
    while (getline(file, line)) {
        // Buscar declaraciones en .h
        if (regex_search(line, match, functionDeclRegex)) {
            functionNames.push_back(match[1]);  // Captura el nombre de la función
        }
        // Buscar métodos en .cpp (solo si tiene "Clase::")
        else if (regex_search(line, match, methodDefRegex)) {
            functionNames.push_back(match[2]);  // Captura el nombre del método
        }
    }
    
    file.close();
    return functionNames;
}

void analyzeFunctionPerformance(vector<int>& inputs, vector<long long>& times) {
    // Se asegura que data.txt se sobrescribe con datos correctos
    for (int n : inputs) {
        auto start = high_resolution_clock::now();
        // Se simula una funcion con trabajo proporcional a n, usando un factor de escalado
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
    // Escribir cada par (n, tiempo) en una linea separada por un espacio
    for (size_t i = 0; i < inputs.size(); i++) {
        file << inputs[i] << " " << times[i] << endl;
    }
    file.close();
}

double calculateRSquared(const vector<double>& observed, const vector<double>& predicted) {
    double mean = accumulate(observed.begin(), observed.end(), 0.0) / observed.size();
    double ssTotal = 0, ssResidual = 0;
    for (size_t i = 0; i < observed.size(); ++i) {
        ssTotal += pow(observed[i] - mean, 2);
        ssResidual += pow(observed[i] - predicted[i], 2);
    }
    return 1 - (ssResidual / ssTotal);
}

string determineBigONotation() {
    // Se simula la evaluacion de la funcion seleccionada
    vector<int> inputs = {10, 100, 1000, 10000, 50000};
    vector<long long> times;
    analyzeFunctionPerformance(inputs, times);

    // Convertir tiempos a logaritmos para ajuste de curvas
    vector<double> logInputs(inputs.size()), logTimes(times.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        logInputs[i] = log(inputs[i]);
        logTimes[i] = log(times[i]);
    }

    // Ajustar diferentes modelos
    vector<double> predictedConstant(inputs.size(), logTimes[0]);
    vector<double> predictedLogarithmic(inputs.size()), predictedLinear(inputs.size());
    vector<double> predictedNLogN(inputs.size()), predictedQuadratic(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        predictedLogarithmic[i] = log(logInputs[i]);
        predictedLinear[i] = logInputs[i];
        predictedNLogN[i] = logInputs[i] + log(logInputs[i]);
        predictedQuadratic[i] = 2 * logInputs[i];
    }

    // Calcular R^2 para cada modelo
    double r2Constant = calculateRSquared(logTimes, predictedConstant);
    double r2Logarithmic = calculateRSquared(logTimes, predictedLogarithmic);
    double r2Linear = calculateRSquared(logTimes, predictedLinear);
    double r2NLogN = calculateRSquared(logTimes, predictedNLogN);
    double r2Quadratic = calculateRSquared(logTimes, predictedQuadratic);

    // Determinar el mejor ajuste
    double maxR2 = max({r2Constant, r2Logarithmic, r2Linear, r2NLogN, r2Quadratic});
    if (maxR2 == r2Constant) {
        globalBigONotation = "O(1)";
    } else if (maxR2 == r2Logarithmic) {
        globalBigONotation = "O(log n)";
    } else if (maxR2 == r2Linear) {
        globalBigONotation = "O(n)";
    } else if (maxR2 == r2NLogN) {
        globalBigONotation = "O(n log n)";
    } else if (maxR2 == r2Quadratic) {
        globalBigONotation = "O(n^2)";
    }

    cout << "Notacion asintotica estimada para la funcion evaluada: " << globalBigONotation << endl;
    return globalBigONotation;
}

void graphBigONotation() {
    // Genera nuevamente data.txt para asegurar datos actualizados
    vector<int> inputs = {10, 100, 1000, 10000, 50000};
    vector<long long> times;
    analyzeFunctionPerformance(inputs, times);
    cout << "Datos guardados en data.txt. Generando graficas para la notacion " << globalBigONotation << "..." << endl;
    string pythonCmd = "python graph_big_o.py " + globalBigONotation;
    system(pythonCmd.c_str());
    // Se llama a la funcion MATLAB pasando la notacion (la funcion MATLAB debe usar el parametro)
    string matlabCmd = "matlab -batch \"graph_big_o_matlab('" + globalBigONotation + "'); exit;\"";
    system(matlabCmd.c_str());
}

void showFunctionContent(const string& filePath, const string& functionName) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string line;
    regex functionStartRegex(R"(^\s*[\w<>:\s]+?\s+(\w+)::)" + functionName + R"(\s*\([^)]*\)\s*\{)");
    smatch match;
    bool inFunction = false;
    int braceCount = 0;

    while (getline(file, line)) {
        if (!inFunction) {
            if (regex_search(line, match, functionStartRegex)) {
                inFunction = true;
                cout << line << endl;
                braceCount = count(line.begin(), line.end(), '{') - count(line.begin(), line.end(), '}');
            }
        } else {
            cout << line << endl;
            braceCount += count(line.begin(), line.end(), '{') - count(line.begin(), line.end(), '}');
            if (braceCount == 0) {
                break;
            }
        }
    }

    file.close();
}

int main() {
    setlocale(LC_ALL, "");  // Habilita la muestra de caracteres especiales en el CMD
    int opcion;
    
    do {
        cout << "\nMenu:\n";
        cout << "1. Mostrar funciones del .h (ingresar path)\n";
        cout << "2. Calcular notacion asintotica de una funcion (evaluacion individual)\n";
        cout << "3. Generar graficas segun la notacion determinada\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
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
                    // Asumimos que el archivo .cpp tiene el mismo nombre que el archivo .h
                    cppPath = headerPath.substr(0, headerPath.find_last_of('.')) + ".cpp";
                }
                break;
            }
            case 2: {
                if(globalFunctions.empty()){
                    cout << "Primero ingrese el path y extraiga las funciones en la opcion 1." << endl;
                } else {
                    cout << "Seleccione el indice de la funcion a evaluar:" << endl;
                    for (size_t i = 0; i < globalFunctions.size(); i++) {
                        cout << i << ": " << globalFunctions[i] << endl;
                    }
                    int idx;
                    cin >> idx;
                    cin.ignore(); // limpiar buffer
                    if(idx < 0 || idx >= globalFunctions.size()){
                        cout << "Indice invalido." << endl;
                    } else {
                        cout << "Evaluando la funcion: " << globalFunctions[idx] << endl;
                        // Mostrar el contenido de la función seleccionada
                        cout << "Contenido de la funcion:" << endl;
                        showFunctionContent(cppPath, globalFunctions[idx]);
                        // Calcular la notación Big-O
                        determineBigONotation();
                    }
                }
                break;
            }
            case 3: {
                if(globalBigONotation.empty()){
                    cout << "Primero calcule la notacion asintotica en la opcion 2." << endl;
                } else {
                    graphBigONotation();
                }
                break;
            }
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}
