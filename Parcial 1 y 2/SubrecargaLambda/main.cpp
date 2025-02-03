#include <iostream>
#include "CustomOperator.h"
#include "CircularDoublyLinkedList.h"
#include "Validaciones.h"

void menu() {
    std::cout << "1. Insertar un valor en la lista" << std::endl;
    std::cout << "2. Eliminar un valor de la lista" << std::endl;
    std::cout << "3. Mostrar la lista" << std::endl;
    std::cout << "4. Aplicar operacion sobre los valores de la lista" << std::endl;
    std::cout << "5. Salir" << std::endl;
}

int main() {
    CircularDoublyLinkedList list;
    int choice, value, operand, opChoice;

    // Crear operadores
    CustomOperator add([](int a, int b) { return a + b; });
    CustomOperator multiply([](int a, int b) { return a * b; });
    CustomOperator combined = add + multiply;

    do {
        menu();
        std::cout << "Ingrese una opcion: ";
        choice = leerEntero();

        switch (choice) {
            case 1:
                std::cout << "Ingrese el valor a insertar: ";
                value = leerEntero();
                list.insert(value);
                break;
            case 2:
                std::cout << "Ingrese el valor a eliminar: ";
                value = leerEntero();
                if (list.remove(value)) {
                    std::cout << "Valor eliminado." << std::endl;
                } else {
                    std::cout << "Valor no encontrado." << std::endl;
                }
                break;
            case 3:
                list.display();
                break;
            case 4:
                std::cout << "1. Sumar" << std::endl;
                std::cout << "2. Multiplicar" << std::endl;
                std::cout << "3. Sumar y multiplicar" << std::endl;
                std::cout << "Elija una operacion: ";
                opChoice = leerEntero();

                std::cout << "Ingrese un valor para la operacion: ";
                operand = leerEntero();

                if (opChoice == 1) {
                    list.applyOperation(add, operand);
                } else if (opChoice == 2) {
                    list.applyOperation(multiply, operand);
                } else if (opChoice == 3) {
                    list.applyOperation(combined, operand);
                } else {
                    std::cout << "Opcion de operacion no valida." << std::endl;
                }
                break;
            case 5:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida." << std::endl;
        }

        esperarEnter(); // Esperar por la entrada del usuario

    } while (choice != 5);

    return 0;
}
