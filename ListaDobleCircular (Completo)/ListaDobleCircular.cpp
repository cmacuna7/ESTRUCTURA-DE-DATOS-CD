/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista doble circular                 *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              25/11/2024                                          *
 * Fecha de modificacion:          25/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 ***************************************************************************************/
#include "ListaDobleCircular.h"
#include <algorithm> // Para std::replace
#include <iterator>  // Para iteradores (opcional)

// Destructor
template <typename T>
ListaCircular<T>::~ListaCircular() {
        if (!cabeza) return;
        Nodo<T>* actual = cabeza;
        do {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
}

// Insertar al final
template <typename T>
void ListaCircular<T>::insertar(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (!cabeza) {
        cabeza = nuevo;
    } else {
        Nodo<T>* cola = cabeza->getAnterior();
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
    }
}

// Mostrar lista circular
template <typename T>
void ListaCircular<T>::mostrar() {
    if (!cabeza) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* actual = cabeza;
    do {
        cout << "[" << actual->getDato() << "] <-> ";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    cout << "(retorno a la cabeza)" << endl;
}

// Buscar palabras que contengan un caracter
template <typename T>
void ListaCircular<T>::buscarPorCaracter(char caracter) {
    Nodo<T>* actual = cabeza;
    bool encontrado = false;
    cout << "Palabras que contienen el caracter '" << caracter << "':" << endl;
    do {
        if (actual->getDato().find(caracter) != string::npos) {
            cout << actual->getDato() << " ";
            encontrado = true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    if (!encontrado) {
        cout << "Ninguna palabra contiene el caracter especificado." << endl;
    }
}

// Borrar un caracter en todas las palabras
template <typename T>
void ListaCircular<T>::borrarCaracter(char caracter) {
    Nodo<T>* actual = cabeza;
    do {
        string dato = actual->getDato();
        dato.erase(remove(dato.begin(), dato.end(), caracter), dato.end());
        actual->setDato(dato);
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    cout << "\nCaracter '" << caracter << "' eliminado de todas las palabras." << endl;
}

// Reemplazar un caracter por otro
template <typename T>
void ListaCircular<T>::reemplazarCaracter(char viejo, char nuevo) {
    Nodo<T>* actual = cabeza;
    do {
        string dato = actual->getDato();
        replace(dato.begin(), dato.end(), viejo, nuevo);
        actual->setDato(dato);
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    cout << "Caracter '" << viejo << "' reemplazado por '" << nuevo << "' en todas las palabras." << endl;
}

// Método auxiliar para eliminar un caracter
template <typename T>
ListaCircular<T> ListaCircular<T>::eliminarCaracterEnAuxiliar(char caracter) {
    ListaCircular<T> nuevaLista; // Lista auxiliar
    Nodo<T>* actual = cabeza;

    do {
        std::string datoModificado = actual->getDato();

        // Eliminar caracteres ignorando mayúsculas/minúsculas
        datoModificado.erase(
            std::remove_if(
                datoModificado.begin(),
                datoModificado.end(),
                [caracter](char c) { return std::tolower(c) == std::tolower(caracter); } // Compara sin distinguir entre mayúsculas y minúsculas
            ),
            datoModificado.end()
        );

        nuevaLista.insertar(datoModificado);
        actual = actual->getSiguiente();
    } while (actual != cabeza); // Asegúrate de recorrer toda la lista circular

    return nuevaLista;
}


// Método auxiliar para reemplazar un caracter
template <typename T>
ListaCircular<T> ListaCircular<T>::reemplazarCaracterEnAuxiliar(char viejo, char nuevo) {
    ListaCircular<T> nuevaLista; // Lista auxiliar
    Nodo<T>* actual = cabeza;

    do {
        std::string datoModificado = actual->getDato();

        // Reemplazar ignorando mayúsculas/minúsculas
        std::transform(
            datoModificado.begin(),
            datoModificado.end(),
            datoModificado.begin(),
            [viejo, nuevo](char c) {
                // Compara el carácter sin distinguir entre mayúsculas y minúsculas
                return std::tolower(c) == std::tolower(viejo) ? nuevo : c;
            }
        );

        nuevaLista.insertar(datoModificado);
        actual = actual->getSiguiente();
    } while (actual != cabeza); // Asegúrate de recorrer toda la lista circular

    return nuevaLista;
}

