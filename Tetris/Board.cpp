/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:       Tetris                                                                  *
 * Autor:           Abner Arboleda                                                          *
 * Fecha de creacion: 01/12/2024                                                            *
 * Fecha de modificacion: 08/11/2024                                                        *
 * Materia:         Estructura de datos                                                     *
 * NRC :            1992                                                                    *
 ********************************************************************************************/
#include "Board.h"

// Implementación de Node
Node::Node(int cols) {
    cells = new int[cols];
    for (int i = 0; i < cols; i++) {
        cells[i] = -1;
    }
    next = nullptr;
}

Node::~Node() {
    delete [] cells;
}

// Implementación de LinkedList
LinkedList::LinkedList() : head(nullptr) { }

LinkedList::~LinkedList() {
    Node* current = head;
    while(current) {
        Node* nxt = current->next;
        delete current;
        current = nxt;
    }
}

void LinkedList::addNode(int cols) {
    Node* newNode = new Node(cols);
    if(!head) {
        head = newNode;
        return;
    }
    Node* cur = head;
    while(cur->next)
        cur = cur->next;
    cur->next = newNode;
}

Node* LinkedList::getNode(int index) {
    Node* cur = head;
    for(int i = 0; i < index && cur; i++){
        cur = cur->next;
    }
    return cur;
}

// Implementación de Board
Board::Board(int r, int c) : rows(r), cols(c) {
    for (int i = 0; i < r; i++){
        list.addNode(c);
    }
}

int& Board::cell(int i, int j) {
    return (list.getNode(i))->cells[j];
}

int Board::getRows() const { return rows; }
int Board::getCols() const { return cols; }
