#include <iostream>
#include <chrono>
#include <graphics.h>

using namespace std;

// Función para combinar dos mitades ordenadas del arreglo
void merge(int arr[], int izquierda, int medio, int derecha)
{
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    int L[n1], R[n2];

    // Copiamos los elementos a los subarreglos temporales
    for (int i = 0; i < n1; i++)
        L[i] = arr[izquierda + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;

    // Mezclamos los subarreglos ordenados en el arreglo original
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiamos los elementos restantes de L[]
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiamos los elementos restantes de R[]
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva Merge Sort
void mergeSort(int arr[], int izquierda, int derecha)
{
    if (izquierda < derecha)
    {
        // Calculamos el punto medio
        int medio = izquierda + (derecha - izquierda) / 2;

        /*
        Aquí se realizan las llamadas recursivas dividiendo el problema en dos mitades:
        - Llamada a mergeSort() para la mitad izquierda:  T(n/2)
        - Llamada a mergeSort() para la mitad derecha:   T(n/2)

        Después de ambas llamadas, se ejecuta la función merge() que combina los resultados en O(n).

        Esto genera la ecuación de recurrencia:
            T(n) = 2T(n/2) + O(n)
        */

        mergeSort(arr, izquierda, medio);   // Primera llamada recursiva: T(n/2)
        mergeSort(arr, medio + 1, derecha); // Segunda llamada recursiva: T(n/2)

        merge(arr, izquierda, medio, derecha); // Mezclamos los resultados en O(n)

        // Visualización gráfica
        cleardevice();
        for (int i = 0; i <= derecha; i++)
        {
            setcolor(WHITE);
            rectangle(50 + i * 20, 400, 70 + i * 20, 400 - arr[i] * 2);
            char num[5];
            sprintf(num, "%d", arr[i]);
            outtextxy(55 + i * 20, 410, num);
        }
        delay(1000);
    }
}

// Función para imprimir el arreglo
void imprimirArreglo(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Arreglo original: ";
    imprimirArreglo(arr, n);

    // Inicialización de la ventana gráfica
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);

    mergeSort(arr, 0, n - 1); // Llamamos a Merge Sort

    cout << "Arreglo ordenado: ";
    imprimirArreglo(arr, n);

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
