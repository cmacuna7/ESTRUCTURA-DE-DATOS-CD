#include "Menu.h"
#include "BackupManager.cpp"
#include "Ayuda.cpp"
#include <iostream>
#include "Validaciones.cpp" // Incluir la clase de validaciones
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
                string titulo, nombreAutor, isbn;
                string fechaNac, fechaPub;

                // Solicitar datos del libro con validaciones
                do {
                    cout << "Ingrese titulo: ";
                    cin >> ws; getline(cin, titulo);
                } while (!Validaciones::validarTextoNoVacio(titulo, "Titulo"));

                do {
                    cout << "Ingrese nombre del autor: ";
                    getline(cin, nombreAutor);
                } while (!Validaciones::validarTexto(nombreAutor, "Nombre del Autor"));

                // Solicitar fecha de nacimiento del autor
                do {
                    cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY): ";
                    getline(cin, fechaNac);
                } while (!Validaciones::validarFecha(fechaNac));

                // Solicitar ISBN
                do {
                    cout << "Ingrese ISBN: ";
                    getline(cin, isbn);
                } while (!Validaciones::validarIsbn(isbn));

                // Solicitar fecha de publicación
                do {
                    cout << "Ingrese fecha de publicacion del libro (DD-MM-YYYY): ";
                    getline(cin, fechaPub);
                } while (!Validaciones::validarFecha(fechaPub));

                // Crear los objetos necesarios
                Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                Persona autor(nombreAutor, fechaNacimientoAutor);
                Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                Libro libro(titulo, isbn, autor, fechaPublicacion);

                // Agregar libro a la lista
                lista.agregarLibro(libro);
            } else if (opciones[seleccion] == "Buscar libro") {
                string titulo;
                cout << "Ingrese el titulo del libro a buscar: ";
                cin >> ws; getline(cin, titulo);
                Nodo* libro = lista.buscarLibro(titulo);
                if (libro) {
                    libro->libro.mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            } else if (opciones[seleccion] == "Eliminar libro") {
                string titulo;
                cout << "Ingrese el titulo del libro a eliminar: ";
                cin >> ws; getline(cin, titulo);
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
                BackupManager::restaurarBackup(lista);  // Llama a la función para restaurar el backup
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
