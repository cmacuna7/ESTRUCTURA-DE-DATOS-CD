#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include <iostream>
#include "Persona.h"
#include "Fecha.h"
using namespace std;

// Clase para representar un libro
class Libro {
private:
    string titulo;
    string isbn;
    Persona autor;
    Fecha fechaPublicacion;

public:
    // Constructor por defecto y parametrizado
    Libro(string t = "", string i = "", Persona a = Persona(), Fecha fp = Fecha())
        : titulo(t), isbn(i), autor(a), fechaPublicacion(fp) {}

    // Métodos para acceder a los atributos
    string getTitulo() const { return titulo; }
    string getIsbn() const { return isbn; }
    Persona getAutor() const { return autor; }
    Fecha getFechaPublicacion() const { return fechaPublicacion; }

    // Métodos para modificar los atributos
    void setTitulo(const string& t) { titulo = t; }
    void setIsbn(const string& i) { isbn = i; }
    void setAutor(const Persona& a) { autor = a; }
    void setFechaPublicacion(const Fecha& fp) { fechaPublicacion = fp; }

    // Método para mostrar la información del libro
    void mostrar() const {
        cout << "Titulo: " << titulo 
            << ", Autor: " << autor.getNombre() 
            << " (Nacido el: " << autor.getFechaNacimiento().mostrar() << ")"
            << ", ISBN: " << isbn 
            << ", Fecha de publicacion: " << fechaPublicacion.mostrar() << endl;
    }
};

#endif
