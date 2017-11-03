#include "errorcrossentropy.hpp"

Scalar* ErrorCrossEntropy::create(Variable* exact, Variable* estimate) {
    // Make sure the sizes are the same
    if(exact->getSize() != estimate->getSize()) {
        Log::print("Variables are incompatible");
        return nullptr;
    }
    
    // Create function object and scalar, and return
    ErrorCrossEntropy* error = new ErrorCrossEntropy(exact, estimate);
    return new Scalar(error);
}

void ErrorCrossEntropy::setResult(Variable* variable) {
    result = variable;
    result->addChild(estimate);
}

void ErrorCrossEntropy::evaluate() {
    // Compute cross entropy error
    scalar* valueExact = exact->getValueAddr();
    scalar* valueEstimate = estimate->getValueAddr();
    
    scalar sum = 0.0;
    dimension n = exact->getSize();
    for(dimension i = 0;i < n; ++i) {
        if(*valueExact != 0.0)
            sum -= (*valueExact) * log(*valueEstimate);
        ++valueExact;
        ++valueEstimate;
    }
    
    // Store result
    *(result->getValueAddr()) = sum;
}

void ErrorCrossEntropy::backpropagate() {
    // Compute contribution to gradient
    scalar gradientResult = *(result->getGradientAddr());
    scalar* valueExact = exact->getValueAddr();
    scalar* valueEstimate = estimate->getValueAddr();
    scalar* gradientEstimate = estimate->getGradientAddr();
    
    dimension n = estimate->getSize();
    for(dimension i = 0;i < n; ++i)
        *(gradientEstimate++) -= gradientResult * (*(valueExact++)) / (*(valueEstimate++));
}
