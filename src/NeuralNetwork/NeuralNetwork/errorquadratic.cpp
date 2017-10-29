#include "errorquadratic.hpp"

Scalar* ErrorQuadratic::create(Variable* exact, Variable* estimate) {
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
    unsigned int n = exact->getSize();
    for(unsigned int i = 0;i < n; ++i) {
        quadraticSum += ((*valueExact) - (*valueEstimate)) * ((*valueExact) - (*valueEstimate));
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
    
    unsigned int n = estimate->getSize();
    for(unsigned int i = 0;i < n; ++i)
        *(gradientEstimate++) += gradientResult * ((*valueExact) - (*valueEstimate));
}
