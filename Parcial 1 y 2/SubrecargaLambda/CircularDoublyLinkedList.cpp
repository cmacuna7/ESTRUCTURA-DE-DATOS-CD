#include "CircularDoublyLinkedList.h"

// Metodo para insertar un valor en la lista
void CircularDoublyLinkedList::insert(int value) {
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

// Metodo para eliminar un valor de la lista
bool CircularDoublyLinkedList::remove(int value) {
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

// Metodo para mostrar los valores de la lista
void CircularDoublyLinkedList::display() const {
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

// Metodo para aplicar una operacion sobre los valores de la lista
void CircularDoublyLinkedList::applyOperation(const CustomOperator& op, int operand) {
    if (head == nullptr) return;
    Node* current = head;
    do {
        current->value = op.execute(current->value, operand);
        current = current->next;
    } while (current != head);
}
