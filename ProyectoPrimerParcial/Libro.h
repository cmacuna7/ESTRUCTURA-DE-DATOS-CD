#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include <iostream>
using namespace std;

// Clase para representar un libro
class Libro {
private:
    string titulo;
    string autor;
    string isbn;
    int anio;

public:
    // Constructor
    Libro(string t, string a, string i, int an);

    // Métodos para acceder a los atributos
    string getTitulo() const;
    string getAutor() const;
    string getIsbn() const;
    int getAnio() const;

    // Método para mostrar la información del libro
    void mostrar() const;
};

#endif
