/*******************************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                                  *
 * Proposito:                      Clase persona para ordenamiento lista circular                      *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz                    *
 * Fecha de creacion:              17/12/2024                                                          *
 * Fecha de modificacion:          18/12/2024                                                          *
 * Materia:                        Estructura de datos                                                 *
 * NRC :                           1992                                                                *
 *******************************************************************************************************/

#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Fecha.h"

using namespace std;

class Persona {
private:
    string nombre;
    string cedula;
    Fecha fechaNacimiento;

public:
    Persona(string n = "", string c = "", Fecha fn = Fecha());
    string getNombre() const;
    string getCedula() const;
    Fecha getFechaNacimiento() const;
    void setNombre(const string& n);
    void setCedula(const string& c);
    void setFechaNacimiento(const Fecha& fn);
    void mostrar() const;
};

#endif // PERSONA_H