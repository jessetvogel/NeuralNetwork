#include "network.hpp"
#include "printer.hpp"

Network::Network() {
    // Create a builder
    builder = new Builder(this);
    
    // Set input, training output vector and error variable to null
    input = nullptr;
    trainOutput = nullptr;
    error = nullptr;
    
    // Set default parameters
    learningRate = 0.5;
    errorType = QUADRATIC;
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
    // Create a new trainOutput if necessary
    if(trainOutput == nullptr || output->getSize() != trainOutput->getSize()) {
        if(trainOutput != nullptr) deleteVariable(trainOutput);
        trainOutput = builder->vector(output->getSize());
    }
    
    // Set the output variable
    this->output = output;
    
    // Update error
    updateError();
}

void Network::updateError() {
    // Delete error if it exists
    if(error != nullptr) deleteVariable(error);
    
    // Create new error function (depending on type)
    switch(errorType) {
        case QUADRATIC:         error = builder->errorQuadratic(trainOutput, output); break;
        case CROSS_ENTROPY:     error = builder->errorCrossEntropy(trainOutput, output); break;
    }
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
    // Make sure training output is set
    if(trainOutput == nullptr) {
        Log::print("No output variable was provided");
        return false;
    }
    
    // Make sure size of sample matches this network
    if(trainOutput != nullptr && sample.getOutputSize() != trainOutput->getSize()) { // TODO: also check input size
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
    
    // Make sure there are parameters
    if(parameters.size() == 0) {
        Log::print("Note that there are no parameters to optimize");
        return true;
    }
    
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
//        Log::print("Hooray, we reached a local minimum exactly!"); // TODO: remove this
        return true;
    }
    
    // Update the parameters (gradient descent)
    scalar alphaOverGradientNorm = learningRate * getError() / gradientNorm;
    for(auto it = parameters.begin();it != parameters.end(); ++it) {
        Variable* variable = *it;
        scalar* value = variable->getValueAddr();
        scalar* gradient = variable->getGradientAddr();
        dimension n = variable->getSize();
        for(dimension i = 0;i < n; ++i)
            *(value++) -= (*(gradient++)) * alphaOverGradientNorm;
    }
    
    return true;
}

void Network::deleteVariable(Variable* variable) {
    for(auto it = variables.begin();it != variables.end(); ++it) {
        if((*it) == variable) {
            variables.erase(it);
            break;
        }
    }
    delete variable;
}
