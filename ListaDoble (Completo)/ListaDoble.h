#include "Nodo.h"
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class ListaDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    // Constructor
    ListaDoble() : cabeza(nullptr), cola(nullptr) {}

    // Destructor
    ~ListaDoble();

    // Métodos de la lista
    void insertar(T dato);
    void mostrar();
    void buscarPorCaracter(char caracter);
    void borrarCaracter(char caracter);
    void reemplazarCaracter(char viejo, char nuevo);
};