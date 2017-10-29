#include "dotmv.hpp"

Vector* DotMV::create(Matrix* a, Vector* b) {
    // Make sure the number of columns matches the size of the vector
    if(a->getColumnSize() != b->getSize()) {
        Log::print("Matrix and vector are incompatible");
        return nullptr;
    }
    
    // Create function object and vector, and return
    DotMV* dotMV = new DotMV(a, b);
    return new Vector(a->getRowSize(), dotMV);
}

void DotMV::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void DotMV::evaluate() {
    // Computes product between matrix a and vector b
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB;
    
    const unsigned int rows = a->getRowSize();
    const unsigned int columns = a->getColumnSize();
    for(unsigned int i = 0;i < rows; ++i) {
        // Compute inner product of i'th row of the matrix with vector
        scalar value = 0.0;
        valueB = b->getValueAddr();
        for(unsigned int j = 0;j < columns; ++j)
            value += (*(valueA++)) * (*(valueB++));
        
        // Store result
        *(valueResult++) = value;
    }
}

void DotMV::backpropagate() {
    // Compute contribution to gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* valueA = a->getValueAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* valueB;
    scalar* gradientB;
    
    // Feels good, computing an outer product and a matrix-vector product in just 10 lines of code
    unsigned int rows = a->getRowSize();
    unsigned int columns = a->getColumnSize();
    for(unsigned int i = 0;i < rows; ++i) {
        valueB = b->getValueAddr();
        gradientB = b->getGradientAddr();
        for(unsigned int j = 0;j < columns; ++j) {
            *(gradientA++) += (*gradientResult) * (*(valueB++));
            *(gradientB++) += (*gradientResult) * (*(valueA++));
        }
       ++ gradientResult;
    }
}
