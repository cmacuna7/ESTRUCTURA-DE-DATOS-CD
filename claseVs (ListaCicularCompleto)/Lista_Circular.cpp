/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              21/11/2024                                          *
 * Fecha de modificacion:          21/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/
#include "Lista_Circular.h"
#include <iostream>

using namespace std;

template <typename T>
Lista_Circular<T>::Lista_Circular() {
    cabeza = NULL;
}

template<typename T>
void Lista_Circular<T>::Insertar_cabeza(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
        nuevo->setSiguiente(cabeza);  // Enlazamos el nodo a sí mismo (circular)
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != cabeza) {  // Buscamos el último nodo
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza);  // Hacemos circular
        cabeza = nuevo;  // La cabeza ahora es el nuevo nodo
    }
}

template<typename T>
void Lista_Circular<T>::Insertar_cola(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
        nuevo->setSiguiente(cabeza);  // Enlazamos el nodo a sí mismo
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != cabeza) {  // Buscamos el último nodo
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza);  // El nuevo nodo apunta a la cabeza
    }
}

template<typename T>
void Lista_Circular<T>::Buscar(T _dato) {
    Nodo<T>* aux = cabeza;
    if (aux != NULL) {
        do {
            if (aux->getDato() == _dato) {
                cout << "El dato " << _dato << " se encuentra en la lista." << endl;
                return;
            }
            aux = aux->getSiguiente();
        } while (aux != cabeza);
    }
    cout << "El dato " << _dato << " no se encuentra en la lista." << endl;
}

template<typename T>
void Lista_Circular<T>::Eliminar(T _dato) {
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    if (aux != NULL) {
        do {
            if (aux->getDato() == _dato) {
                if (anterior == NULL) {  // El nodo a eliminar es la cabeza
                    Nodo<T>* temp = cabeza;
                    if (cabeza->getSiguiente() == cabeza) {
                        cabeza = NULL;  // Caso lista con un solo nodo
                    } else {
                        while (aux->getSiguiente() != cabeza) {
                            aux = aux->getSiguiente();
                        }
                        cabeza = cabeza->getSiguiente();  // Actualizamos la cabeza
                    }
                    delete temp;
                } else {
                    anterior->setSiguiente(aux->getSiguiente());
                    delete aux;
                }
                cout << "El dato " << _dato << " se ha eliminado de la lista." << endl;
                return;
            }
            anterior = aux;
            aux = aux->getSiguiente();
        } while (aux != cabeza);
    }
    cout << "El dato " << _dato << " no se encuentra en la lista." << endl;
}

template<typename T>
void Lista_Circular<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    if (aux != NULL) {
        do {
            cout << aux->getDato() << " -> ";
            aux = aux->getSiguiente();
        } while (aux != cabeza);
        cout << "" << endl;
    } else {
        cout << "La lista está vacía." << endl;
    }
}

template<typename T>
void Lista_Circular<T>::BuscarPorCaracter(char caracter) {
    Nodo<T>* aux = cabeza;
    bool encontrado = false;

    if (aux != NULL) {
        do {
            string palabra = aux->getDato();  // Asumimos que T es un string
            for (char c : palabra) {
                if (tolower(c) == tolower(caracter)) {
                    cout << "\nPalabra encontrada: " << palabra << endl;
                    encontrado = true;
                    break;
                }
            }
            aux = aux->getSiguiente();
        } while (aux != cabeza);
    }

    if (!encontrado) {
        cout << "\nNo se encontraron palabras con el caracter '" << caracter << "'.\n";
    }
}

template<typename T>
Lista_Circular<string> Lista_Circular<T>::EliminarCaracter(char caracter) {
    Lista_Circular<string> nuevaLista;
    Nodo<T>* aux = cabeza;

    if (aux != NULL) {
        do {
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
        } while (aux != cabeza);
    }

    return nuevaLista;
}

template<typename T>
Lista_Circular<string> Lista_Circular<T>::ModificarCaracter(char borrar, char reemplazar) {
    Lista_Circular<string> nuevaLista;
    Nodo<T>* aux = cabeza;

    if (aux != NULL) {
        do {
            string palabra = aux->getDato();
            string palabraModificada = "";

            // Procesar cada carácter en la palabra
            for (char c : palabra) {
                if (tolower(c) == tolower(borrar)) {
                    if (reemplazar != '\0') {
                        palabraModificada += reemplazar;
                    }
                } else {
                    palabraModificada += c;
                }
            }

            // Insertar palabra modificada en la lista auxiliar
            nuevaLista.Insertar_cabeza(palabraModificada);
            aux = aux->getSiguiente();
        } while (aux != cabeza);
    }

    return nuevaLista;
}
