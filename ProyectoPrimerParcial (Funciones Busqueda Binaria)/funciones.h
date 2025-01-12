#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>

// Declaración de funciones
std::vector<std::string> dividir(const std::string& linea, char delimitador);
void buscarPorRango(const std::string& rutaArchivo, int anioInicio, int anioFin);
void buscarPorRangoFechaNacimiento(const std::string& rutaArchivo, int anioInicio, int anioFin);
void buscarPorPrefijoAutor(const std::string& rutaArchivo, const std::string& prefijo);
void buscarPorPrefijoISBN(const std::string& rutaArchivo, const std::string& prefijo);

#endif
