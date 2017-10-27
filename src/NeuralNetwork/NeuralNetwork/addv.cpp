#include "addv.hpp"

AddV::AddV(Vector* a, Vector* b) : a(a), b(b) {}

Vector* AddV::create(Vector* a, Vector* b) {
    // Make sure sizes of the vectors are equal
    if(a->getSize() != b->getSize()) {
        Log::print("Vectors are incompatible");
        return nullptr;
    }
    
    // Create function object and vector, and return
    AddV* addV = new AddV(a, b);
    return (addV->result = new Vector(a->getSize(), addV));
}

void AddV::evaluate() {
    // Evaluate inputs
    a->computeValue();
    b->computeValue();

    // Compute sum elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    scalar* valueB = b->getValueAddr();

    unsigned int n = a->getSize();
    for(unsigned int i = 0;i < n; ++i)
        *(valueResult++) = (*(valueA++)) + (*(valueB++));
}

void AddV::backpropagate() {
    // Compute gradient
    unsigned int n = sizeof(scalar) * a->getSize();
    memcpy(a->getGradientAddr(), result->getGradientAddr(), n);
    memcpy(b->getGradientAddr(), result->getGradientAddr(), n);
    
    // Backpropagate
    a->computeGradient();
    b->computeGradient();
}
