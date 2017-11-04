#include "sigmoid.hpp"
#include <cmath>

void Sigmoid::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void Sigmoid::evaluate() {
    // Compute sigmoid elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    dimension n = result->getSize();
    for(dimension i = 0;i < n; ++i)
        *(valueResult++) = sig(*(valueA++));
}

void Sigmoid::backpropagate() {
    // Compute contribution to gradient
    scalar* valueResult = result->getValueAddr();
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    
    dimension n = result->getSize();
    for(dimension i = 0;i < n; ++i) {
        *(gradientA++) += (*(gradientResult++)) * (*valueResult) * (1.0 - (*valueResult));
        ++ valueResult;
    }
}

scalar Sigmoid::sig(scalar x) {
    return 1.0 / (1.0 + exp(-x));
}
