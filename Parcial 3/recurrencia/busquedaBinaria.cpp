#include <iostream>
#include <chrono>
#include <graphics.h>

using namespace std;

// Función recursiva de búsqueda binaria
int busquedaBinaria(int arr[], int inicio, int fin, int objetivo)
{
    if (inicio > fin)
        return -1; // Caso base: Si el rango es inválido, el elemento no está en el arreglo.

    int medio = inicio + (fin - inicio) / 2; // Se calcula el índice medio (para evitar desbordamiento de enteros).

    // Visualización gráfica
    cleardevice();
    for (int i = 0; i < 8; i++)
    {
        if (i >= inicio && i <= fin)
        {
            setcolor(GREEN);
        }
        else
        {
            setcolor(RED);
        }
        rectangle(50 + i * 50, 200, 100 + i * 50, 250);
        char num[3];
        sprintf(num, "%d", arr[i]);
        outtextxy(65 + i * 50, 215, num);
    }
    delay(1000);

    if (arr[medio] == objetivo)
        return medio; // Caso base: Si el elemento en la posición media es el buscado, se retorna su índice.

    // Aquí ocurre la **llamada recursiva**, dividiendo el problema a la mitad en cada paso.
    if (arr[medio] > objetivo)
        return busquedaBinaria(arr, inicio, medio - 1, objetivo); // Buscar en la mitad izquierda.

    return busquedaBinaria(arr, medio + 1, fin, objetivo); // Buscar en la mitad derecha.
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15}; // Arreglo ordenado
    int n = sizeof(arr) / sizeof(arr[0]);    // Tamaño del arreglo
    int objetivo;

    cout << "Ingrese el numero a buscar: ";
    cin >> objetivo;

    // Inicialización de la ventana gráfica
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);

    int resultado = busquedaBinaria(arr, 0, n - 1, objetivo);

    if (resultado != -1)
        cout << "Elemento encontrado en la posicion: " << resultado << endl;
    else
    {
        cout << "Elemento no encontrado" << endl;
    }

    // Captura el tiempo de finalización
    auto end = std::chrono::high_resolution_clock::now();
    // Calcula la duración en milisegundos
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de ejecucion: " << duration.count() << " ms" << std::endl;

    // Espera antes de cerrar la ventana gráfica
    delay(5000);
    closegraph();

    return 0;
}

/*
    *** Análisis de Recurrencia ***

    La función realiza una llamada recursiva en cada paso, reduciendo el tamaño del problema a la mitad.

    - La ecuación de recurrencia es:

      T(n) = T(n/2) + O(1)

      Explicación:
      - T(n) representa el tiempo de ejecución para una entrada de tamaño "n".
      - T(n/2) representa la llamada recursiva donde reducimos el problema a la mitad.
      - O(1) representa el costo constante de calcular el índice medio y hacer comparaciones.
*/