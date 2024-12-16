#include <iostream>
#include <string>
#include <cctype>
#include "validaciones.h" // Incluir la cabecera

using namespace std;

// Función para validar si una expresión infija es válida
bool isValidExpression(const string& expr) {
    int parentheses = 0;      // Contador para balance de paréntesis
    bool lastWasOperator = true; // Controla que no haya operadores consecutivos ni operadores al inicio
    bool lastWasOpenParen = false; // Para validar que un paréntesis de apertura no sea seguido directamente por un operador

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // Verificar que no haya espacios
        if (isspace(c)) {
            cout << "Error: La expresion no debe contener espacios." << endl;
            return false;
        }

        // Verificar caracteres válidos
        if (!(isdigit(c)|| c == '+' || c == '-' || 
            c == '*' || c == '/' || c == '^' || c == '(' || c == ')')) {
            cout << "Error: La expresion contiene caracteres invalidos: " << c << endl;
            return false;
        }

        // Verificar balance y uso correcto de paréntesis
        if (c == '(') {
            parentheses++;
            lastWasOpenParen = true;
        } else if (c == ')') {
            parentheses--;
            if (parentheses < 0) {
                cout << "Error: Parentesis desbalanceados o mal ordenados." << endl;
                return false;
            }
            if (lastWasOperator) {
                cout << "Error: Un operador no puede preceder un parentesis de cierre." << endl;
                return false;
            }
        }

        // Verificar que los operadores no estén consecutivos ni al inicio/final
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            // Permitir un '-' inicial
            if (i == 0 && c == '-') {
                lastWasOperator = false;
                continue;
            }
            
            if (lastWasOperator || lastWasOpenParen) {
                cout << "Error: Operadores consecutivos o mal colocados." << endl;
                return false;
            }
            lastWasOperator = true;
        } else {
            lastWasOperator = false; // Si encontramos un número, letra o paréntesis de cierre
        }

        // Un paréntesis de apertura no puede ser seguido directamente por un operador
        if (lastWasOpenParen && (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')) {
            cout << "Error: Un parentesis de apertura no puede ser seguido directamente por un operador." << endl;
            return false;
        }

        lastWasOpenParen = (c == '(');
    }

    // Verificar si los paréntesis están equilibrados
    if (parentheses != 0) {
        cout << "Error: Parentesis desbalanceados." << endl;
        return false;
    }

    // Verificar que la expresión no termine con un operador
    if (lastWasOperator) {
        cout << "Error: La expresion no puede terminar con un operador." << endl;
        return false;
    }

    return true;
}
