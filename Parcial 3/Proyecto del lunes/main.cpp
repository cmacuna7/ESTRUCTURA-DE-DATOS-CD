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
#include <conio.h>
#include "bigO.cpp"

using namespace std;
using namespace std::chrono;

// Clases para el menú
class NodoMenu {
    public:
        string dato;
        NodoMenu* siguiente;
        NodoMenu* anterior;
        
        NodoMenu(string valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
    };
    
    class ListaCircularMenu {
    private:
        NodoMenu* primero;
        int tamano;
        
    public:
        ListaCircularMenu() : primero(nullptr), tamano(0) {}
        
        void insertar(string valor) {
            NodoMenu* nuevo = new NodoMenu(valor);
            if (!primero) {
                primero = nuevo;
                nuevo->siguiente = nuevo;
                nuevo->anterior = nuevo;
            } else {
                NodoMenu* ultimo = primero->anterior;
                nuevo->siguiente = primero;
                nuevo->anterior = ultimo;
                ultimo->siguiente = nuevo;
                primero->anterior = nuevo;
            }
            tamano++;
        }
        
        NodoMenu* getPrimero() { return primero; }
        int getTamano() { return tamano; }
        
        string obtenerOpcion(int indice) {
            if (indice >= tamano) return "";
            NodoMenu* actual = primero;
            for (int i = 0; i < indice; i++) {
                actual = actual->siguiente;
            }
            return actual->dato;
        }
};

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
    setlocale(LC_ALL, "");
    
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Mostrar funciones del .h (ingresar path)");
    menuOpciones.insertar("Calcular notacion asintotica de una funcion");
    menuOpciones.insertar("Generar graficas segun la notacion determinada");
    menuOpciones.insertar("Salir");
    
    int seleccion = 0;
    string filename = "funcion.txt";
    string code;
    string bigO;
    
    while (true) {
        system("cls");
        cout << "=== Analisis de Complejidad Algoritmica ===\n\n";
        NodoMenu* actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++) {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<\n";
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        } else if (tecla == 80) { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        } else if (tecla == '\r') { // Enter
            system("cls");
            int opcion = seleccion + 1;
            
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
                        cin.ignore();
                        if(idx < 0 || idx >= globalFunctions.size()){
                            cout << "Indice invalido." << endl;
                        } else {
                            cout << "Evaluando la funcion: " << globalFunctions[idx] << endl;
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
                case 4: {
                    cout << "Saliendo del programa..." << endl;
                    return 0;
                }
            }
            
            cout << "\nPresione cualquier tecla para continuar...";
            _getch();
        }
    }

    return 0;
}
