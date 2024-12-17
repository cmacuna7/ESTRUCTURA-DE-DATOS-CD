#include <iostream>
#include <string>
#include <cctype>
#include "validaciones.h" // Incluir la cabecera

using namespace std;

// Función para validar si una expresión infija es válida
bool isValidExpression(const std::string& expr) {
    int parentheses = 0;            // Contador para balance de paréntesis
    bool lastWasOperator = true;    // Controla si el último carácter fue un operador
    bool lastWasOpenParen = false;  // Verifica si el último carácter fue '('

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // 1. Verificar que no haya espacios
        if (std::isspace(c)) {
            std::cout << "Error: La expresion no debe contener espacios." << std::endl;
            return false;
        }

        // 2. Verificar caracteres válidos
        if (!(std::isdigit(c) || c == '+' || c == '-' || 
              c == '*' || c == '/' || c == '^' || c == '(' || c == ')')) {
            std::cout << "Error: La expresion contiene caracteres invalidos: " << c << std::endl;
            return false;
        }

        // 3. Manejar paréntesis
        if (c == '(') {
            parentheses++;
            lastWasOpenParen = true;
        } else if (c == ')') {
            if (parentheses == 0) {
                std::cout << "Error: Parantesis desbalanceados." << std::endl;
                return false;
            }
            parentheses--;
        }

        // 4. Manejar operadores
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (lastWasOperator && !lastWasOpenParen) {
                std::cout << "Error: Operador en posicion invalida." << std::endl;
                return false;
            }
            lastWasOperator = true;
        } else {
            lastWasOperator = false;
        }

        lastWasOpenParen = false;
    }

    if (parentheses != 0) {
        std::cout << "Error: Parentesis desbalanceados." << std::endl;
        return false;
    }

    return true;
}
