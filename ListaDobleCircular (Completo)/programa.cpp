/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista doble circular                 *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              25/11/2024                                          *
 * Fecha de modificacion:          25/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 ***************************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
#include "ListaDobleCircular.cpp"

using namespace std;

// Función principal
bool esEntero(string);

int main() {

    // Crear instancias de la clase Validaciones para enteros y strings
    Validaciones<int> ingresar_entero;
    Validaciones<string> ingresar_string;

    // Cambiar ListaDoble por ListaCircular
    ListaCircular<string>* lista_datos = new ListaCircular<string>();
    ListaCircular<string>* lista_auxiliar = nullptr; // Lista auxiliar inicializada como vacía

    char opcion, caracter, viejo, nuevo;
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

                    do {
                    cout << "\nIngrese un unico caracter a buscar: ";
                    caracter = ingresar_string.ingresar("", "char")[0];
                    } while (caracter == '\0');  

            lista_datos->buscarPorCaracter(caracter);
            system("pause");
            break;
        }
        case '3': {

            do {
                cout << "\nIngrese el caracter a borrar: ";
                caracter = ingresar_string.ingresar("", "char")[0];
            } while (caracter == '\0');  


        if (lista_auxiliar == nullptr) {
            // Primera vez: se opera sobre lista_datos
            lista_auxiliar = new ListaCircular<string>(lista_datos->eliminarCaracterEnAuxiliar(caracter));
            cout << "\nContenido de la lista original (después de borrar el carácter):" << endl;
            lista_datos->mostrar();
        } else {
            // Siguientes veces: se opera sobre lista_auxiliar
            ListaCircular<string>* nuevaLista = new ListaCircular<string>(lista_auxiliar->eliminarCaracterEnAuxiliar(caracter));
            delete lista_auxiliar; // Elimina la lista auxiliar previa
            lista_auxiliar = nuevaLista;
        }

        // Mostrar contenido de lista_auxiliar después de la operación
        cout << "\nContenido de la lista auxiliar (despues de borrar el caracter):" << endl;
        lista_auxiliar->mostrar();

        system("pause");
        break;
    }

        case '4': {

            do {
                cout << "\nIngrese el caracter a reemplazar: ";
                viejo = ingresar_string.ingresar("", "char")[0];
            } while (viejo == '\0');  

            do {
                cout << "\nIngrese el nuevo caracter: ";
                nuevo = ingresar_string.ingresar("", "char")[0];
            } while (nuevo == '\0');  


            // Si ya existe una lista auxiliar, realizamos el reemplazo en ella.
            if (lista_auxiliar != nullptr) {
                // Reemplazar el carácter en la lista auxiliar
                lista_auxiliar->reemplazarCaracter(viejo, nuevo);

                cout << "\nContenido de la lista auxiliar (despues de reemplazar el caracter):" << endl;
                lista_auxiliar->mostrar();
            } else {
                cout << "No hay lista auxiliar para realizar el reemplazo." << endl;
            }

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
