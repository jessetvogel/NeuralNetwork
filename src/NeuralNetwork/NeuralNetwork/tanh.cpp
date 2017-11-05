#include "tanh.hpp"
#include <cmath>

void Tanh::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void Tanh::evaluate() {
    // Compute relu elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    dim n = result->getSize();
    for(dim i = 0;i < n; ++i)
        *(valueResult++) = tanh(*(valueA++));
}

void Tanh::backpropagate() {
    // Compute contribution to gradient
    scalar* gradientResult = result->getGradientAddr();
    scalar* valueA = a->getValueAddr();
    scalar* gradientA = a->getGradientAddr();
    
    dim n = a->getSize();
    for(dim i = 0;i < n; ++i) {
        *(gradientA++) += (*(gradientResult++)) * (1.0 - (*valueA) * (*valueA));
        ++valueA;
    }
}
