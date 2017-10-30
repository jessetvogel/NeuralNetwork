#include "dotmm.hpp"

Matrix* DotMM::create(Matrix* a, Matrix* b) {
    // Make sure the number of columns of a matches the number of rows of b
    if(a->getColumnSize() != b->getRowSize()) {
        Log::print("Matrices are incompatible");
        return nullptr;
    }
    
    // Create function object and vector, and return
    DotMM* dotMM = new DotMM(a, b);
    return new Matrix(a->getRowSize(), b->getColumnSize(), dotMM);
}

void DotMM::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void DotMM::evaluate() {
    // TODO
}

void DotMM::backpropagate() {
    // TODO
}
