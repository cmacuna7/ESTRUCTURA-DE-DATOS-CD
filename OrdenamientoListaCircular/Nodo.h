#ifndef NODO_H
#define NODO_H

#include "Persona.h"

// Nodo de la lista circular simple
struct Nodo {
    Persona persona;   // Ahora contiene un objeto de tipo Persona
    Nodo* siguiente;   // Puntero al siguiente nodo (o al primero si es el último)
};

#endif // NODO_H