#include "subtractm.hpp"

SubtractM::SubtractM(Matrix* a, Matrix* b) : a(a), b(b) {}

Matrix* SubtractM::create(Matrix* a, Matrix* b) {
    // Make sure sizes of the vectors are equal
    if(a->getRowSize() != b->getRowSize() || a->getColumnSize() != b->getColumnSize()) {
        Log::print("Matrices are incompatible");
        return nullptr;
    }
    
    // Create function object and matrix, and return
    SubtractM* subtractM = new SubtractM(a, b);
    return (subtractM->result = new Matrix(a->getRowSize(), a->getColumnSize(), subtractM));
}

void SubtractM::evaluate() {
    // Evaluate inputs
    a->computeValue();
    b->computeValue();

    // Compute difference elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    unsigned int n = a->getRowSize() * a->getColumnSize();
    for(unsigned int i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) - (*(valueB++));
}

void SubtractM::backpropagate() {
    // Compute gradients
    unsigned int n = sizeof(scalar) * a->getRowSize() * a->getColumnSize();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    scalar* gradientResult = result->getGradientAddr();
    
    for(unsigned int i = 0;i < n; ++i)
        *(gradientB++) = - (*(gradientA++) = *(gradientResult++));
    
    // Backpropagate
    a->computeGradient();
    b->computeGradient();
}
