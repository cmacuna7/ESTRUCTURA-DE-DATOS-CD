#ifndef CUSTOMOPERATOR_H
#define CUSTOMOPERATOR_H

#include <functional>

using BinaryOp = std::function<int(int, int)>;

class CustomOperator {
public:
    BinaryOp operation;

    CustomOperator(BinaryOp op) : operation(op) {}

    CustomOperator operator+(const CustomOperator& other) const {
        return CustomOperator([=](int a, int b) {
            return operation(a, b) + other.operation(a, b);
        });
    }

    int execute(int a, int b) const {
        return operation(a, b);
    }
};

#endif
