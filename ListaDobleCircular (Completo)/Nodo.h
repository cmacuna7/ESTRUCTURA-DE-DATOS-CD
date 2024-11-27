/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista doble circular                 *
 * Autor:                          Marcelo Acuña, Abner Arboleda, Christian Bonifaz    *
 * Fecha de creacion:              25/11/2024                                          *
 * Fecha de modificacion:          25/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1992                                                *
 ***************************************************************************************/
#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
private:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;

public:
    Nodo(T dato) : dato(dato), siguiente(this), anterior(this) {} // Nodo se apunta a sí mismo
    ~Nodo() {}

    // Getters
    T getDato() const { return dato; }
    Nodo* getSiguiente() const { return siguiente; }
    Nodo* getAnterior() const { return anterior; }

    // Setters
    void setDato(T dato) { this->dato = dato; }
    void setSiguiente(Nodo* siguiente) { this->siguiente = siguiente; }
    void setAnterior(Nodo* anterior) { this->anterior = anterior; }
};

#endif
