/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista doble                          *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              25/11/2024                                          *
 * Fecha de modificacion:          25/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 ***************************************************************************************/

#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
#include "ListaDoble.cpp"

using namespace std;

// Función principal
int main() {

    //Crear instancias de la clase Validaciones para enteros y strings
    Validaciones<int> ingresar_entero;
    Validaciones<string> ingresar_string;

    ListaDoble<string>* lista_datos = new ListaDoble<string>();
    ListaDoble<string>* lista_auxiliar = nullptr; // Lista auxiliar inicializada como vacía


    char opcion;
    std::string dato_nombre, dato_apellido;

    do {
        system("cls");
        cout << "*********** Menu ***********" << endl;
        cout << "1. Insertar datos" << endl;
        cout << "2. Buscar palabras por caracter" << endl;
        cout << "3. Borrar un caracter de las palabras" << endl;
        cout << "4. Reemplazar un caracter por otro en las palabras" << endl;
        cout << "5. Mostrar lista" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case '1': {
            string cedula;
            do {
                cout << "Ingrese la cedula:";
                cin >> cedula;
                if (!ingresar_string.validarCedula(cedula)) {
                    cout << "Cedula invalida. Intente nuevamente." << endl;
                }
            } while (!ingresar_string.validarCedula(cedula));
            lista_datos->insertar(cedula);

            // Insertar nombre
            do{
                dato_nombre = ingresar_string.ingresar("Ingrese el nombre:", "string");
            }while (dato_nombre.empty());
            lista_datos->insertar(dato_nombre);

            // Ingresar apellido
            do{
                dato_apellido = ingresar_string.ingresar("\nIngrese el apellido:", "string");
            }while (dato_apellido.empty());
            lista_datos->insertar(dato_apellido);

            cout << "\nDatos ingresados correctamente." << endl;
            system("pause");
            break;
        }
        case '2': {
            char caracter;
            cout << "Ingrese el caracter a buscar: ";
            cin >> caracter;
            lista_datos->buscarPorCaracter(caracter);
            system("pause");
            break;
        }
        case '3': {
            char caracter;
            cout << "Ingrese el caracter a borrar: ";
            cin >> caracter;

            // Elimina cualquier lista auxiliar existente
            if (lista_auxiliar != nullptr) {
                delete lista_auxiliar;
                lista_auxiliar = nullptr;
            }

            // Crear una nueva lista auxiliar con los cambios
            lista_auxiliar = new ListaDoble<string>(lista_datos->eliminarCaracterEnAuxiliar(caracter));

            cout << "\nContenido de la lista original:" << endl;
            lista_datos->mostrar();

            cout << "\nContenido de la lista auxiliar (después de borrar el carácter):" << endl;
            lista_auxiliar->mostrar();

            system("pause");
            break;
        }
        case '4': {
            char viejo, nuevo;
            cout << "Ingrese el caracter a reemplazar: ";
            cin >> viejo;
            cout << "Ingrese el nuevo caracter: ";
            cin >> nuevo;

            // Elimina cualquier lista auxiliar existente
            if (lista_auxiliar != nullptr) {
                delete lista_auxiliar;
                lista_auxiliar = nullptr;
            }

            // Crear una nueva lista auxiliar con los cambios
            lista_auxiliar = new ListaDoble<string>(lista_datos->reemplazarCaracterEnAuxiliar(viejo, nuevo));

            cout << "\nContenido de la lista original:" << endl;
            lista_datos->mostrar();

            cout << "\nContenido de la lista auxiliar (después de reemplazar el carácter):" << endl;
            lista_auxiliar->mostrar();

            system("pause");
            break;
        }
        case '5': {
            cout << "\nContenido de la lista original:" << endl;
            lista_datos->mostrar();

            if (lista_auxiliar != nullptr) {
                cout << "\nContenido de la lista auxiliar:" << endl;
                lista_auxiliar->mostrar();
            } else {
                cout << "\nLa lista auxiliar esta vacia o no ha sido creada." << endl;
            }

            system("pause");
            break;
        }
        case '6':
            cout << "Saliendo del sistema." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            system("pause");
            break;
        }
    } while (opcion != '6');

    delete lista_datos;
    if (lista_auxiliar != nullptr) {
        delete lista_auxiliar;
        lista_auxiliar = nullptr;
    }   
    return 0;
}
