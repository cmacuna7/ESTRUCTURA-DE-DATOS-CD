#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <sstream>
#include <clocale>
#include <cmath>   // Include cmath for log functions
#include <conio.h> // Include conio.h for _getch()

using namespace std;
using namespace std::chrono;

// Variables globales para almacenar funciones y notacion determinada
vector<string> globalFunctions;
string globalBigONotation = "";

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
    regex functionRegex(R"((\w+)\s+(\w+)\s*\(([^)]*)\)\s*;)");
    smatch match;

    while (getline(file, line))
    {
        if (regex_search(line, match, functionRegex))
        {
            functionNames.push_back(match[2]);
        }
    }

    file.close();
    return functionNames;
}

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
    }
    file.close();
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
                }
                system("pause");
                break;
            }
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
                        cout << i << ": " << globalFunctions[i] << endl;
                    }
                    int idx;
                    cin >> idx;
                    cin.ignore(); // limpiar buffer
                    if (idx < 0 || idx >= globalFunctions.size())
                    {
                        cout << "Índice inválido." << endl;
                    }
                    else
                    {
                        cout << "Evaluando la función: " << globalFunctions[idx] << endl;
                        determineBigONotation();
                    }
                }
                system("pause");
                break;
            }
            case 3:
            {
                if (globalBigONotation.empty())
                {
                    cout << "Primero calcule la notación asintótica en la opción 2." << endl;
                }
                else
                {
                    graphBigONotation();
                }
                system("pause");
                break;
            }
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida, intente de nuevo." << endl;
            }
        }
    } while (opcion != 4);

    return 0;
}
