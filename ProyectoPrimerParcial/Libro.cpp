#include "Libro.h"
#include <iostream>

Libro::Libro(string t, string i, Persona a, Fecha fp) 
    : titulo(t), isbn(i), autor(a), fechaPublicacion(fp) {}

string Libro::getTitulo() const { return titulo; }
string Libro::getIsbn() const { return isbn; }
Persona Libro::getAutor() const { return autor; }
Fecha Libro::getFechaPublicacion() const { return fechaPublicacion; }

void Libro::setTitulo(const string& t) { titulo = t; }
void Libro::setIsbn(const string& i) { isbn = i; }
void Libro::setAutor(const Persona& a) { autor = a; }
void Libro::setFechaPublicacion(const Fecha& fp) { fechaPublicacion = fp; }

void Libro::mostrar() const {
    cout << "Titulo: " << titulo 
        << ", Autor: " << autor.getNombre() 
        << " (Nacido el: " << autor.getFechaNacimiento().mostrar() << ")"
        << ", ISBN: " << isbn 
        << ", Fecha de publicacion: " << fechaPublicacion.mostrar() << endl;
}
