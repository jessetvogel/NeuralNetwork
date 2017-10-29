#include "subtract.hpp"

Scalar* Subtract::create(Scalar* a, Scalar* b) {
    // Create function object and scalar, and return
    Subtract* subtract = new Subtract(a, b);
    return new Scalar(subtract);
}

Vector* Subtract::create(Vector* a, Vector* b) {
    // Make sure sizes of the vectors are equal
    if(a->getSize() != b->getSize()) {
        Log::print("Vectors are incompatible");
        return nullptr;
    }
    
    // Create function object and vector, and return
    Subtract* subtract = new Subtract(a, b);
    return new Vector(a->getSize(), subtract);
}

Matrix* Subtract::create(Matrix* a, Matrix* b) {
    // Make sure sizes of the matrices are equal
    if(a->getRowSize() != b->getRowSize() || a->getColumnSize() != b->getColumnSize()) {
        Log::print("Matrices are incompatible");
        return nullptr;
    }
    
    // Create function object and matrix, and return
    Subtract* subtract = new Subtract(a, b);
    return new Matrix(a->getRowSize(), a->getColumnSize(), subtract);
}

void Subtract::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void Subtract::evaluate() {
    // Compute difference elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    unsigned int n = a->getSize();
    for(unsigned int i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) - (*(valueB++));
}

void Subtract::backpropagate() {
    // Compute contribution to the gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    
    unsigned int n = result->getSize();
    for(unsigned int i = 0;i < n; ++i) {
        *(gradientA++) += *gradientResult;
        *(gradientB++) -= *(gradientResult++);
    }
}
