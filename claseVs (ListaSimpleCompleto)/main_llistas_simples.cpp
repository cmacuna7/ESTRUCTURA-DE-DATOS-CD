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
    //Crear instancias de la clase Validaciones para enteros y strings
    Validaciones<int> ingresar_entero;
    Validaciones<string> ingresar_string;

    Lista_Simple<string>* lista_datos = new Lista_Simple<string>();
    Lista_Simple<string> lista_auxiliar; // Lista auxiliar global para modificaciones

    char opcion;
    char caracter;
    bool cedulaValida = false;
    std::string dato_nombre, dato_apellido;
    bool primera_edicion = true;

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
                cout << "Ingrese la cedula: ";
                cin >> cedula;
                if (!ingresar_string.validarCedula(cedula)) {
                    cout << "Cedula invalida. Intente nuevamente." << endl;
                }
            } while (!ingresar_string.validarCedula(cedula));
            lista_datos->Insertar_cabeza(cedula);

            string nombre = ingresar_string.ingresar("Ingrese el nombre: ", "string");
            lista_datos->Insertar_cabeza(nombre);

            string apellido = ingresar_string.ingresar("Ingrese el apellido: ", "string");
            lista_datos->Insertar_cabeza(apellido);

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
            cout << "Ingrese el caracter a borrar: ";
            char borrar = ingresar_string.ingresar("", "char")[0];

            if (primera_edicion) {
                lista_auxiliar = lista_datos->ModificarCaracter(borrar);
                primera_edicion = false; // Cambiar a false después de la primera edición
            } else {
                lista_auxiliar = lista_auxiliar.ModificarCaracter(borrar);
            }

            cout << "\nContenido de la lista original:\n";
            lista_datos->Mostrar();

            cout << "Contenido de la lista auxiliar (despues de borrar '" << borrar << "'):\n";
            lista_auxiliar.Mostrar();

            system("pause");
            break;
        }
        case '4': {
            cout << "Ingrese el caracter a borrar: ";
            char borrar = ingresar_string.ingresar("", "char")[0];

            cout << "\nIngrese el caracter por el que se reemplazara: ";
            char reemplazar = ingresar_string.ingresar("", "char")[0];

            if (primera_edicion) {
                lista_auxiliar = lista_datos->ModificarCaracter(borrar, reemplazar);
                primera_edicion = false; // Cambiar a false después de la primera edición
            } else {
                lista_auxiliar = lista_auxiliar.ModificarCaracter(borrar, reemplazar);
            }

            cout << "Contenido de la lista original:\n";
            lista_datos->Mostrar();

            cout << "Contenido de la lista auxiliar (modificada):\n";
            lista_auxiliar.Mostrar();

            system("pause");
            break;
        }
        
        case '5': { // Mostrar lista original y auxiliar
            cout << "Contenido de la lista original:\n";
            lista_datos->Mostrar();

            cout << "\nContenido de la lista auxiliar:\n";
            lista_auxiliar.Mostrar();

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
    return 0;
}
