#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <regex>
#include <iostream>
#include <cctype>

using namespace std;

class Validaciones {
public:
    static bool validarFecha(const string& fecha);
    static bool validarCedula(const string& cedula);
    static bool validarTextoNoVacio(const string& texto, const string& campo);
    static bool validarTexto(const string& texto, const string& campo);
    static bool validarTituloNombre(const string& texto, const string& campo);

private:
    static int diasEnMes(int mes, int anio);
    static bool esBisiesto(int anio);
};

#endif // VALIDACIONES_H