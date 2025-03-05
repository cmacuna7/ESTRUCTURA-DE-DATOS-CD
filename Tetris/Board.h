/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:       Tetris                                                                  *
 * Autor:           Abner Arboleda                                                          *
 * Fecha de creacion: 01/12/2024                                                            *
 * Fecha de modificacion: 08/11/2024                                                        *
 * Materia:         Estructura de datos                                                     *
 * NRC :            1992                                                                    *
 ********************************************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;

const int boardWidth = 10;
const int boardHeight = 20;

// Clase Node: representa un nodo (fila) de la lista enlazada.
class Node {
public:
    int* cells;
    Node* next;
    Node(int cols);
    ~Node();
};

// Clase LinkedList: maneja los nodos.
class LinkedList {
    Node* head;
public:
    LinkedList();
    ~LinkedList();
    void addNode(int cols);
    Node* getNode(int index);
};

// Clase Board: utiliza LinkedList para almacenar las filas.
class Board {
    int rows, cols;
    LinkedList list;
public:
    Board(int r, int c);
    int& cell(int i, int j);
    int getRows() const;
    int getCols() const;
};

#endif // BOARD_H
