#include "subtractv.hpp"

SubtractV::SubtractV(Vector* a, Vector* b) : a(a), b(b) {}

Vector* SubtractV::create(Vector* a, Vector* b) {
    // Make sure sizes of the vectors are equal
    if(a->getSize() != b->getSize()) {
        Log::print("Vectors are incompatible");
        return nullptr;
    }
    
    // Create function object and vector, and return
    SubtractV* subtractV = new SubtractV(a, b);
    return (subtractV->result = new Vector(a->getSize(), subtractV));
}

void SubtractV::evaluate() {
    // Evaluate inputs
    a->computeValue();
    b->computeValue();

    // Compute difference elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    unsigned int n = a->getSize();
    for(unsigned int i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) - (*(valueB++));
}

void SubtractV::backpropagate() {
    // Compute gradients
    unsigned int n = sizeof(scalar) * a->getSize();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    scalar* gradientResult = result->getGradientAddr();
    
    for(unsigned int i = 0;i < n; ++i)
        *(gradientB++) = - (*(gradientA++) = *(gradientResult++));
    
    // Backpropagate
    a->computeGradient();
    b->computeGradient();
}

