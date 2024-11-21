#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Nodo {
    string dato;
    Nodo* siguiente;

    Nodo(string valor) : dato(valor), siguiente(nullptr) {}
};

class ListaEnlazada {
private:
    struct Nodo {
        string dato;
        Nodo* siguiente;
        Nodo(string d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* head;

public:
    ListaEnlazada() : head(nullptr) {}

    // Insertar un nuevo dato en la lista
    void insertar(const string& dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        if (head == nullptr) {
            head = nuevoNodo;
        } else {
            Nodo* temp = head;
            while (temp->siguiente != nullptr) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
        }
    }

    // Función para borrar un carácter de todas las palabras en la lista
    ListaEnlazada borrarCaracter(char caracter) const {
        ListaEnlazada nuevaLista;
        Nodo* actual = head;

        while (actual != nullptr) {
            string palabra = actual->dato;
            string palabraModificada = "";

            // Eliminar el carácter de la palabra
            for (char c : palabra) {
                if (tolower(c) != tolower(caracter)) {
                    palabraModificada += c;
                }
            }

            // Insertar la palabra modificada en la nueva lista
            nuevaLista.insertar(palabraModificada);
            actual = actual->siguiente;
        }

        return nuevaLista;
    }

    void buscarPorCaracter(char caracter) const {
        Nodo* actual = head;
        bool encontrado = false;

        while (actual != nullptr) {
            string palabra = actual->dato;
            for (char c : palabra) {
                if (tolower(c) == tolower(caracter)) {
                    cout << "Palabra encontrada: " << palabra << endl;
                    encontrado = true;
                    break;
                }
            }
            actual = actual->siguiente;
        }

        if (!encontrado) {
            cout << "No se encontraron palabras con el caracter '" << caracter << "'.\n";
        }
    }

    void mostrar() const {
        Nodo* actual = head;
        while (actual != nullptr) {
            cout << actual->dato << " -> ";
            actual = actual->siguiente;
        }
        cout << "NULL\n";
    }
};


#endif