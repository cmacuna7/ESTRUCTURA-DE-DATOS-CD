#include "Libro.h"

// Constructor
Libro::Libro(string t, string a, string i, int an)
    : titulo(t), autor(a), isbn(i), anio(an) {}

// Métodos para acceder a los atributos
string Libro::getTitulo() const {
    return titulo;
}

string Libro::getAutor() const {
    return autor;
}

string Libro::getIsbn() const {
    return isbn;
}

int Libro::getAnio() const {
    return anio;
}

// Método para mostrar la información del libro
void Libro::mostrar() const {
    cout << titulo << " por " << autor << ", ISBN: " << isbn << ", Anio: " << anio << endl;
}
