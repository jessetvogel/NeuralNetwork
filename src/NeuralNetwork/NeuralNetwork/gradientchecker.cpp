#include "gradientchecker.hpp"
#include <cmath>

void GradientChecker::check(Network& network, Sample& sample) {
    // Compute initial error
    network.feed(sample);
    scalar initialError = network.getError();
    
    // Reset gradient of all variables
    std::vector<Variable*>* variables = network.getVariables();
    for(auto it = variables->begin();it != variables->end(); ++it)
        (*it)->resetGradient();
    
    // Set gradient of error to one
    network.error->computeGradient();
    *(network.error->getGradientAddr()) = 1.0;
    
    // Compute the gradient of all parameters through backpropagation
    std::vector<Variable*>* parameters = network.getParameters();
    for(auto it = parameters->begin();it != parameters->end(); ++it)
        (*it)->computeGradient();
    
    // Check gradients
    bool foundError = false;
    scalar h = 0.000001;
    for(auto it = parameters->begin();it != parameters->end(); ++it) {
        Variable* v = *it;
        scalar* value = v->getValueAddr();
        scalar* gradient = v->getGradientAddr();
        dim n = v->getSize();
        for(dim i = 0;i < n; ++i) {
            *value += h;
            network.feed(sample);
            scalar adjustedError = network.getError();
            scalar gradientByTrial = (adjustedError - initialError) / h;
            *value -= h;
            if(std::abs(gradientByTrial - *gradient) > 0.0001) {
                Log::print("Invalid gradient found! Computed was '" + std::to_string(*gradient) + "', but by trial gives '" + std::to_string(gradientByTrial) + "'");
                foundError = true;
            }
            value ++;
            gradient ++;
        }
    }
    
    if(!foundError)
        Log::print("No gradient errors found");
}
