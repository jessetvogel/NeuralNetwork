#include "subtracts.hpp"

SubtractS::SubtractS(Scalar* a, Scalar* b) : a(a), b(b) {}

Scalar* SubtractS::create(Scalar* a, Scalar* b) {
    // Create function object and scalar, and return
    SubtractS* subtractS = new SubtractS(a, b);
    return (subtractS->result = new Scalar(subtractS));
}

void SubtractS::evaluate() {
    // Evaluate inputs
    a->computeValue();
    b->computeValue();

    // Compute sum
    *(result->getValueAddr()) = (*(a->getValueAddr())) - (*(b->getValueAddr()));
}

void SubtractS::backpropagate() {
    // Compute gradients
    *(b->getGradientAddr()) = - (*(a->getGradientAddr()) = *(result->getGradientAddr()));
    
    // Backpropagate
    a->computeGradient();
    b->computeGradient();
}
