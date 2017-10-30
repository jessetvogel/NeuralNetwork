#include "errorquadratic.hpp"

Scalar* ErrorQuadratic::create(Variable* exact, Variable* estimate) {
    // Make sure the sizes are the same
    if(exact->getSize() != estimate->getSize()) {
        Log::print("Variables are incompatible");
        return nullptr;
    }
    
    // Create function object and scalar, and return
    ErrorQuadratic* error = new ErrorQuadratic(exact, estimate);
    return new Scalar(error);
}

void ErrorQuadratic::setResult(Variable* variable) {
    result = variable;
    result->addChild(estimate);
}

void ErrorQuadratic::evaluate() {
    // Compute quadratic error
    scalar* valueExact = exact->getValueAddr();
    scalar* valueEstimate = estimate->getValueAddr();
    
    scalar quadraticSum = 0.0;
    dimension n = exact->getSize();
    for(dimension i = 0;i < n; ++i) {
        quadraticSum += ((*valueEstimate) - (*valueExact)) * ((*valueEstimate) - (*valueExact));
        ++valueExact;
        ++valueEstimate;
    }
    
    // Store result
    *(result->getValueAddr()) = 0.5 * quadraticSum;
}

void ErrorQuadratic::backpropagate() {
    // Compute contribution to gradient
    scalar gradientResult = *(result->getGradientAddr());
    scalar* valueExact = exact->getValueAddr();
    scalar* valueEstimate = estimate->getValueAddr();
    scalar* gradientEstimate = estimate->getGradientAddr();
    
    dimension n = estimate->getSize();
    for(dimension i = 0;i < n; ++i)
        *(gradientEstimate++) += gradientResult * ((*valueEstimate++) - (*valueExact++));
}
