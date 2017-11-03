#include "tanh.hpp"
#include <cmath>

Scalar* Tanh::create(Scalar* a) {
    // Create function object and scalar, and return
    Tanh* tanh = new Tanh(a);
    return new Scalar(tanh);
}

Vector* Tanh::create(Vector* a) {
    // Create function object and vector, and return
    Tanh* tanh = new Tanh(a);
    return new Vector(a->getSize(), tanh);
}

Matrix* Tanh::create(Matrix* a) {
    // Create function object and matrix, and return
    Tanh* tanh = new Tanh(a);
    return new Matrix(a->getRowSize(), a->getColumnSize(), tanh);
}

void Tanh::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void Tanh::evaluate() {
    // Compute relu elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    dimension n = result->getSize();
    for(dimension i = 0;i < n; ++i)
        *(valueResult++) = tanh(*(valueA++));
}

void Tanh::backpropagate() {
    // Compute contribution to gradient
    scalar* gradientResult = result->getGradientAddr();
    scalar* valueA = a->getValueAddr();
    scalar* gradientA = a->getGradientAddr();
    
    dimension n = a->getSize();
    for(dimension i = 0;i < n; ++i) {
        *(gradientA++) += (*(gradientResult++)) * (1.0 - (*valueA) * (*valueA));
        ++valueA;
    }
}
