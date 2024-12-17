#include "Persona.h"
#include "Utilidades.cpp" // Include the header for Utilidades
#include <iostream>

Persona::Persona(string n, string sn, string a, string c, Fecha fn)
    : nombre(n), segundoNombre(sn), apellido(a), cedula(c), fechaNacimiento(fn) {
    correo = Utilidades::generarCorreo(n, sn, a);
}

string Persona::getNombre() const { return nombre; }

string Persona::getSegundoNombre() const { return segundoNombre; }

string Persona::getApellido() const { return apellido; }

string Persona::getCedula() const { return cedula; }

Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

string Persona::getCorreo() const { return correo; }

void Persona::setNombre(const string& n) { 
    nombre = n; 
    correo = Utilidades::generarCorreo(nombre, segundoNombre, apellido);
}

void Persona::setSegundoNombre(const string& sn) { 
    segundoNombre = sn; 
    correo = Utilidades::generarCorreo(nombre, segundoNombre, apellido);
}

void Persona::setApellido(const string& a) { 
    apellido = a; 
    correo = Utilidades::generarCorreo(nombre, segundoNombre, apellido);
}

void Persona::setCedula(const string& c) { cedula = c; }

void Persona::setFechaNacimiento(const Fecha& fn) { fechaNacimiento = fn; }

void Persona::mostrar() const {
    cout << left << setw(20) << "Primer Nombre" 
        << setw(20) << "Segundo Nombre"
        << setw(15) << "Apellido"
        << setw(20) << "Cedula" 
        << setw(30) << "Correo"
        << setw(30) << "Fecha de Nacimiento" << endl;
    cout << string(130, '-') << endl;

    cout << left << setw(20) << nombre
        << setw(20) << segundoNombre
        << setw(15) << apellido
        << setw(20) << cedula 
        << setw(30) << correo
        << setw(30) << fechaNacimiento.mostrar() << endl;
}