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
#include "bigO.cpp"

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


void generarGrafica(const string& bigO) {
    // Ejecutar Python
    string comandoPython = "python graph_big_o.py \"" + bigO + "\"";
    system(comandoPython.c_str());
    
    // Ejecutar MATLAB (requiere MATLAB instalado y en el PATH)
    string comandoMatlab = "matlab -batch \"graph_big_o('" + bigO + "'); exit\"";
    system(comandoMatlab.c_str());
}


void showFunctionContent(const string& filePath, const string& functionName) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    ofstream outFile("funcion.txt");
    if (!outFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de salida." << endl;
        return;
    }

    string line;
    bool inFunction = false;
    int braceCount = 0;

    while (getline(file, line)) {
        if (!inFunction) {
            if (line.find(functionName + "(") != string::npos && line.find("{") != string::npos) {
                inFunction = true;
                cout << line << endl;
                outFile << line << endl;
                braceCount = count(line.begin(), line.end(), '{') - count(line.begin(), line.end(), '}');
            } else if (line.find(functionName + "(") != string::npos) {
                inFunction = true;
                cout << line << endl;
                outFile << line << endl;
                while (getline(file, line) && line.find("{") == string::npos) {
                    cout << line << endl;
                    outFile << line << endl;
                }
                cout << line << endl;
                outFile << line << endl;
                braceCount = count(line.begin(), line.end(), '{') - count(line.begin(), line.end(), '}');
            }
        } else {
            cout << line << endl;
            outFile << line << endl;
            braceCount += count(line.begin(), line.end(), '{') - count(line.begin(), line.end(), '}');
            if (braceCount == 0) {
                break;
            }
        }
    }

    file.close();
    outFile.close();
}

int main() {
    setlocale(LC_ALL, "");  // Habilita la muestra de caracteres especiales en el CMD
    int opcion;
    string filename = "funcion.txt";
    string code;
    string bigO;
    
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
                        code = readFile(filename);
                        bigO = determineBigO(code);
                        cout << "La notacion Big O de la funcion es: " << bigO << endl;
                    }
                }
                break;
            }
            case 3: {
                if(bigO.empty()){
                    cout << "Primero calcule la notacion Big O de una funcion en la opcion 2." << endl;
                } else {
                    generarGrafica(bigO);
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
