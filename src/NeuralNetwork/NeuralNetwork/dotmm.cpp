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
    // Compute matrix-matrix product
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    dimension rows = a->getRowSize();
    dimension columns = b->getColumnSize();
    dimension K = a->getColumnSize();
    for(dimension i = 0;i < rows; ++i) {
        for(dimension j = 0;j < columns; ++j) {
            scalar value = 0.0;
            scalar* vB = valueB + j;
            scalar* vA = valueA + i * K;
            for(dimension k = 0;k < K; ++k) {
                value += (*(vA++)) * (*vB);
                vB += columns;
            }
            *(valueResult++) = value;
        }
    }
}

void DotMM::backpropagate() {
    // Compute contribution to the gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    dimension I = a->getRowSize();
    dimension J = b->getColumnSize();
    dimension K = a->getColumnSize();
    
    for(dimension i = 0;i < I; ++i) {
        for(dimension j = 0;j < J; ++j) {
            scalar* vA = valueA + i * K;
            scalar* vB = valueB + j;
            scalar* gA = gradientA + i * K;
            scalar* gB = gradientB + j;
            for(dimension k = 0;k < K; ++k) {
                *(gA++) += (*gradientResult) * (*vB);
                *gB += (*gradientResult) * (*(vA++));
                vB += J;
                gB += J;
            }
            ++gradientResult;
        }
    }
}
