#ifndef NODO_H
#define NODO_H

#include "Persona.h"

// Nodo de la lista simplemente enlazada
struct Nodo {
    Persona persona;   // Ahora contiene un objeto de tipo Persona
    Nodo* siguiente;
};

#endif // NODO_H