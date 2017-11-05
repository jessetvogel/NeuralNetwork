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
    
    dim n = a->getSize();
    for(dim i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) - (*(valueB++));
}

void Subtract::backpropagate() {
    // Compute contribution to the gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    
    dim n = result->getSize();
    for(dim i = 0;i < n; ++i) {
        *(gradientA++) += *gradientResult;
        *(gradientB++) -= *(gradientResult++);
    }
}
