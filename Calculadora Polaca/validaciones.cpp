#include <iostream>
#include <string>
#include <cctype>
#include "validaciones.h" // Incluir la cabecera

using namespace std;

// Funcion para validar si una expresion infija es valida
bool isValidExpression(const std::string& expr) {
    int parentheses = 0;            // Contador para balance de parentesis
    bool lastWasOperator = true;    // Controla si el ultimo caracter fue un operador
    bool lastWasOpenParen = false;  // Verifica si el ultimo caracter fue '('

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // 1. Verificar que no haya espacios
        if (std::isspace(c)) {
            std::cout << "Error: La expresion no debe contener espacios." << std::endl;
            return false;
        }

        // 2. Verificar caracteres validos (numeros, operadores y parentesis)
        if (!(std::isdigit(c) || c == '+' || c == '-' || 
              c == '*' || c == '/' || c == '^' || c == '(' || c == ')')) {
            std::cout << "Error: La expresion contiene caracteres invalidos: " << c << std::endl;
            return false;
        }

        // 3. Manejar parentesis
        if (c == '(') {
            parentheses++;
            lastWasOpenParen = true;
            lastWasOperator = true; // Un operador puede venir despues de '('
        } else if (c == ')') {
            if (parentheses == 0) {
                std::cout << "Error: Parentesis desbalanceados." << std::endl;
                return false;
            }
            if (lastWasOperator) {
                std::cout << "Error: Un operador no puede preceder un parentesis de cierre." << std::endl;
                return false;
            }
            parentheses--;
        }

        // 4. Manejar el '-' como signo negativo o como operador
        if (c == '-') {
            if (lastWasOperator || lastWasOpenParen) {
                // Se permite como signo negativo
                lastWasOperator = false; 
            } else {
                // Es un operador de resta
                if (lastWasOperator) {
                    std::cout << "Error: Operador '-' en posicion invalida." << std::endl;
                    return false;
                }
                lastWasOperator = true;
            }
        }
        // 5. Manejar otros operadores
        else if (c == '+' || c == '*' || c == '/' || c == '^') {
            if (lastWasOperator && !lastWasOpenParen) {
                std::cout << "Error: Operador en posicion invalida o dos operadores consecutivos." << std::endl;
                return false;
            }
            lastWasOperator = true;
        } 
        // 6. Manejar operandos
        else if (std::isdigit(c)) {
            lastWasOperator = false;
        }

        // 7. Verificar despues de '(' debe haber un operando o '('
        if (lastWasOpenParen && !(std::isdigit(c) || c == '(' || c == '-')) {
            std::cout << "Error: Despues de un parentesis de apertura debe haber un operando, '-' o un parentesis de apertura." << std::endl;
            return false;
        }

        lastWasOpenParen = (c == '(');
    }

    // 8. Verificar balance de parentesis
    if (parentheses != 0) {
        std::cout << "Error: Parentesis desbalanceados." << std::endl;
        return false;
    }

    // 9. Verificar que la expresion no termine en un operador
    if (lastWasOperator) {
        std::cout << "Error: La expresion no puede terminar con un operador." << std::endl;
        return false;
    }

    return true;
}
