#include "subtract.hpp"

void Subtract::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void Subtract::evaluate() {
    // Compute difference elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    dimension n = a->getSize();
    for(dimension i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) - (*(valueB++));
}

void Subtract::backpropagate() {
    // Compute contribution to the gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    
    dimension n = result->getSize();
    for(dimension i = 0;i < n; ++i) {
        *(gradientA++) += *gradientResult;
        *(gradientB++) -= *(gradientResult++);
    }
}
