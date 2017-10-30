#include "network.hpp"

Network::Network(dimension outputSize) {
    // Create a builder
    builder = new Builder(this);
    
    // Create training output vector
    trainOutput = builder->vector(outputSize);
    
    // Set error variable to null
    error = nullptr;
    
    // Set default learning rate
    learningRate = 0.5;
}

Network::~Network() {
    // Delete all variables connected to this network
    for(auto it = variables.begin();it != variables.end(); ++it)
        delete *it;
    
    // Delete builder
    delete builder;
}

void Network::setInput(Variable* input) {
    // Set the input variable
    this->input = input;
}

void Network::setOutput(Variable* output) {
    // Make sure the variable has the correct size
    if(output->getSize() != trainOutput->getSize()) {
        Log::print("Variable does not have the correct size");
        return;
    }
    
    // Set the output variable
    this->output = output;

    // Delete error and remove it from the list of variables (if it exists)
    if(error != nullptr) {
        for(auto it = variables.begin();it != variables.end(); ++it) {
            if((*it) == error) {
                variables.erase(it);
                break;
            }
        }
        delete error;
    }
    
    // Create new error function
    error = builder->errorQuadratic(trainOutput, output);
}

bool Network::feed(scalar* values) {
    // Make sure some output variable has been provided
    if(output == nullptr) {
        Log::print("No output variable was provided");
        return false;
    }
    
    // Copy values to input (if it exists)
    if(input != nullptr)
        memcpy(input->getValueAddr(), values, sizeof(scalar) * input->getSize());
    
    // Mark all variables as unevaluated
    for(auto it = variables.begin();it != variables.end(); ++it)
        (*it)->resetValue();
    
    // Compute output
    output->computeValue();
    return true;
}

bool Network::feed(Sample& sample) {
    // Make sure size of sample matches this network
    if(sample.getOutputSize() != trainOutput->getSize()) { // TODO: also check input size
        Log::print("Sample has incorrect size");
        return false;
    }
    
    // Feed input to network
    if(!feed(sample.input)) return false;
    
    // Set training output
    memcpy(trainOutput->getValueAddr(), sample.output, sizeof(scalar) * trainOutput->getSize());
    
    // Compute error
    error->computeValue();
    return true;
}

bool Network::train(Sample& sample) {
    // Feed sample to network
    if(!feed(sample)) return false;
    
    // Reset the gradients of all variables
    for(auto it = variables.begin();it != variables.end(); ++it)
        (*it)->resetGradient();
    
    // Set gradient of error to 1.0
    error->computeGradient();
    *(error->getGradientAddr()) = 1.0;

    // Compute the gradient for all parameters, and determine the norm of the gradient
    scalar gradientNorm = 0.0;
    for(auto it = parameters.begin();it != parameters.end(); ++it) {
        Variable* variable = *it;
        variable->computeGradient();
        scalar* gradient = variable->getGradientAddr();
        dimension n = variable->getSize();
        for(dimension i = 0;i < n; ++i) {
            gradientNorm += (*gradient) * (*gradient);
            ++ gradient;
        }
    }
    
    // In practice unnecessary, but just to be sure
    if(gradientNorm <= 0.0) {
        // We are exactly at a local minimum, no need to update the parameters
        Log::print("Hooray, we reached a local minimum exactly!"); // TODO: remove this
        return true;
    }
    
    // Update the parameters
    scalar alphaOverGradientNorm = learningRate * getError() / gradientNorm;
    for(auto it = parameters.begin();it != parameters.end(); ++it) {
        Variable* variable = *it;
        scalar* value = variable->getValueAddr();
        scalar* gradient = variable->getGradientAddr();
        dimension n = variable->getSize();
        for(dimension i = 0;i < n; ++i) {
            *(value++) += (*(gradient++)) * alphaOverGradientNorm;
        }
    }
    
    return true;
}
