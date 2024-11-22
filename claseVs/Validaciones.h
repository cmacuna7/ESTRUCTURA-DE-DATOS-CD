/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Validaciones                                        *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              21/11/2024                                          *
 * Fecha de modificacion:          21/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 **************************************************************************************/

#include <string>   // Para std::string
#include <iostream> // Para std::cout
#include <cctype>   // Para isdigit e isalpha
#include <cstdlib>  // Para atoi y atof
#include <stdexcept> // Para std::invalid_argument
#include <cstring>  // Para strchr
#include <conio.h>  // Para getch (específico de Windows)


#if !defined(__Validaciones_Validaciones_h)
#define __Validaciones_Validaciones_h

template<typename T>
class Validaciones
{
   public:
      Validaciones();
      // Método para ingresar datos
      T ingresar(const std::string& msj, const std::string& tipo);
      // Método para validar cédula ecuatoriana
      bool validarCedula(const std::string& cedula); // Cambiado el tipo a std::string
   protected:
   private:
      T numero;
};

#endif