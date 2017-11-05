#include "dot.hpp"

void Dot::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
    result->addChild(b);
}

void Dot::evaluate() {
    // Computes inner product between vectors a and b
    scalar value = 0.0;
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    dim n = a->getSize();
    for(dim i = 0;i < n; ++i)
        value += (*(valueA++)) * (*(valueB++));
    
    // Store result
    *(result->getValueAddr()) = value;
}

void Dot::backpropagate() {
    // Compute contribution to the gradients
    scalar gradientResult = *(result->getGradientAddr());
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    
    dim n = a->getSize();
    for(dim i = 0;i < n; ++i) {
        *(gradientA++) += gradientResult * (*(valueB++));
        *(gradientB++) += gradientResult * (*(valueA++));
    }
}
