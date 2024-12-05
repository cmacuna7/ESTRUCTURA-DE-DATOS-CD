#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Fecha.h"
using namespace std;

// Clase para representar datos de una persona (autor)
class Persona {
private:
    string nombre;
    Fecha fechaNacimiento;

public:
    // Constructor por defecto y parametrizado
    Persona(string n = "", Fecha fn = Fecha()) : nombre(n), fechaNacimiento(fn) {}

    // Métodos para acceder a los atributos
    string getNombre() const { return nombre; }
    Fecha getFechaNacimiento() const { return fechaNacimiento; }

    // Métodos para modificar los atributos
    void setNombre(const string& n) { nombre = n; }
    void setFechaNacimiento(const Fecha& fn) { fechaNacimiento = fn; }

    // Mostrar datos de la persona
    void mostrar() const {
        cout << "Nombre: " << nombre << ", Fecha de nacimiento: " << fechaNacimiento.mostrar() << endl;
    }
};

#endif
