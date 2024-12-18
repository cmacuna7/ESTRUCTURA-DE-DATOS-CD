#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

class Utilidades {
public:
    static std::string generarCorreo(const std::string& nombre, const std::string& sNombre, const std::string& apellido);
};

#endif // UTILIDADES_H