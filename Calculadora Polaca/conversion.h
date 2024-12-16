#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>

// Declaraciones de funciones
int precedence(char op);
float applyOperator(char op, float a, float b);
std::string infixToPrefix(std::string infix);
std::string infixToPostfix(std::string infix);
float evaluatePrefix(std::string prefix);

#endif // CONVERSION_H
