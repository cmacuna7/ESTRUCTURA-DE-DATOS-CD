#include <iostream>
#include <list>
#include <string>
#include <locale>
#include <codecvt>
#include <cstdlib> // Para usar system("cls") y system("pause")
#include "Trie.cpp"

using namespace std;

int main() {
    // Configurar la consola para usar la configuración regional predeterminada del sistema
    setlocale(LC_ALL, "");

    Trie trie;
    list<wstring> bookTitles;
    wstring title;
    int choice;

    system("cls"); // Limpiar la consola al iniciar el programa

    do {
        system("cls"); // Limpiar la consola antes de mostrar el menú
        wcout << L"\nMenú:\n";
        wcout << L"1. Ingresar título del libro\n";
        wcout << L"2. Mostrar árbol trie\n";
        wcout << L"3. Mostrar recorrido realizado por el árbol trie\n";
        wcout << L"4. Salir\n";
        wcout << L"Seleccione una opción: ";
        wcin >> choice;
        wcin.ignore(); // Ignorar el salto de línea después de la elección

        system("cls"); // Limpiar la consola después de seleccionar una opción

        switch (choice) {
            case 1:
                wcout << L"Ingrese el título del libro: ";
                getline(wcin, title);
                bookTitles.push_back(title);
                trie.insert(title);
                break;
            case 2:
                wcout << L"\nTítulos de libros en el trie:\n";
                trie.display();
                wcout << L"\nAltura del trie: " << trie.getHeight() << endl;
                for (const auto& bookTitle : bookTitles) {
                    wcout << L"Profundidad del título \"" << bookTitle << L"\": " << trie.getDepth(bookTitle) << endl;
                    wcout << L"Nivel del título \"" << bookTitle << L"\": " << trie.getLevel(bookTitle) << endl;
                }
                break;
            case 3:
                wcout << L"\nRecorrido del trie:\n";
                trie.showTraversal();
                wcout << L"\nDatos almacenados:\n";
                for (const auto& bookTitle : bookTitles) {
                    wcout << bookTitle << endl;
                }
                break;
            case 4:
                wcout << L"Saliendo...\n";
                break;
            default:
                wcout << L"Opción no válida. Intente de nuevo.\n";
                break;
        }

        if (choice != 4) {
            system("pause"); // Pausar la consola
        }

    } while (choice != 4);

    return 0;
}
