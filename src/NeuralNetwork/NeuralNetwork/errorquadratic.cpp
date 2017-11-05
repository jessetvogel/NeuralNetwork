#include "errorquadratic.hpp"

Scalar* ErrorQuadratic::create(Variable* exact, Variable* estimate) {
    // Make sure sizes correspond
    if(exact->getSize() != estimate->getSize()) {
        Log::print("Incompatible variables");
        return nullptr;
    }
    
    // Create function object and tensor, and return
    return new Scalar(new ErrorQuadratic(exact, estimate));
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
    dim n = exact->getSize();
    for(dim i = 0;i < n; ++i) {
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
    
    dim n = estimate->getSize();
    for(dim i = 0;i < n; ++i)
        *(gradientEstimate++) += gradientResult * ((*valueEstimate++) - (*valueExact++));
}
