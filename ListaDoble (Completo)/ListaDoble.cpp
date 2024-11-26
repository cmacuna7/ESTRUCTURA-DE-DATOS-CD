#include "ListaDoble.h"
#include <algorithm> // Para std::replace
#include <iterator>  // Para iteradores (opcional)

// Destructor
template <typename T>
ListaDoble<T>::~ListaDoble() {
    Nodo<T>* actual = cabeza;
    while (actual) {
        Nodo<T>* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

// Insertar al final
template <typename T>
void ListaDoble<T>::insertar(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
}

// Mostrar lista doble
template <typename T>
void ListaDoble<T>::mostrar() {
    if (!cabeza) {
        cout << "La lista está vacía." << endl;
        return;
    }

    Nodo<T>* actual = cabeza;
    cout << "NULL <-> ";
    while (actual) {
        cout << "[" << actual->getDato() << "]";
        if (actual->getSiguiente()) {
            cout << " <-> ";
        }
        actual = actual->getSiguiente();
    }
    cout << " <-> NULL" << endl;
}

// Buscar palabras que contengan un caracter
template <typename T>
void ListaDoble<T>::buscarPorCaracter(char caracter) {
    Nodo<T>* actual = cabeza;
    bool encontrado = false;
    cout << "Palabras que contienen el caracter '" << caracter << "':" << endl;
    while (actual) {
        if (actual->getDato().find(caracter) != string::npos) {
            cout << actual->getDato() << " ";
            encontrado = true;
        }
        actual = actual->getSiguiente();
    }
    if (!encontrado) {
        cout << "Ninguna palabra contiene el caracter especificado." << endl;
    }
}

// Borrar un caracter en todas las palabras
template <typename T>
void ListaDoble<T>::borrarCaracter(char caracter) {
    Nodo<T>* actual = cabeza;
    while (actual) {
        string dato = actual->getDato();
        dato.erase(remove(dato.begin(), dato.end(), caracter), dato.end());
        actual->setDato(dato);
        actual = actual->getSiguiente();
    }
    cout << "Caracter '" << caracter << "' eliminado de todas las palabras." << endl;
}

// Reemplazar un caracter por otro
template <typename T>
void ListaDoble<T>::reemplazarCaracter(char viejo, char nuevo) {
    Nodo<T>* actual = cabeza;
    while (actual) {
        string dato = actual->getDato();
        // Usamos std::replace con iteradores
        replace(dato.begin(), dato.end(), viejo, nuevo);
        actual->setDato(dato);
        actual = actual->getSiguiente();
    }
    cout << "Caracter '" << viejo << "' reemplazado por '" << nuevo << "' en todas las palabras." << endl;
}