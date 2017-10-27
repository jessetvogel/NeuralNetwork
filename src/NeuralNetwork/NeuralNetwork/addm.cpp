#include "addm.hpp"

AddM::AddM(Matrix* a, Matrix* b) : a(a), b(b) {}

Matrix* AddM::create(Matrix* a, Matrix* b) {
    // Make sure sizes of the vectors are equal
    if(a->getRowSize() != b->getRowSize() || a->getColumnSize() != b->getColumnSize()) {
        Log::print("Matrices are incompatible");
        return nullptr;
    }
    
    // Create function object and matrix, and return
    AddM* addM = new AddM(a, b);
    return (addM->result = new Matrix(a->getRowSize(), a->getColumnSize(), addM));
}

void AddM::evaluate() {
    // Evaluate inputs
    a->computeValue();
    b->computeValue();

    // Compute sum elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    unsigned int n = a->getRowSize() * a->getColumnSize();
    for(unsigned int i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) + (*(valueB++));
}

void AddM::backpropagate() {
    // Compute gradient
    unsigned int n = sizeof(scalar) * a->getRowSize() * a->getColumnSize();
    memcpy(a->getGradientAddr(), result->getGradientAddr(), n);
    memcpy(b->getGradientAddr(), result->getGradientAddr(), n);
    
    // Backpropagate
    a->computeGradient();
    b->computeGradient();
}
