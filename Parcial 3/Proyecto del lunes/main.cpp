#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <sstream>
#include <clocale>
<<<<<<< HEAD
#include <cmath>   // Include cmath for log functions
#include <conio.h> // Include conio.h for _getch()
=======
#include <numeric>
#include <cmath>
#include "bigO.cpp"
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89

using namespace std;
using namespace std::chrono;

// Variables globales para almacenar funciones y notacion determinada
vector<string> globalFunctions;
string globalBigONotation = "";
string headerPath;
string cppPath;

vector<string> extractFunctionNames(const string &filePath)
{
    vector<string> functionNames;
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return functionNames;
    }

    string line;
    regex functionDeclRegex(R"(^\s*[\w<>:\s]+?\s+(\w+)\s*\([^)]*\)\s*;)");
    regex methodDefRegex(R"(^\s*[\w<>:\s]+?\s+(\w+)::(\w+)\s*\([^)]*\)\s*\{?)");
    smatch match;
<<<<<<< HEAD

    while (getline(file, line))
    {
        if (regex_search(line, match, functionRegex))
        {
            functionNames.push_back(match[2]);
=======
    
    while (getline(file, line)) {
        // Buscar declaraciones en .h
        if (regex_search(line, match, functionDeclRegex)) {
            functionNames.push_back(match[1]);  // Captura el nombre de la función
        }
        // Buscar métodos en .cpp (solo si tiene "Clase::")
        else if (regex_search(line, match, methodDefRegex)) {
            functionNames.push_back(match[2]);  // Captura el nombre del método
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89
        }
    }

    file.close();
    return functionNames;
}

<<<<<<< HEAD
void analyzeFunctionPerformance(vector<int> &inputs, vector<long long> &times)
{
    // Se asegura que data.txt se sobrescribe con datos correctos
    for (int n : inputs)
    {
        auto start = high_resolution_clock::now();
        // Se simula una función con trabajo proporcional a n, usando un factor de escalado
        auto lambdaFunction = [n]()
        {
            volatile long long sum = 0;
            int iterations = n * 1000; // Factor de escalado para generar tiempos medibles
            for (int i = 0; i < iterations; i++)
            {
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
    for (size_t i = 0; i < inputs.size(); i++)
    {
        file << inputs[i] << " " << times[i] << endl;
=======

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
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89
    }

    file.close();
<<<<<<< HEAD
}

string determineBestFit(const vector<int> &inputs, const vector<long long> &times)
{
    // Fit the data to different complexity models and select the best fit
    // Models: O(1), O(log n), O(n), O(n log n), O(n^2)
    vector<string> models = {"O(1)", "O(log n)", "O(n)", "O(n log n)", "O(n^2)"};
    vector<double> errors(models.size(), 0.0);

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        double n = inputs[i];
        double t = times[i];
        errors[0] += pow(t - 1, 2);          // O(1)
        errors[1] += pow(t - log(n), 2);     // O(log n)
        errors[2] += pow(t - n, 2);          // O(n)
        errors[3] += pow(t - n * log(n), 2); // O(n log n)
        errors[4] += pow(t - n * n, 2);      // O(n^2)
    }

    // Normalize errors by the number of data points
    for (auto &error : errors)
    {
        error /= inputs.size();
    }

    // Find the model with the minimum error
    auto minErrorIt = min_element(errors.begin(), errors.end());
    int bestFitIndex = distance(errors.begin(), minErrorIt);
    return models[bestFitIndex];
}

void determineBigONotation()
{
    // Se simula la evaluación de la función seleccionada
    vector<int> inputs = {10, 100, 1000, 10000, 50000};
    vector<long long> times;
    analyzeFunctionPerformance(inputs, times);
    // Determine the best fit for the function's performance
    globalBigONotation = determineBestFit(inputs, times);
    cout << "Notación asintótica estimada para la función evaluada: " << globalBigONotation << endl;
}

void graphBigONotation()
{
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

void displayMenu(int selectedOption)
{
    system("cls"); // Clear the console
    cout << "\nMenú:\n";
    cout << (selectedOption == 1 ? "> " : "  ") << "1. Mostrar funciones del .h (ingresar path)\n";
    cout << (selectedOption == 2 ? "> " : "  ") << "2. Calcular notación asintótica de una función (evaluación individual)\n";
    cout << (selectedOption == 3 ? "> " : "  ") << "3. Generar gráficas según la notación determinada\n";
    cout << (selectedOption == 4 ? "> " : "  ") << "4. Salir\n";
}

int main()
{
    setlocale(LC_ALL, ""); // Habilita la muestra de caracteres especiales en el CMD
    int opcion = 1;
    string headerPath;
    char key;

    do
    {
        displayMenu(opcion);
        key = _getch(); // Get key press

        if (key == 72)
        { // Up arrow key
            if (opcion > 1)
            {
                opcion--;
            }
        }
        else if (key == 80)
        { // Down arrow key
            if (opcion < 4)
            {
                opcion++;
            }
        }
        else if (key == 13)
        { // Enter key
            switch (opcion)
            {
            case 1:
            {
=======
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
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89
                cout << "Ingrese el path del archivo .h: ";
                getline(cin, headerPath);
                globalFunctions = extractFunctionNames(headerPath);
                if (globalFunctions.empty())
                {
                    cout << "No se encontraron funciones o no se pudo abrir el archivo." << endl;
                }
                else
                {
                    cout << "Funciones encontradas:" << endl;
                    for (size_t i = 0; i < globalFunctions.size(); i++)
                    {
                        cout << i << ": " << globalFunctions[i] << endl;
                    }
                    // Asumimos que el archivo .cpp tiene el mismo nombre que el archivo .h
                    cppPath = headerPath.substr(0, headerPath.find_last_of('.')) + ".cpp";
                }
                system("pause");
                break;
            }
<<<<<<< HEAD
            case 2:
            {
                if (globalFunctions.empty())
                {
                    cout << "Primero ingrese el path y extraiga las funciones en la opción 1." << endl;
                }
                else
                {
                    cout << "Seleccione el índice de la función a evaluar:" << endl;
                    for (size_t i = 0; i < globalFunctions.size(); i++)
                    {
=======
            case 2: {
                if(globalFunctions.empty()){
                    cout << "Primero ingrese el path y extraiga las funciones en la opcion 1." << endl;
                } else {
                    cout << "Seleccione el indice de la funcion a evaluar:" << endl;
                    for (size_t i = 0; i < globalFunctions.size(); i++) {
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89
                        cout << i << ": " << globalFunctions[i] << endl;
                    }
                    int idx;
                    cin >> idx;
                    cin.ignore(); // limpiar buffer
<<<<<<< HEAD
                    if (idx < 0 || idx >= globalFunctions.size())
                    {
                        cout << "Índice inválido." << endl;
                    }
                    else
                    {
                        cout << "Evaluando la función: " << globalFunctions[idx] << endl;
                        determineBigONotation();
=======
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
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89
                    }
                }
                system("pause");
                break;
            }
<<<<<<< HEAD
            case 3:
            {
                if (globalBigONotation.empty())
                {
                    cout << "Primero calcule la notación asintótica en la opción 2." << endl;
                }
                else
                {
                    graphBigONotation();
=======
            case 3: {
                if(bigO.empty()){
                    cout << "Primero calcule la notacion Big O de una funcion en la opcion 2." << endl;
                } else {
                    generarGrafica(bigO);
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89
                }
                system("pause");
                break;
            }
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
<<<<<<< HEAD
                cout << "Opción no válida, intente de nuevo." << endl;
            }
=======
                cout << "Opcion no valida, intente de nuevo." << endl;
>>>>>>> c173680d4113dfb9ebdeaf1b7b9e1b80956eec89
        }
    } while (opcion != 4);

    return 0;
}
