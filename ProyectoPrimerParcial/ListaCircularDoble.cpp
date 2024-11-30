#include "ListaCircularDoble.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Agregar libro
void ListaCircularDoble::agregarLibro(const Libro& libro) {
    Nodo* nuevo = new Nodo{libro, nullptr, nullptr};
    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        Nodo* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        cabeza->anterior = nuevo;
        ultimo->siguiente = nuevo;
    }
    cout << "Libro agregado: " << libro.getTitulo() << endl;
}

// Imprimir todos los libros
void ListaCircularDoble::imprimirLibros() {
    if (!cabeza) {
        cout << "No hay libros registrados.\n";
        return;
    }
    Nodo* actual = cabeza;
    cout << left << setw(20) << "Titulo" << setw(20) << "Autor" << setw(15) << "ISBN" << setw(6) << "Anio" << endl;
    cout << string(61, '-') << endl;
    do {
        cout << left << setw(20) << actual->libro.getTitulo()
            << setw(20) << actual->libro.getAutor()
            << setw(15) << actual->libro.getIsbn()
            << setw(6) << actual->libro.getAnio() << endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}

// Buscar libro
Nodo* ListaCircularDoble::buscarLibro(const string& titulo) {
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo) return actual;
        actual = actual->siguiente;
    } while (actual != cabeza);
    return nullptr;
}

// Eliminar libro
void ListaCircularDoble::eliminarLibro(const string& titulo) {
    if (!cabeza) return;
    Nodo* actual = cabeza;
    do {
        if (actual->libro.getTitulo() == titulo) {
            if (actual->siguiente == actual) {
                cabeza = nullptr;
            } else {
                Nodo* anterior = actual->anterior;
                Nodo* siguiente = actual->siguiente;
                anterior->siguiente = siguiente;
                siguiente->anterior = anterior;
                if (actual == cabeza) cabeza = siguiente;
            }
            delete actual;
            cout << "Libro eliminado: " << titulo << endl;
            return;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
    cout << "Libro no encontrado: " << titulo << endl;
}

// Backup
void ListaCircularDoble::crearBackup(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo de backup.\n";
        return;
    }
    Nodo* actual = cabeza;
    if (actual) {
        do {
            archivo << actual->libro.getTitulo() << ";" 
                    << actual->libro.getAutor() << ";" 
                    << actual->libro.getIsbn() << ";" 
                    << actual->libro.getAnio() << "\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }
    archivo.close();
    cout << "Backup creado: " << nombreArchivo << endl;
}

// Restaurar backup
void ListaCircularDoble::restaurarBackup(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de backup.\n";
        return;
    }

    // Limpiar la lista actual
    while (cabeza) {
        Nodo* temp = cabeza->siguiente;
        delete cabeza;
        if (temp == cabeza) break;
        cabeza = temp;
    }
    cabeza = nullptr;

    // Leer datos del archivo
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string titulo, autor, isbn;
        int anio;
        getline(ss, titulo, ';');
        getline(ss, autor, ';');
        getline(ss, isbn, ';');
        ss >> anio;
        Libro libro(titulo, autor, isbn, anio);
        agregarLibro(libro);
    }
    archivo.close();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}
