#include "Menu.h"
#include "BackupManager.cpp"
#include "Ayuda.cpp"
#include <iostream>
#include "Validaciones.cpp" // Incluir el header de Validaciones
#include <conio.h> // Para captura de teclas
#include <vector>
#include <sstream>
#include <ctime>

using namespace std;

string generarCorreo(string nombre, string sNombre, string apellido) {
    // Crear el correo concatenando el primer caracter de nombre + primer caracter de segundo nombre + apellido
    for (int i = 0; i < nombre.length(); i++) {
        nombre[i] = tolower(nombre[i]);
    }
    for (int i = 0; i < sNombre.length(); i++) {
        sNombre[i] = tolower(sNombre[i]);
    }
    for (int i = 0; i < apellido.length(); i++) {
        apellido[i] = tolower(apellido[i]);
    }
    string correo = string(1, nombre[0]) + string(1, sNombre[0]) + apellido + "@espe.edu.ec";
    return correo;
}

void mostrarMenu(ListaDoble& lista) {
    vector<string> opciones = {
        "Agregar persona",
        "Buscar persona",
        "Eliminar persona",
        "Ver todas las personas",
        "Crear backup",
        "Restaurar backup",
        "Ordenar por cédula",
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
            if (opciones[seleccion] == "Agregar persona") {
                string nombre, cedula, fechaNac, sNombre, apellido, correo;

                // Solicitar nombre de la persona
                do {
                    cout << "Ingrese Primer Nombre de la persona: ";
                    getline(cin, nombre);
                } while (!Validaciones::validarTituloNombre(nombre, "Nombre"));

                do {
                    cout << "Ingrese Segundo Nombre de la persona: ";
                    getline(cin, sNombre);
                } while (!Validaciones::validarTituloNombre(sNombre, "Segundo Nombre"));

                do {
                    cout << "Ingrese apellido de la persona: ";
                    getline(cin, apellido);
                } while (!Validaciones::validarTituloNombre(apellido, "Apellido"));

                    correo = generarCorreo(nombre, sNombre, apellido);

                    // Mostrar el correo generado
                    cout << "El correo generado es: " << correo << endl;


                // Solicitar cédula
                do {
                    cout << "Ingrese cédula: ";
                    getline(cin, cedula);
                } while (!Validaciones::validarCedula(cedula));

                // Solicitar fecha de nacimiento
                do {
                    cout << "Ingrese fecha de nacimiento (DD-MM-YYYY): ";
                    getline(cin, fechaNac);
                } while (!Validaciones::validarFecha(fechaNac));

                // Crear la persona
                Fecha fechaNacimiento = Fecha::crearDesdeCadena(fechaNac);
                Persona persona(nombre, cedula, fechaNacimiento);

                // Agregar persona a la lista
                lista.agregarPersona(persona);
            } else if (opciones[seleccion] == "Buscar persona") {
                string cedula;
                cout << "Ingrese la cédula de la persona a buscar: ";
                cin >> ws; getline(cin, cedula);
                Nodo* persona = lista.buscarPersonaPorCedula(cedula);
                if (persona) {
                    persona->persona.mostrar();
                } else {
                    cout << "Persona no encontrada.\n";
                }
            } else if (opciones[seleccion] == "Eliminar persona") {
                string cedula;
                cout << "Ingrese la cédula de la persona a eliminar: ";
                cin >> ws; getline(cin, cedula);
                // Eliminar usando cédula
                Nodo* personaAEliminar = lista.buscarPersonaPorCedula(cedula);
                if (personaAEliminar) {
                    lista.eliminarPersonaPorCedula(cedula);
                } else {
                    cout << "Persona no encontrada con cédula: " << cedula << endl;
                }
            } else if (opciones[seleccion] == "Ver todas las personas") {
                lista.imprimirPersonas();
            } else if (opciones[seleccion] == "Crear backup") {
                time_t ahora = time(0);
                tm* tiempo = localtime(&ahora);
                stringstream ss;
                ss << (1900 + tiempo->tm_year) << "_" << (1 + tiempo->tm_mon) << "_" << tiempo->tm_mday << "_"
                << tiempo->tm_hour << "_" << tiempo->tm_min << "_" << tiempo->tm_sec << ".txt";
                lista.crearBackup(ss.str());
            } else if (opciones[seleccion] == "Restaurar backup") {
                BackupManager::restaurarBackup(lista);  // Llama a la función para restaurar el backup
            } else if (opciones[seleccion] == "Ordenar por cédula") {
                lista.ordenarPorCedula();
                cout << "Lista ordenada por cédula.\n";
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