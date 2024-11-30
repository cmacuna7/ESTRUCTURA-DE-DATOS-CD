#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Nodo.h"

using namespace std;

// Clase para la lista circular doblemente enlazada
class ListaCircularDoble {
private:
    Nodo* cabeza = nullptr;

public:
    // Agregar libro
    void agregarLibro(const Libro& libro);

    // Imprimir todos los libros
    void imprimirLibros();

    // Buscar libro
    Nodo* buscarLibro(const string& titulo);

    // Eliminar libro
    void eliminarLibro(const string& titulo);

    // Crear backup
    void crearBackup(const string& nombreArchivo);

    // Restaurar backup
    void restaurarBackup(const string& nombreArchivo);
};

#endif