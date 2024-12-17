#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Fecha.h"
#include "Utilidades.h"

using namespace std;

class Persona {
private:
    string nombre;
    string segundoNombre;
    string apellido;
    string cedula;
    Fecha fechaNacimiento;
    string correo;

public:
    Persona(string n = "", string sn = "", string a = "", string c = "", Fecha fn = Fecha());

    string getNombre() const;
    string getSegundoNombre() const;
    string getApellido() const;
    string getCedula() const;
    Fecha getFechaNacimiento() const;
    string getCorreo() const;

    void setNombre(const string& n);
    void setSegundoNombre(const string& sn);
    void setApellido(const string& a);
    void setCedula(const string& c);
    void setFechaNacimiento(const Fecha& fn);
    void mostrar() const;
};

#endif // PERSONA_H