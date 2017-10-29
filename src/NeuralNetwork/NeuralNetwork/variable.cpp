#include "variable.hpp"

Variable::Variable(unsigned int size, Function* function) : size(size), function(function) {
    value = new scalar[size];
    gradient = new scalar[size];
}

Variable::~Variable() {
    delete function;
    delete[] value;
    delete[] gradient;
}

void Variable::computeValue() {
    // If already done, return
    if(computedValue) return;
    
    // Mark as done
    computedValue = true;
    
    // First make sure all inputs are evaluated
    for(auto it = inputs.begin();it != inputs.end(); ++it)
        (*it)->computeValue();
    
    // Then evaluate the function (if it exists)
    if(function != nullptr)
        function->evaluate();
}

void Variable::computeGradient() {
    // If already done, return
    if(computedGradient) return;
    
    // Mark as done
    computedGradient = true;
    
    // Initialize gradient with zeroes
    memset(gradient, 0, sizeof(scalar) * size);
    
    // The gradient is the sum of the contributions to the gradient through all dependents
    for(auto it = dependents.begin();it != dependents.end(); ++it) {
        (*it)->computeGradient();
        (*it)->getFunction()->backpropagate();
    }
}

void Variable::resetValue() {
    if(!computedValue) return;
    
    // Mark variable as unevaluated
    computedValue = false;
    
    // Mark all inputs as unevaluated
    for(auto it = inputs.begin();it != inputs.end(); ++it)
        (*it)->resetValue();
}

void Variable::resetGradient() {
    if(!computedGradient) return;
    
    // Mark variable as unevaluated gradient
    computedGradient = false;
    
    // Mark all dependents as unevaluated gradient
    for(auto it = dependents.begin();it != dependents.end(); ++it)
        (*it)->resetGradient();
}
