/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              21/11/2024                                          *
 * Fecha de modificacion:          21/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#include "Lista_Simple.h"

using namespace std;


template <typename T>
Lista_Simple<T>::Lista_Simple()
{
    cabeza = NULL;
}

template <typename T>
void Lista_Simple<T>::Insertar_cabeza(T _dato)
{
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

template<typename T> 
void Lista_Simple<T>::Insertar_cola(T _dato) 
{
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

template<typename T> 
void Lista_Simple<T>::Buscar(T _dato) {
    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            cout << "El dato " << _dato << " si se encuentra en la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T> 
void Lista_Simple<T>::Eliminar(T _dato) {
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            if (anterior == NULL) {
                cabeza = aux->getSiguiente();
            }
            else {
                anterior->setSiguiente(aux->getSiguiente());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
            return;
        }
        anterior = aux;
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T> 
void Lista_Simple<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        cout << aux->getDato() << " -> ";
        aux = aux->getSiguiente();
    }
    cout << "NULL" << endl;
}

template<typename T>
void Lista_Simple<T>::BuscarPorCaracter(char caracter) {
    Nodo<T>* aux = cabeza;
    bool encontrado = false;

    while (aux != nullptr) {
        string palabra = aux->getDato(); // Asumimos que `T` puede convertirse a string
        for (char c : palabra) {
            if (tolower(c) == tolower(caracter)) {
                cout << "\nPalabra encontrada: " << palabra << endl;
                encontrado = true;
                break;
            }
        }
        aux = aux->getSiguiente();
    }

    if (!encontrado) {
        cout << "\nNo se encontraron palabras con el caracter '" << caracter << "'.\n";
    }
}

template<typename T>
Lista_Simple<string> Lista_Simple<T>::EliminarCaracter(char caracter) {
    Lista_Simple<string> nuevaLista;
    Nodo<T>* aux = cabeza;

    while (aux != nullptr) {
        string palabra = aux->getDato();
        string palabraModificada = "";

        // Eliminar el carácter de la palabra
        for (char c : palabra) {
            if (tolower(c) != tolower(caracter)) {
                palabraModificada += c;
            }
        }

        // Insertar palabra modificada en la nueva lista
        nuevaLista.Insertar_cabeza(palabraModificada);
        aux = aux->getSiguiente();
    }

    return nuevaLista;
}