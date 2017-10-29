#include "scalar.hpp"

Scalar::Scalar(Function* function) : Variable(1, function) {
    function->setResult(this);
}

void Scalar::findGradients() {
    // Set gradient to 1.0
    *gradient = 1.0;
    
    // Backpropagate
    computeGradient();
}
