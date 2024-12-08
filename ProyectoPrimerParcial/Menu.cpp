#include "Menu.h"
#include "BackupManager.cpp"
#include <iostream>
#include "Validaciones.cpp" // Incluir el header de Validaciones
#include <conio.h> // Para captura de teclas
#include <vector>
#include <sstream>
#include <ctime>
#include "pdf_generator.h"

using namespace std;

void mostrarMenu(ListaCircularDoble& lista) {
    vector<string> opciones = {
        "Agregar libro",
        "Buscar libro",
        "Eliminar libro",
        "Ver todos los libros",
        "Exportar en archivo PDF",
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
                string titulo, isbn, isni;
                string fechaPub, fechaNac;
                Persona autor;

                // Solicitar titulo del libro
                do {
                    cout << "Ingrese título del libro: ";
                    getline(cin, titulo);
                } while (!Validaciones::validarTitulo(titulo, "Título"));

                // Solicitar ISBN
                do {
                    cout << "Ingrese ISBN: ";
                    getline(cin, isbn);
                } while (!Validaciones::validarIsbn(isbn));

                // Verificar si el ISBN ya existe
                Nodo* libroExistente = lista.buscarLibroPorIsbn(isbn);
                if (libroExistente) {
                    cout << "El ISBN ya existe. Información del libro existente:\n";
                    libroExistente->libro.mostrar();
                } else {
                    // Solicitar ISNI del autor
                    do {
                        cout << "Ingrese ISNI del autor: ";
                        getline(cin, isni);
                    } while (!Validaciones::validarIsni(isni));

                    // Verificar si el ISNI ya existe
                    Persona autorExistente = lista.buscarAutorPorIsni(isni);
                    if (autorExistente.getNombre() != "") {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = autorExistente;
                    } else {
                        string nombreAutor;

                        // Solicitar nombre del autor
                        do {
                            cout << "Ingrese nombre del autor: ";
                            getline(cin, nombreAutor);
                        } while (!Validaciones::validarTituloNombre(nombreAutor, "Nombre del Autor"));

                        // Solicitar fecha de nacimiento del autor
                        do {
                            cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY): ";
                            getline(cin, fechaNac);
                        } while (!Validaciones::validarFecha(fechaNac));

                        // Crear el autor
                        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                        autor = Persona(nombreAutor, isni, fechaNacimientoAutor);
                    }

                    // Solicitar fecha de publicación del libro
                    do {
                        cout << "Ingrese fecha de publicación del libro (DD-MM-YYYY): ";
                        getline(cin, fechaPub);
                    } while (!Validaciones::validarFechaPublicacion(fechaPub, fechaNac));

                    // Crear el libro
                    Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                    Libro libro(titulo, isbn, autor, fechaPublicacion);

                    // Agregar libro a la lista
                    lista.agregarLibro(libro);
                }
            } else if (opciones[seleccion] == "Buscar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a buscar: ";
                cin >> ws; getline(cin, isbn);
                Nodo* libro = lista.buscarLibroPorIsbn(isbn);
                if (libro) {
                    libro->libro.mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            } else if (opciones[seleccion] == "Eliminar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a eliminar: ";
                cin >> ws; getline(cin, isbn);
                // Eliminar usando ISBN
                Nodo* libroAEliminar = lista.buscarLibroPorIsbn(isbn);
                if (libroAEliminar) {
                    string titulo = libroAEliminar->libro.getTitulo();
                    lista.eliminarLibro(titulo);
                } else {
                    cout << "Libro no encontrado con ISBN: " << isbn << endl;
                }
            } else if (opciones[seleccion] == "Ver todos los libros") {
                lista.imprimirLibros();
            }else if (opciones[seleccion] == "Exportar en archivo PDF") {

                    const std::string inputFile = "libros.txt";
                    createPDF(inputFile);


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
            system("start cmd /K \"C:\\ESPE\\1992-ESTRUCTURA DE DATOS\\ESTRUCTURA-DE-DATOS-CD\\ProyectoPrimerParcial\\Ayuda\\output\\ayuda.exe");
        }
    }
}
