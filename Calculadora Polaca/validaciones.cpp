#include <iostream>
#include <string>
#include <cctype>
#include "validaciones.h" // Incluir la cabecera

using namespace std;

// Función para validar si una expresión infija es válida
bool isValidExpression(const string& expr) {
    int parentheses = 0;        // Contador para balance de paréntesis
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
        if (!(isdigit(c) || c == '+' || c == '-' || 
            c == '*' || c == '/' || c == '^' || c == '(' || c == ')')) {
            cout << "Error: La expresion contiene caracteres invalidos: " << c << endl;
            return false;
        }

        // Verificar balance y uso correcto de paréntesis
        if (c == '(') {
            parentheses++;
            lastWasOpenParen = true;
            lastWasOperator = true; // Un paréntesis de apertura puede preceder a un número o signo
            continue;
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
            // Permitir un '-' inicial o después de un '(' como signo
            if ((i == 0 || lastWasOpenParen) && c == '-') {
                lastWasOperator = false; // Tratar el signo como parte de un número
                continue;
            }

            if (lastWasOperator) {
                cout << "Error: Operadores consecutivos o mal colocados." << endl;
                return false;
            }
            lastWasOperator = true;

            // Validar si el operador está al final de la expresión
            if (i == expr.length() - 1) {
                cout << "Error: La expresion no puede terminar con un operador." << endl;
                return false;
            }

            // Validar si un operador aparece antes de un paréntesis de cierre
            if (i + 1 < expr.length() && expr[i + 1] == ')') {
                cout << "Error: Un operador no puede estar antes de un parentesis de cierre." << endl;
                return false;
            }
        } else {
            lastWasOperator = false; // Si encontramos un número o paréntesis de cierre
        }

        // Un paréntesis de apertura no puede ser seguido directamente por un operador (excepto '-')
        if (lastWasOpenParen && (c == '+' || c == '*' || c == '/' || c == '^')) {
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