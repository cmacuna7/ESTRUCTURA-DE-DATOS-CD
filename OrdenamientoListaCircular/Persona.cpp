/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Clase persona para ordenamiento lista circular                      *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#include "Persona.h"
#include <iostream>

Persona::Persona(string n, string c, Fecha fn) : nombre(n), cedula(c), fechaNacimiento(fn) {}

string Persona::getNombre() const { return nombre; }

string Persona::getCedula() const { return cedula; }

Fecha Persona::getFechaNacimiento() const { return fechaNacimiento; }

void Persona::setNombre(const string& n) { nombre = n; }

void Persona::setCedula(const string& c) { cedula = c; }

void Persona::setFechaNacimiento(const Fecha& fn) { fechaNacimiento = fn; }

void Persona::mostrar() const {
    cout << "Nombre: " << nombre 
        << ", Cedula: " << cedula 
        << ", Fecha de nacimiento: " << fechaNacimiento.mostrar() << endl;
}