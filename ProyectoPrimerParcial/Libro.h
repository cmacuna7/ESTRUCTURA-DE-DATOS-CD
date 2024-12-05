#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include <iostream>
#include "Persona.cpp"
#include "Fecha.h"
using namespace std;

class Libro {
private:
    string titulo;
    string isbn;
    Persona autor;
    Fecha fechaPublicacion;

public:
    Libro(string t = "", string i = "", Persona a = Persona(), Fecha fp = Fecha());
    string getTitulo() const;
    string getIsbn() const;
    Persona getAutor() const;
    Fecha getFechaPublicacion() const;
    void setTitulo(const string& t);
    void setIsbn(const string& i);
    void setAutor(const Persona& a);
    void setFechaPublicacion(const Fecha& fp);
    void mostrar() const;
};

#endif
