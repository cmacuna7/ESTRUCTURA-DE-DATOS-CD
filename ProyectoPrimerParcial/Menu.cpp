#include "Menu.h"
#include "Backup.cpp"
#include "Ayuda.cpp"
#include <iostream>
#include <conio.h> // Para captura de teclas
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

void mostrarMenu(ListaCircularDoble& lista) {
    vector<string> opciones = {
        "Agregar libro",
        "Buscar libro",
        "Eliminar libro",
        "Ver todos los libros",
        "Crear backup",
        "Restaurar backup",
        "Salir"
    };
    int seleccion = 0;

    while (true) {
        system("cls");
        cout << "=== Menu Principal ===\n";
        for (size_t i = 0; i < opciones.size(); ++i) {
            if (i == seleccion)
                cout << ">> " << opciones[i] << " <<\n";
            else
                cout << "   " << opciones[i] << endl;
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            seleccion = (seleccion - 1 + opciones.size()) % opciones.size();
        } else if (tecla == 80) { // Flecha Abajo
            seleccion = (seleccion + 1) % opciones.size();
        } else if (tecla == '\r') { // Enter
            if (opciones[seleccion] == "Agregar libro") {
                string titulo, autor, isbn;
                int anio;
                cout << "Ingrese titulo: "; cin >> ws; getline(cin, titulo);
                cout << "Ingrese autor: "; getline(cin, autor);
                cout << "Ingrese ISBN: "; cin >> isbn;
                cout << "Ingrese anio: "; cin >> anio;
                Libro libro(titulo, autor, isbn, anio);
                lista.agregarLibro(libro);
            } else if (opciones[seleccion] == "Buscar libro") {
                string titulo;
                cout << "Ingrese el titulo del libro a buscar: "; cin >> ws; getline(cin, titulo);
                Nodo* libro = lista.buscarLibro(titulo);
                if (libro) {
                    libro->libro.mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            } else if (opciones[seleccion] == "Eliminar libro") {
                string titulo;
                cout << "Ingrese el titulo del libro a eliminar: "; cin >> ws; getline(cin, titulo);
                lista.eliminarLibro(titulo);
            } else if (opciones[seleccion] == "Ver todos los libros") {
                lista.imprimirLibros();
            } else if (opciones[seleccion] == "Crear backup") {
                time_t ahora = time(0);
                tm* tiempo = localtime(&ahora);
                stringstream ss;
                ss << (1900 + tiempo->tm_year) << "_" << (1 + tiempo->tm_mon) << "_" << tiempo->tm_mday << "_"
                << tiempo->tm_hour << "_" << tiempo->tm_min << "_" << tiempo->tm_sec << ".txt";
                lista.crearBackup(ss.str());
            } else if (opciones[seleccion] == "Restaurar backup") {
                restaurarBackup(lista);  // Llama a la función para restaurar el backup
            } else if (opciones[seleccion] == "Salir") {
                break;
            }
            cout << "Presione cualquier tecla para continuar...\n";
            _getch();
        } else if (tecla == 59) { // F1
            mostrarAyuda();
        }
    }
}
