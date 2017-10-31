#include "add.hpp"

Scalar* Add::create(Scalar* a, Scalar* b) {
    // Create function object and scalar, and return
    Add* add = new Add(a, b);
    return new Scalar(add);
}

Vector* Add::create(Vector* a, Vector* b) {
    // Make sure sizes of the vectors are equal
    if(a->getSize() != b->getSize()) {
        Log::print("Vectors are incompatible");
        return nullptr;
    }
    
    // Create function object and vector, and return
    Add* add = new Add(a, b);
    return new Vector(a->getSize(), add);
}

Matrix* Add::create(Matrix* a, Matrix* b) {
    // Make sure sizes of the matrices are equal
    if(a->getRowSize() != b->getRowSize() || a->getColumnSize() != b->getColumnSize()) {
        Log::print("Matrices are incompatible");
        return nullptr;
    }
    
    // Create function object and matrix, and return
    Add* add = new Add(a, b);
    return new Matrix(a->getRowSize(), a->getColumnSize(), add);
}

void Add::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void Add::evaluate() {
    // Compute sum elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();

    dimension n = result->getSize();
    for(dimension i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) + (*(valueB++));
}

void Add::backpropagate() {
    // Compute contribution to the gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    
    dimension n = result->getSize();
    for(dimension i = 0;i < n; ++i) {
        *(gradientA++) += *(gradientResult);
        *(gradientB++) += *(gradientResult++);
    }
}
