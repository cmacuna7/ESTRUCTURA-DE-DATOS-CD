#ifndef LISTACIRCULARSIMPLE_H
#define LISTACIRCULARSIMPLE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Nodo.h"
#include "Persona.cpp"

using namespace std;

// Clase para la lista circular simple
class ListaCircularSimple {
private:
    Nodo* cabeza = nullptr;
    Nodo* cola = nullptr;  // Puntero al último nodo de la lista
    string archivoPersonas = "personas.txt";  // Archivo donde se guardarán las personas
    bool evitarGuardar = false;               // Bandera para controlar el guardado

public:
    // Agregar persona
    void agregarPersona(const Persona& persona);
    // Imprimir todas las personas
    void imprimirPersonas();
    // Buscar persona por nombre
    Nodo* buscarPersona(const string& nombre);
    // Buscar persona por cédula
    Nodo* buscarPersonaPorCedula(const string& cedula);
    // Eliminar persona por nombre
    void eliminarPersona(const string& nombre);
    // Eliminar persona por cédula
    void eliminarPersonaPorCedula(const string& cedula);
    // Crear backup
    void crearBackup(const string& nombreArchivo);
    // Restaurar backup
    void restaurarBackup(const string& nombreArchivo);
    // Guardar todas las personas en el archivo
    void guardarPersonasEnArchivo();
    // Cargar las personas desde el archivo
    void cargarPersonasDesdeArchivo();
    // Limpiar la lista
    void limpiarLista();
    // Ordenar la lista por cédula usando merge sort externo
    void ordenarPorCedula();
};

#endif // LISTACIRCULARSIMPLE_H