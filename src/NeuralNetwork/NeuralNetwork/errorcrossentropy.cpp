#include "errorcrossentropy.hpp"

Scalar* ErrorCrossEntropy::create(Variable* exact, Variable* estimate) {
    // Make sure sizes correspond
    if(exact->getSize() != estimate->getSize()) {
        Log::print("Incompatible variables");
        return nullptr;
    }
    
    // Create function object and tensor, and return
    return new Scalar(new ErrorCrossEntropy(exact, estimate));
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
    dim n = exact->getSize();
    for(dim i = 0;i < n; ++i) {
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
    
    dim n = estimate->getSize();
    for(dim i = 0;i < n; ++i)
        *(gradientEstimate++) -= gradientResult * (*(valueExact++)) / (*(valueEstimate++));
}
