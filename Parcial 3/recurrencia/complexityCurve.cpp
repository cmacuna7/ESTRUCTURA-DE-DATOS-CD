#include <iostream>
#include <chrono>
#include <graphics.h>
#include <cmath>

using namespace std;

// Función recursiva de búsqueda binaria
int busquedaBinaria(int arr[], int inicio, int fin, int objetivo)
{
    if (inicio > fin)
        return -1;

    int medio = inicio + (fin - inicio) / 2;

    if (arr[medio] == objetivo)
        return medio;

    if (arr[medio] > objetivo)
        return busquedaBinaria(arr, inicio, medio - 1, objetivo);

    return busquedaBinaria(arr, medio + 1, fin, objetivo);
}

void plotComplexityCurve()
{
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);

    int maxN = 1000;
    int arr[maxN];
    for (int i = 0; i < maxN; i++)
    {
        arr[i] = i;
    }

    setcolor(WHITE);
    line(50, 450, 50, 50);   // Eje Y
    line(50, 450, 650, 450); // Eje X

    setcolor(YELLOW);
    outtextxy(30, 30, "Tiempo (ms)");
    outtextxy(600, 460, "Tamaño del arreglo");

    for (int n = 1; n <= maxN; n += 10)
    {
        auto start = chrono::high_resolution_clock::now();
        busquedaBinaria(arr, 0, n - 1, n - 1);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duration = end - start;

        int x = 50 + n / 2;
        int y = 450 - duration.count() * 10;
        putpixel(x, y, RED);
    }

    delay(10000);
    closegraph();
}

int main()
{
    plotComplexityCurve();
    return 0;
}
