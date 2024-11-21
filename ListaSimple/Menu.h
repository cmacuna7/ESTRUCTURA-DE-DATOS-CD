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
            cin >> opcion;

            switch (opcion) {
                case '1': {
                    string nombre, apellido, cedula;
                    cout << "Ingrese el nombre: ";
                    cin >> nombre;
                    cout << "Ingrese el apellido: ";
                    cin >> apellido;
                    do {
                        cout << "Ingrese la cedula: ";
                        cin >> cedula;
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
                    cout << "Ingrese el caracter a buscar: ";
                    cin >> caracter;
                    lista.buscarPorCaracter(caracter);
                    pausa(); 
                    break;
                }

                case '3': {
                    cout << "Ingrese el caracter a borrar: ";
                    cin >> caracter;
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
                    cout << "Opcion invalida. Intente de nuevo.\n";
                    pausa(); 
                    break;
            }
        } while (opcion != '5');
    }
};

#endif
