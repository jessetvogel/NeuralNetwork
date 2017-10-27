#include "adds.hpp"

AddS::AddS(Scalar* a, Scalar* b) : a(a), b(b) {}

Scalar* AddS::create(Scalar* a, Scalar* b) {
    // Create function object and scalar, and return
    AddS* addS = new AddS(a, b);
    return (addS->result = new Scalar(addS));
}

void AddS::evaluate() {
    // Evaluate inputs
    a->computeValue();
    b->computeValue();

    // Compute sum
    *(result->getValueAddr()) = (*(a->getValueAddr())) + (*(b->getValueAddr()));
}

void AddS::backpropagate() {
    // Compute gradient
    *(a->getGradientAddr()) = *(b->getGradientAddr()) = *(result->getGradientAddr());
    
    // Backpropagate
    a->computeGradient();
    b->computeGradient();
}
