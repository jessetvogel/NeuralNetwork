#include "dotmv.hpp"

Vector* DotMV::create(Matrix* a, Variable* b) {
    // Make sure dimensions match
    if(a->getDimension(MATRIX_COLUMNS) != b->getSize()) {
        Log::print("Incompatible matrix and vector");
        return nullptr;
    }
    
    // Create object and vector
    dim length = a->getDimension(MATRIX_ROWS);
    return new Vector(new DotMV(a, b), &length);
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
    
    dim rows = a->getDimension(MATRIX_ROWS);
    dim columns = a->getDimension(MATRIX_COLUMNS);
    for(dim i = 0;i < rows; ++i) {
        // Compute inner product of i'th row of the matrix with vector
        scalar value = 0.0;
        valueB = b->getValueAddr();
        for(dim j = 0;j < columns; ++j)
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
    dim rows = a->getDimension(MATRIX_ROWS);
    dim columns = a->getDimension(MATRIX_COLUMNS);
    for(dim i = 0;i < rows; ++i) {
        valueB = b->getValueAddr();
        gradientB = b->getGradientAddr();
        for(dim j = 0;j < columns; ++j) {
            *(gradientA++) += (*gradientResult) * (*(valueB++));
            *(gradientB++) += (*gradientResult) * (*(valueA++));
        }
       ++ gradientResult;
    }
}
