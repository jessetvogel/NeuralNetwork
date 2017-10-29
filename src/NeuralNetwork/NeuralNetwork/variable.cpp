#include "variable.hpp"

Variable::Variable(unsigned int n, Function* function) : n(n), function(function) {
    value = new scalar[n];
    gradient = new scalar[n];
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
    
    // Then evaluate the function
    function->evaluate();
}

void Variable::computeGradient() {
    // If already done, return
    if(computedGradient) return;
    
    // Mark as done
    computedGradient = true;
    
    // Initialize gradient with zeroes
    memset(gradient, 0, sizeof(scalar) * n);
    
    // The gradient is the sum of the contributions to the gradient through all dependents
    for(auto it = dependents.begin();it != dependents.end(); ++it) {
        (*it)->computeGradient();
        (*it)->getFunction()->backpropagate();
    }
}
