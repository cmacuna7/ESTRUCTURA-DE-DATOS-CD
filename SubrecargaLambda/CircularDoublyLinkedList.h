#ifndef CIRCULARDOUBLYLINKEDLIST_H
#define CIRCULARDOUBLYLINKEDLIST_H

#include <iostream>
#include "CustomOperator.h"

class Node {
public:
    int value;
    Node* next;
    Node* prev;
    Node(int v) : value(v), next(nullptr), prev(nullptr) {}
};

class CircularDoublyLinkedList {
private:
    Node* head;

public:
    CircularDoublyLinkedList() : head(nullptr) {}

    // Insertar un valor en la lista
    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    // Eliminar un valor de la lista
    bool remove(int value) {
        if (head == nullptr) return false;
        Node* current = head;
        do {
            if (current->value == value) {
                if (current == head && head->next == head) {
                    delete current;
                    head = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    if (current == head) head = current->next;
                    delete current;
                }
                return true;
            }
            current = current->next;
        } while (current != head);
        return false;
    }

    // Mostrar la lista
    void display() const {
        if (head == nullptr) {
            std::cout << "Lista vacia." << std::endl;
            return;
        }
        Node* current = head;
        do {
            std::cout << current->value << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }

    // Aplicar una operacion sobre los valores de la lista
    void applyOperation(const CustomOperator& op, int operand) {
        if (head == nullptr) return;
        Node* current = head;
        do {
            current->value = op.execute(current->value, operand);
            current = current->next;
        } while (current != head);
    }
};

#endif
