/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Josue Chango, Adonny Calero, Eduardo altamirano     *
 * Fecha de creacion:              18/11/2024                                          *
 * Fecha de modificacion:          18/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
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
    Lista_Simple<std::string>* lista_datos = new Lista_Simple<std::string>();
    Lista_Simple<float>* lista_flotante = new Lista_Simple<float>();
    Lista_Simple<double>* lista_doble = new Lista_Simple<double>();
    Lista_Simple<std::string>* lista_string = new Lista_Simple<std::string>();
    Lista_Simple<char>* lista_letras = new Lista_Simple<char>();

    int opcion, dato_cedula;
    float dato_flotante;
    double dato_doble;
    std::string dato_nombre,  dato_apellido;
    std::string cedula_str, dato_aux;
    char dato_char;

    Validaciones<int> ingresar_entero;
    Validaciones<float> ingresar_flotante;
    Validaciones<double> ingresar_doble;
    Validaciones<std::string> ingresar_string;
    Validaciones<char> ingresar_letra;

    /*HINSTANCE hDLL = LoadLibrary("ValidDll.dll");
    if (!hDLL) {
        std::cerr << "No se pudo cargar la DLL.\n";
        return 1;
    }*/
        do{
                system("cls");
                cout << "*********** Datos Cedula - Nombre - Apellido ***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                do{
                    dato_cedula = ingresar_entero.ingresar("Ingrese la cedula: ", "entero");
                    cout << endl;
                    cedula_str = to_string(dato_cedula);
                }while (cedula_str.length()!=10);

                    lista_datos->Insertar_cabeza(cedula_str);
                    //lista_datos->Insertar_cola(cedula_str);

                do{
                    dato_nombre = ingresar_string.ingresar("Ingrese nombre: ", "string");
                    cout << endl;
                }while(dato_nombre.empty());

                    lista_datos->Insertar_cabeza(dato_nombre);
                    //lista_datos->Insertar_cola(dato_nombre);

                do{    
                    dato_apellido = ingresar_string.ingresar("Ingrese apellido: ", "string");
                    cout << endl;
                }while(dato_apellido.empty());

                    lista_datos->Insertar_cabeza(dato_apellido);
                    //lista_datos->Insertar_cola(dato_apellido);

                    cout << endl << "Datos ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    do{
                    dato_aux = ingresar_string.ingresar("ingrese el dato a buscar: ", "string");
                    cout << endl;
                    }while(dato_aux.empty());

                    lista_datos->Buscar(dato_aux);
                    system("pause");
                    break;
                case 3:
                    do{
                    dato_aux = ingresar_string.ingresar("ingrese el dato a eliminar: ", "string");
                    cout << endl;
                    }while(dato_aux.empty());

                    lista_datos->Eliminar(dato_aux);
                    system("pause");
                    break;
                case 4:
                    lista_datos->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            
    
    return 0;
}
