#include <iostream>
#include <chrono>
#include <graphics.h>

using namespace std;

// Función recursiva para calcular el factorial de un número
int factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;

    return n * factorial(n - 1);
}

void plotFactorial(int num)
{
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);

    setcolor(WHITE);
    line(50, 450, 50, 50);   // Eje Y
    line(50, 450, 650, 450); // Eje X

    setcolor(YELLOW);
    char label1[] = "Factorial";
    char label2[] = "Numero";
    outtextxy(30, 30, label1);
    outtextxy(600, 460, label2);

    for (int n = 1; n <= num; n++)
    {
        int result = factorial(n);

        int x = 50 + n * 20;
        int y = 450 - result / 1000;
        setcolor(RED);
        circle(x, y, 5);
        floodfill(x, y, RED);
    }

    delay(10000);
    closegraph();
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    int num;
    cout << "Ingrese un numero: ";
    cin >> num;
    cout << "El factorial de " << num << " es: " << factorial(num) << endl;

    plotFactorial(num);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de ejecucion: " << duration.count() << " ms" << std::endl;

    return 0;
}
