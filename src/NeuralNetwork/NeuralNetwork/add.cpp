#include "add.hpp"

void Add::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void Add::evaluate() {
    // Compute sum elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();

    dim n = result->getSize();
    for(dim i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) + (*(valueB++));
}

void Add::backpropagate() {
    // Compute contribution to the gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    
    dim n = result->getSize();
    for(dim i = 0;i < n; ++i) {
        *(gradientA++) += *(gradientResult);
        *(gradientB++) += *(gradientResult++);
    }
}
