#include "Ayuda.h"
#include <iostream>
#include <conio.h>

using namespace std;

void mostrarAyuda() {
    system("cls");
    cout << "=== Ayuda ===\n";
    cout << "Este programa permite gestionar un registro de libros.\n";
    cout << "Opciones disponibles:\n";
    cout << "1. Agregar libro\n";
    cout << "2. Buscar libro\n";
    cout << "3. Eliminar libro\n";
    cout << "4. Ver todos los libros\n";
    cout << "5. Crear backup\n";
    cout << "6. Restaurar backup\n";
    cout << "Use las teclas de flecha para navegar por el menu y Enter para seleccionar.\n";
    cout << "Presione F1 para mostrar esta ayuda.\n";
    cout << "\nPresione cualquier tecla para volver al menu principal...\n";
    _getch();
}
