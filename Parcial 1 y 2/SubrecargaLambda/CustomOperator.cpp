#include "CustomOperator.h"

CustomOperator::CustomOperator(BinaryOp op) : operation(op) {}

CustomOperator CustomOperator::operator+(const CustomOperator& other) const {
    return CustomOperator([=](int a, int b) {
        return operation(a, b) + other.operation(a, b);
    });
}

int CustomOperator::execute(int a, int b) const {
    return operation(a, b);
}
