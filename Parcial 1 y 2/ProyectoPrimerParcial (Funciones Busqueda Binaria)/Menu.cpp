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
    vector<string> opciones = {
        "Agregar libro",
        "Buscar libro",
        "Eliminar libro",
        "Ver todos los libros",
        "Exportar en archivo PDF",
        "Crear backup",
        "Restaurar backup",
        "Buscar por rango",
        "Buscar por rango de fecha de nacimiento",
        "Buscar por prefijo de autor",
        "Búsqueda por Rango de ISBN",
        "Buscar por prefijo de ISBN",
        "Buscar por prefijo de ISNI",
        "Buscar por sufijo de autor",

        "Salir"
    };
    int seleccion = 0;
    string ruta = "libros.txt"; // Ruta del archivo
    int anioInicio, anioFin;

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
            } else if (opciones[seleccion] == "Buscar por rango"){
                const std::string inputFile12 = "libros.txt";

                while (true) {
                    anioFin = ingresarAnio("Ingrese el año de fin (0001 a 2024): ");
                    anioInicio = ingresarAnio("Ingrese el año de inicio (0001 a 2024): ");
                

                    // Validar que el año final sea mayor al inicial
                    if (anioFin > anioInicio) {
                        break;
                    } else {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }

                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                buscarPorRango(ruta, anioInicio, anioFin);

            
            } else if (opciones[seleccion] == "Buscar por rango de fecha de nacimiento") {
                const std::string inputFile12 = "libros.txt";
                

                while (true) {
                    anioFin = ingresarAnio("Ingrese el año de fin (0001 a 2024): ");
                    anioInicio = ingresarAnio("Ingrese el año de inicio (0001 a 2024): ");
                

                    // Validar que el año final sea mayor al inicial
                    if (anioFin > anioInicio) {
                        break;
                    } else {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }
                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                buscarPorRangoFechaNacimiento(ruta, anioInicio, anioFin);
            } else if (opciones[seleccion] == "Buscar por prefijo de autor") {
                string prefijo;
                cout << "Ingrese el prefijo del autor: ";
                cin >> ws; getline(cin, prefijo);
                cout << "Registros encontrados con autor que empieza con '" << prefijo << "':\n";
                buscarPorPrefijoAutor(ruta, prefijo);
            } else if (opciones[seleccion] == "Buscar por prefijo de ISBN") {
                string prefijo;
                cout << "Ingrese el prefijo del ISBN: ";
                cin >> ws; getline(cin, prefijo);
                cout << "Registros encontrados con ISBN que empieza con '" << prefijo << "':\n";
                buscarPorPrefijoISBN(ruta, prefijo);
            }else if (opciones[seleccion] == "Buscar por prefijo de ISNI") {
                string prefijo;
                cout << "Ingrese el prefijo del ISNI: ";
                cin >> ws; getline(cin, prefijo);
                cout << "Registros encontrados con ISNI que empieza con '" << prefijo << "':\n";
                buscarPorPrefijoISNI(ruta, prefijo);
            }else if (opciones[seleccion] == "Buscar por sufijo de autor") {
                string sufijo;
                cout << "Ingrese el sufijo del autor: ";
                cin >> ws; getline(cin, sufijo);
                cout << "Registros encontrados con autor que termina con '" << sufijo << "':\n";
                buscarPorSufijoAutor(ruta, sufijo);
            }else if (opciones[seleccion] == "Búsqueda por Rango de ISBN") {
                string isbnInicio, isbnFin;
                cout << "Ingrese el ISBN de inicio: ";
                cin >> ws; getline(cin, isbnInicio);
                cout << "Ingrese el ISBN de fin: ";
                cin >> ws; getline(cin, isbnFin);
                cout << "Registros encontrados con ISBN entre '" << isbnInicio << "' y '" << isbnFin << "':\n";
                buscarPorRangoISBN(ruta, isbnInicio, isbnFin);
            }else if (opciones[seleccion] == "Salir") {
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
