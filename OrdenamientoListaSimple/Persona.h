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