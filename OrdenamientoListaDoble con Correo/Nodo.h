#ifndef NODO_H
#define NODO_H

#include "Persona.h"

// Nodo de la lista doblemente enlazada
struct Nodo {
    Persona persona;   // Ahora contiene un objeto de tipo Persona
    Nodo* siguiente;
    Nodo* anterior;    // Puntero al nodo anterior
};

#endif // NODO_H