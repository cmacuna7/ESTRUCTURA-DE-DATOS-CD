/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista circular                       *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              21/11/2024                                          *
 * Fecha de modificacion:          21/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#include "Lista_Circular.cpp"
#include "Nodo.cpp"
#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
using namespace std;

bool esEntero(string);

int main() {
    //Crear instancias de la clase Validaciones para enteros y strings
    Validaciones<int> ingresar_entero;
    Validaciones<string> ingresar_string;

    Lista_Circular<string>* lista_datos = new Lista_Circular<string>();
    Lista_Circular<string> lista_auxiliar; // Lista auxiliar global para modificaciones

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
                cout << "Ingrese la cedula:";
                cin >> cedula;
                if (!ingresar_string.validarCedula(cedula)) {
                    cout << "Cedula invalida. Intente nuevamente." << endl;
                }
            } while (!ingresar_string.validarCedula(cedula));
            lista_datos->Insertar_cabeza(cedula);

            // Insertar nombre
            do{
            dato_nombre = ingresar_string.ingresar("Ingrese el nombre:", "string");
            }while (dato_nombre.empty());
            lista_datos->Insertar_cabeza(dato_nombre);
                        
            do{
            // Insertar apellido
            dato_apellido = ingresar_string.ingresar("\nIngrese el apellido:", "string");
            }while (dato_apellido.empty());

            lista_datos->Insertar_cabeza(dato_apellido);

            cout << "\nDatos ingresados correctamente." << endl;
            system("pause");
            break;
        }

        case '2': {
            char caracter;
            do {
                cout << "Ingrese un unico caracter a buscar: ";
                cin >> caracter;
                // Validación para asegurar que solo se ingresó un carácter
                if (cin.peek() != '\n') {
                    cout << "Error: Ingrese unicamente un caracter valido." << endl;
                    // Limpia el buffer de entrada en caso de error
                    cin.clear();
                    while (cin.get() != '\n') {
                    // Descartar el resto de la entrada
                    }
                } else {
                    break; // Entrada válida, salir del bucle
                }
            } while (true);
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
