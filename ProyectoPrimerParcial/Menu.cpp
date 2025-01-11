/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include "Menu.h"
#include "BackupManager.cpp"
#include <iostream>
#include "Validaciones.cpp" 
#include <conio.h> 
#include <vector>
#include <sstream>
#include <ctime>
#include "pdf_generator.h"
#include <windows.h>
#include "funciones.h"

using namespace std;

std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH); 
    std::wstring path(buffer);
    return path.substr(0, path.find_last_of(L"\\/"));
}
int ingresarAnio(const string& mensaje) {
    int anio;
    string input;
    while (true) {
        cout << mensaje;
        getline(cin, input);  // Usamos getline para permitir validación de la entrada completa

        // Validar si la entrada está vacía o contiene solo espacios
        if (input.empty() || input.find_first_not_of(' ') == string::npos) {
            cout << "Error: Debe ingresar un dato (no puede estar vacío o contener solo espacios)." << endl;
            continue;
        }

        // Validar que el año sea numérico y tenga 4 dígitos
        try {
            anio = stoi(input);  // Convertimos la entrada a entero
            if (anio < 1 || anio > 2024) {
                throw invalid_argument("Año fuera de rango.");
            }
            break;  // Salimos del bucle si el año es válido
        } catch (const invalid_argument& e) {
            cout << "Error: Ingrese un año válido de 4 dígitos entre 0001 y 2024." << endl;
        }
    }
    return anio;
}
void mostrarMenu(ListaCircularDoble& lista) {
    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Agregar libro");
    menuOpciones.insertar("Buscar libro");
    menuOpciones.insertar("Eliminar libro");
    menuOpciones.insertar("Ver todos los libros");
    menuOpciones.insertar("Exportar en archivo PDF");
    menuOpciones.insertar("Crear backup");
    menuOpciones.insertar("Restaurar backup");
    menuOpciones.insertar("Buscar por rango");
    menuOpciones.insertar("Salir");

    int seleccion = 0;
    string ruta = "libros.txt";
    int anioInicio, anioFin;

    while (true) {
        system("cls");
        cout << "=== Menu Principal ===\n";
        NodoMenu* actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++) {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<\n";
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        } else if (tecla == 80) { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        } else if (tecla == '\r') { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Agregar libro") {
                string titulo, isbn, isni;
                string fechaPub, fechaNac;
                Persona autor;

                do {
                    cout << "Ingrese título del libro: ";
                    getline(cin, titulo);
                } while (!Validaciones::validarTitulo(titulo, "Título"));

                do {
                    cout << "Ingrese ISBN: ";
                    getline(cin, isbn);
                } while (!Validaciones::validarIsbn(isbn));

                Nodo* libroExistente = lista.buscarLibroPorIsbn(isbn);
                if (libroExistente) {
                    cout << "El ISBN ya existe. Información del libro existente:\n";
                    libroExistente->libro.mostrar();
                } else {
                    do {
                        cout << "Ingrese ISNI del autor: ";
                        getline(cin, isni);
                    } while (!Validaciones::validarIsni(isni));

                    Persona autorExistente = lista.buscarAutorPorIsni(isni);
                    if (autorExistente.getNombre() != "") {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = autorExistente;
                        // Guardamos la fecha de nacimiento del autor existente
                        fechaNac = autorExistente.getFechaNacimiento().toString();
                    } else {
                        string nombreAutor;
                        do {
                            cout << "Ingrese nombre del autor: ";
                            getline(cin, nombreAutor);
                        } while (!Validaciones::validarTituloNombre(nombreAutor, "Nombre del Autor"));

                        do {
                            cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY): ";
                            getline(cin, fechaNac);
                        } while (!Validaciones::validarFecha(fechaNac));

                        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                        autor = Persona(nombreAutor, isni, fechaNacimientoAutor);
                    }

                    do {
                        cout << "Ingrese fecha de publicación del libro (DD-MM-YYYY): ";
                        getline(cin, fechaPub);
                    } while (!Validaciones::validarFechaPublicacion(fechaPub, fechaNac));

                    Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                    Libro libro(titulo, isbn, autor, fechaPublicacion);
                    lista.agregarLibro(libro);
                }
            } else if (opcionSeleccionada == "Buscar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a buscar: ";
                cin >> ws; getline(cin, isbn);
                Nodo* libro = lista.buscarLibroPorIsbn(isbn);
                if (libro) {
                    libro->libro.mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            } else if (opcionSeleccionada == "Eliminar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a eliminar: ";
                cin >> ws; getline(cin, isbn);
                Nodo* libroAEliminar = lista.buscarLibroPorIsbn(isbn);
                if (libroAEliminar) {
                    string titulo = libroAEliminar->libro.getTitulo();
                    lista.eliminarLibro(titulo);
                } else {
                    cout << "Libro no encontrado con ISBN: " << isbn << endl;
                }
            } else if (opcionSeleccionada == "Ver todos los libros") {
                lista.imprimirLibros();
            } else if (opcionSeleccionada == "Exportar en archivo PDF") {
                const std::string inputFile = "libros.txt";
                createPDF(inputFile);
            } else if (opcionSeleccionada == "Crear backup") {
                time_t ahora = time(0);
                tm* tiempo = localtime(&ahora);
                stringstream ss;
                ss << (1900 + tiempo->tm_year) << "_" << (1 + tiempo->tm_mon) << "_" << tiempo->tm_mday << "_"
                << tiempo->tm_hour << "_" << tiempo->tm_min << "_" << tiempo->tm_sec << ".txt";
                lista.crearBackup(ss.str());
            } else if (opcionSeleccionada == "Restaurar backup") {
                BackupManager::restaurarBackup(lista);
            } else if (opcionSeleccionada == "Buscar por rango") {
                while (true) {
                    anioFin = ingresarAnio("Ingrese el año de fin (0001 a 2024): ");
                    anioInicio = ingresarAnio("Ingrese el año de inicio (0001 a 2024): ");

                    if (anioFin > anioInicio) {
                        break;
                    } else {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }
                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                buscarPorRango(ruta, anioInicio, anioFin);
            } else if (opcionSeleccionada == "Salir") {
                break;
            }
            cout << "Presione cualquier tecla para continuar...\n";
            _getch();
        } else if (tecla == 59) { // F1
            std::wstring base_path = getExecutablePath();
            std::wstring ayuda_path = base_path + L"\\output\\ayuda.exe";
            std::string command = "start cmd /C \"" + std::string(ayuda_path.begin(), ayuda_path.end()) + "\"";
            system(command.c_str());
        }
    }
}