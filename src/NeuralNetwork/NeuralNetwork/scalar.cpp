#include "scalar.hpp"

Scalar::Scalar(Function* function) : function(function) {
    computedValue = false;
    computedGradient = false;
}

Scalar::~Scalar() {
    delete function;
}

void Scalar::findGradients() {
    // Set gradient to 1.0
    gradient = 1.0;
    
    // Backpropagate
    function->backpropagate();
}
