#ifndef MENU_H
#define MENU_H

#include "ListaEnlazada.h"
#include "Validaciones.h"
#include <iostream>
#include <string>

using namespace std;

class Menu {
private:
    ListaEnlazada lista;  // Lista original
    Menu() {}

    void pausa() {
#ifdef _WIN32
        system("pause");
#else
        cout << "Presione Enter para continuar...";
        cin.ignore();
        cin.get(); 
#endif
    }

public:
    static Menu& getInstance() {
        static Menu instancia;
        return instancia;
    }

    void mostrarMenu() {
        char opcion, caracter;
        do {
            cout << "\n=== Menu ===\n";
            cout << "1. Ingresar datos\n";
            cout << "2. Buscar palabras por caracter\n";
            cout << "3. Borrar un caracter de las palabras\n";
            cout << "4. Mostrar lista\n";
            cout << "5. Salir\n";
            cout << "Seleccione una opcion: ";
            opcion = Validaciones::getInstance().leerCaracter("");
            switch (opcion) {
                case '1': {
                    string nombre, apellido, cedula;
                    nombre = Validaciones::getInstance().leerCadenaSinNumero("\nIngrese el nombre: ");

                    apellido = Validaciones::getInstance().leerCadenaSinNumero("\nIngrese el apellido: ");

                    do {
                        cedula = Validaciones::getInstance().leerCadena("Ingrese la cedula: ");
                        if (!Validaciones::getInstance().validarCedula(cedula)) {
                            cout << "Cedula invalida. Intente de nuevo.\n";
                        }
                    } while (!Validaciones::getInstance().validarCedula(cedula));

                    // Insertar datos en la lista original
                    lista.insertar(nombre);
                    lista.insertar(apellido);
                    lista.insertar(cedula);

                    cout << "Datos ingresados correctamente.\n";
                    pausa(); 
                    break;
                }

                case '2': {
                    caracter = Validaciones::getInstance().leerCaracter("\nIngrese el caracter a buscar: ");
                    lista.buscarPorCaracter(caracter);
                    pausa(); 
                    break;
                }

                case '3': {
                    caracter = Validaciones::getInstance().leerCaracter("\nIngrese el caracter a borrar: ");
                    // Crear una nueva lista con las palabras modificadas
                    ListaEnlazada nuevaLista = lista.borrarCaracter(caracter);
                    cout << "Contenido de la nueva lista (despues de borrar '" << caracter << "'):\n";
                    nuevaLista.mostrar();
                    pausa(); 
                    break;
                }

                case '4': {
                    cout << "Contenido de la lista original:\n";
                    lista.mostrar();
                    pausa(); 
                    break;
                }

                case '5':
                    cout << "Saliendo del sistema.\n";
                    break;

                default:
                    cout << "\nOpcion invalida. Intente de nuevo.\n";
                    pausa(); 
                    break;
            }
        } while (opcion != '5');
    }
};

#endif
