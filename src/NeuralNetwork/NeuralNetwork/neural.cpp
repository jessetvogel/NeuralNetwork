#include "neural.hpp"
#include "m.hpp"

Neural::~Neural() {
    delete trainOutput;
    delete error;
}

void Neural::feed(scalar* values) {
    // Copy values to input
    memcpy(input->getValueAddr(), values, sizeof(scalar) * input->getSize());
    
    // Mark all variables as unevaluated
    output->resetValue();
    
    // Compute output
    output->computeValue();
}

void Neural::train(Sample& sample) {
    // Feed input to network
    feed(sample.input);
    
    // Compute error
    error->computeValue();
    
    // Reset the gradients of all parameters
    for(auto it = parameters.begin();it != parameters.end(); ++it)
        (*it)->resetGradient();
    
    // Set gradient of error to 1
    error->computeGradient();
    *(error->getGradientAddr()) = 1.0;

    // Compute the gradient for all parameters, and determine the norm of the gradient
    scalar gradientNorm = 0.0;
    for(auto it = parameters.begin();it != parameters.end(); ++it) {
        Variable* variable = *it;
        variable->computeGradient();
        scalar* gradient = variable->getGradientAddr();
        unsigned int n = variable->getSize();
        for(unsigned int i = 0;i < n; ++i) {
            gradientNorm += (*gradient) * (*gradient);
            ++ gradient;
        }
    }
    
    // Update the parameters
    scalar alphaOverGradientNorm = learningRate / gradientNorm;
    for(auto it = parameters.begin();it != parameters.end(); ++it) {
        Variable* variable = *it;
        scalar* value = variable->getValueAddr();
        scalar* gradient = variable->getGradientAddr();
        unsigned int n = variable->getSize();
        for(unsigned int i = 0;i < n; ++i) {
            *(value++) = (*(gradient++)) * alphaOverGradientNorm;
        }
    }
}
