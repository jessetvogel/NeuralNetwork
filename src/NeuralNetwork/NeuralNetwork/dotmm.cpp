#include "dotmm.hpp"

Matrix* DotMM::create(Matrix* a, Matrix* b) {
    // Make sure dimensions match
    if(a->getDimension(MATRIX_COLUMNS) != b->getDimension(MATRIX_ROWS)) {
        Log::print("Incompatible matrices");
        return nullptr;
    }
    
    // Create object and vector
    dim dimensions[2] = { a->getDimension(MATRIX_ROWS), b->getDimension(MATRIX_COLUMNS) };
    return new Matrix(new DotMM(a, b), dimensions);
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
    
    dim rows = a->getDimension(MATRIX_ROWS);
    dim columns = b->getDimension(MATRIX_COLUMNS);
    dim K = a->getDimension(MATRIX_COLUMNS);
    for(dim i = 0;i < rows; ++i) {
        for(dim j = 0;j < columns; ++j) {
            scalar value = 0.0;
            scalar* vB = valueB + j;
            scalar* vA = valueA + i * K;
            for(dim k = 0;k < K; ++k) {
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
    
    dim I = a->getDimension(MATRIX_ROWS);
    dim J = b->getDimension(MATRIX_COLUMNS);
    dim K = a->getDimension(MATRIX_COLUMNS);
    
    for(dim i = 0;i < I; ++i) {
        for(dim j = 0;j < J; ++j) {
            scalar* vA = valueA + i * K;
            scalar* vB = valueB + j;
            scalar* gA = gradientA + i * K;
            scalar* gB = gradientB + j;
            for(dim k = 0;k < K; ++k) {
                *(gA++) += (*gradientResult) * (*vB);
                *gB += (*gradientResult) * (*(vA++));
                vB += J;
                gB += J;
            }
            ++gradientResult;
        }
    }
}
