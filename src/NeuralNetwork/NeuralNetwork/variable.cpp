#include "variable.hpp"
#include <chrono>

std::default_random_engine Variable::randomGenerator((unsigned) (std::chrono::system_clock::now().time_since_epoch().count())); // Use time-based seed

Variable::Variable(Function* function) : function(function) {
    if(function != nullptr)
        function->setResult(this);
    
    // Default values
    computedValue = false;
    computedGradient = false;
}

Variable::~Variable() {
    delete function;
    delete[] value;
    delete[] gradient;
}

void Variable::initializeValues(scalar stddev) {
    std::normal_distribution<scalar> distribution(0.0, stddev);
    
    scalar* ptr = value;
    for(dim i = 0;i < size; ++i)
        *(ptr++) = distribution(randomGenerator);
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
        (*it)->function->backpropagate();
    }
}
