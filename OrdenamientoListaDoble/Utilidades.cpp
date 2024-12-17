#include "Utilidades.h"
#include <algorithm>

std::string Utilidades::generarCorreo(const std::string& nombre, const std::string& sNombre, const std::string& apellido) {
    std::string nombreLower = nombre;
    std::string sNombreLower = sNombre;
    std::string apellidoLower = apellido;
    for (int i = 0; i < nombreLower.length(); i++) {
        nombreLower[i] = tolower(nombreLower[i]);
    }
    for (int i = 0; i < sNombreLower.length(); i++) {
        sNombreLower[i] = tolower(sNombreLower[i]);
    }
    for (int i = 0; i < apellidoLower.length(); i++) {
        apellidoLower[i] = tolower(apellidoLower[i]);
    }
    return std::string(1, nombreLower[0]) + std::string(1, sNombreLower[0]) + apellidoLower + "@espe.edu.ec";
}