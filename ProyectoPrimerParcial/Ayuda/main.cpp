#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "Ayuda.h"

using namespace std;

int main() {
    while (true) {
        if (_kbhit()) {
            char tecla = _getch();
            
            if (tecla == 59) {  // F1
                // Abrir una nueva ventana de consola que ejecute el programa de ayuda
                system("start cmd /K \"path_to_your_program\\ayuda.exe\"");
            }
        }
    }

    return 0;
}
