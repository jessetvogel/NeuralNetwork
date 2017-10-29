#include "sigmoid.hpp"
#include <cmath>

Scalar* Sigmoid::create(Scalar* a) {
    // Create function object and vector, and return
    Sigmoid* sigmoid = new Sigmoid(a);
    return new Scalar(sigmoid);
}

Vector* Sigmoid::create(Vector* a) {
    // Create function object and vector, and return
    Sigmoid* sigmoid = new Sigmoid(a);
    return new Vector(a->getSize(), sigmoid);
}

Matrix* Sigmoid::create(Matrix* a) {
    // Create function object and vector, and return
    Sigmoid* sigmoid = new Sigmoid(a);
    return new Matrix(a->getRowSize(), a->getColumnSize(), sigmoid);
}

void Sigmoid::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void Sigmoid::evaluate() {
    // Compute sigmoid elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    unsigned int n = result->getSize();
    for(unsigned int i = 0;i < n; ++i)
        *(valueResult++) = sig(*(valueA++));
}

void Sigmoid::backpropagate() {
    // Compute contribution to gradient
    scalar* valueResult = result->getValueAddr();
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    
    unsigned int n = result->getSize();
    for(unsigned int i = 0;i < n; ++i)
        *(gradientA++) += (*(gradientResult++)) * (*(valueResult));
}

scalar Sigmoid::sig(scalar x) {
    return 1.0 / (1.0 + exp(-x));
}
