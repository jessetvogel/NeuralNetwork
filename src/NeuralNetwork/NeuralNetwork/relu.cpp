#include "relu.hpp"
#include <cmath>

void ReLU::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void ReLU::evaluate() {
    // Compute relu elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    dim n = result->getSize();
    for(dim i = 0;i < n; ++i) {
        *(valueResult++) = (*valueA) > 0.0 ? (*valueA) : 0.0;
        ++valueA;
    }
}

void ReLU::backpropagate() {
    // Compute contribution to gradient
    scalar* gradientResult = result->getGradientAddr();
    scalar* valueA = a->getValueAddr();
    scalar* gradientA = a->getGradientAddr();
    
    dim n = a->getSize();
    for(dim i = 0;i < n; ++i) {
        if((*(valueA++)) > 0.0)
            *gradientA += *gradientResult;
        ++gradientA;
        ++gradientResult;
    }
}
