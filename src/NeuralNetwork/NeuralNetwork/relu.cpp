#include "relu.hpp"
#include <cmath>

Scalar* ReLU::create(Scalar* a) {
    // Create function object and scalar, and return
    ReLU* reLU = new ReLU(a);
    return new Scalar(reLU);
}

Vector* ReLU::create(Vector* a) {
    // Create function object and vector, and return
    ReLU* reLU = new ReLU(a);
    return new Vector(a->getSize(), reLU);
}

Matrix* ReLU::create(Matrix* a) {
    // Create function object and matrix, and return
    ReLU* reLU = new ReLU(a);
    return new Matrix(a->getRowSize(), a->getColumnSize(), reLU);
}

void ReLU::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void ReLU::evaluate() {
    // Compute relu elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    dimension n = result->getSize();
    for(dimension i = 0;i < n; ++i) {
        *(valueResult++) = (*valueA) > 0.0 ? (*valueA) : 0.0;
        ++valueA;
    }
}

void ReLU::backpropagate() {
    // Compute contribution to gradient
    scalar* valueA = a->getValueAddr();
    scalar* gradientA = a->getGradientAddr();
    
    dimension n = a->getSize();
    for(dimension i = 0;i < n; ++i) {
        if((*(valueA++)) > 0.0)
            *gradientA += 1.0;
        ++gradientA;
    }
}
