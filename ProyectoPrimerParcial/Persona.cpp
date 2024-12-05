#include "Persona.h"
#include <iostream>

Persona::Persona(string n, Fecha fn) : nombre(n), fechaNacimiento(fn) {}

string Persona::getNombre() const { return nombre; }
Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

void Persona::setNombre(const string& n) { nombre = n; }
void Persona::setFechaNacimiento(const Fecha& fn) { fechaNacimiento = fn; }

void Persona::mostrar() const {
    cout << "Nombre: " << nombre << ", Fecha de nacimiento: " << fechaNacimiento.mostrar() << endl;
}
