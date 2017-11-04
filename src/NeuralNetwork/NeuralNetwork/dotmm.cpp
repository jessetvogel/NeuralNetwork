#include "dotmm.hpp"

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
    
    dimension rows = a->getDimension(MATRIX_ROWS);
    dimension columns = b->getDimension(MATRIX_COLUMNS);
    dimension K = a->getDimension(MATRIX_COLUMNS);
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
    
    dimension I = a->getDimension(MATRIX_ROWS);
    dimension J = b->getDimension(MATRIX_COLUMNS);
    dimension K = a->getDimension(MATRIX_COLUMNS);
    
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
