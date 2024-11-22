/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              21/11/2024                                          *
 * Fecha de modificacion:          21/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#include "Lista_Simple.cpp"
#include "Nodo.cpp"
#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
//#include <windows.h>
using namespace std;



bool esEntero(string);

int main() {
    // Crear instancias de la clase Validaciones para enteros y strings
    Validaciones<int> ingresar_entero;
    Validaciones<string> ingresar_string;

    Lista_Simple<string>* lista_datos = new Lista_Simple<string>();

    char opcion;
    char caracter;
    bool cedulaValida = false;
    std::string dato_nombre, dato_apellido;
    do {
        system("cls");
        cout << "*********** Menu ***********" << endl;
        cout << "1. Insertar datos" << endl;
        cout << "2. Buscar palabras por caracter" << endl;
        cout << "3. Borrar un caracter de las palabras" << endl;
        cout << "4. Mostrar lista" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case '1': {
            // Insertar cedula
            string cedula;
            // Pedir y validar cédula
            do {
                cout << "Ingrese la cedula (10 digitos): ";
                cin >> cedula;
                // Llamar al método de validación para la cédula
                cedulaValida = ingresar_string.validarCedula(cedula);
                if (!cedulaValida) {
                    cout << "Cedula invalida" << endl;
                }
            } while (!cedulaValida);

            lista_datos->Insertar_cabeza(cedula);
            //lista_datos->Insertar_cola(cedula);

            // Insertar nombre
            do{
            dato_nombre = ingresar_string.ingresar("\nIngrese el nombre: ", "string");
             }while (dato_nombre.empty());
            lista_datos->Insertar_cabeza(dato_nombre);
            //lista_datos->Insertar_cola(dato_nombre);
                        
            do{
            // Insertar apellido
            dato_apellido = ingresar_string.ingresar("\nIngrese el apellido: ", "string");
            }while (dato_apellido.empty());

            lista_datos->Insertar_cabeza(dato_apellido);
            //lista_datos->Insertar_cola(dato_apellido);

            cout << "\nDatos ingresados correctamente." << endl;
            system("pause");
            break;
        }
        case '2': {
            caracter = ingresar_string.ingresar("Ingrese el caracter a buscar: ", "char")[0];
            lista_datos->BuscarPorCaracter(caracter);
            system("pause");
            break;
        }
        case '3': {
            caracter = ingresar_string.ingresar("Ingrese el caracter a borrar: ", "char")[0];
            Lista_Simple<string> nuevaLista = lista_datos->EliminarCaracter(caracter);
            
            cout << "\nContenido de la nueva lista (despues de borrar '" << caracter << "'):\n";
            nuevaLista.Mostrar();
            system("pause");
            break;
        }
        case '4': {
            cout << "Contenido de la lista:\n";
            lista_datos->Mostrar();
            system("pause");
            break;
        }
        case '5':
            cout << "Saliendo del sistema." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            system("pause");
            break;
        }
    } while (opcion != '5');

    delete lista_datos;
    return 0;
}
