#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Fecha.h"

using namespace std;

class Persona {
private:
    string nombre;
    Fecha fechaNacimiento;

public:
    Persona(string n = "", Fecha fn = Fecha());
    string getNombre() const;
    Fecha getFechaNacimiento() const;
    void setNombre(const string& n);
    void setFechaNacimiento(const Fecha& fn);
    void mostrar() const;
};

#endif // PERSONA_H
