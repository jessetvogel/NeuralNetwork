#include "dotvv.hpp"

DotVV::DotVV(Vector* a, Vector* b) : a(a), b(b) {}

Scalar* DotVV::create(Vector* a, Vector* b) {
    // Make sure sizes of the vectors are equal
    if(a->getSize() != b->getSize()) {
        Log::print("Vectors are incompatible");
        return nullptr;
    }
    
    // Create function object and scalar, and return
    DotVV* dotVV = new DotVV(a, b);
    return (dotVV->result = new Scalar(dotVV));
}

void DotVV::evaluate() {
    // Computes inner product between vectors a and b
    scalar value = 0.0;
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    
    unsigned int n = a->getSize();
    for(unsigned int i = 0;i < n; ++i)
        value += (*(valueA++)) * (*(valueB++));
    
    // Store result
    *(result->getValueAddr()) = value;
}

void DotVV::backpropagate() {
    // Determine gradient of result
    result->computeGradient();
    
    // Compute new gradients
    scalar gradientResult = *(result->getGradientAddr());
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();
    scalar* gradientA = a->getGradientAddr();
    scalar* gradientB = b->getGradientAddr();
    
    unsigned int n = a->getSize();
    for(unsigned int i = 0;i < n; ++i) {
        *(gradientA++) = gradientResult * (*(valueB++));
        *(gradientB++) = gradientResult * (*(valueA++));
    }
}
