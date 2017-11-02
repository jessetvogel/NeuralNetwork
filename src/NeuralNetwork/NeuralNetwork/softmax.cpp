#include "softmax.hpp"
#include <cmath>

Vector* Softmax::create(Vector* a) {
    // Create function object and vector, and return
    Softmax* softmax = new Softmax(a);
    return new Vector(a->getSize(), softmax);
}

void Softmax::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void Softmax::evaluate() {
    // Evaluate
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    // Determine the maximum value (for numerical stability)
    dimension n = result->getSize();
    scalar max = *valueA;
    for(dimension i = 1;i < n; ++i) {
        if(*valueA > max)
            max = *valueA;
        ++valueA;
    }
    
    // Take exponential and compute sum meanwhile
    valueA = a->getValueAddr();
    scalar sum = 0.0;
    for(dimension i = 0;i < n; ++i)
        sum += (*(valueResult++) = exp((*(valueA)++) - max));
    
    // Normalize
    valueResult = result->getValueAddr();
    for(dimension i = 0;i < n; ++i)
        *(valueResult++) /= sum;
}

void Softmax::backpropagate() {
    // Compute contribution to gradients
    scalar* gradientResult = result->getGradientAddr();
    scalar* valueResult = result->getValueAddr();
    scalar* gradientA = a->getGradientAddr();

    dimension n = result->getSize();
    scalar X = 0.0;
    for(dimension i = 0;i < n; ++i)
        X += (*(gradientResult++)) * (*(valueResult++));

    gradientResult = result->getGradientAddr();
    valueResult = result->getValueAddr();
    for(dimension i = 0;i < n; ++i) {
        *(gradientA++) = (*(valueResult++)) * ((*(gradientResult++)) - X);
    }
}
