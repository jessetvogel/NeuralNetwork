#include "sigmoid.hpp"
#include <cmath>

Sigmoid::Sigmoid(Vector* a) : a(a) {}

Vector* Sigmoid::create(Vector* a) {
    // Create function object and vector, and return
    Sigmoid* sigmoid = new Sigmoid(a);
    return (sigmoid->result = new Vector(a->getSize(), sigmoid));
}

void Sigmoid::evaluate() {
    // Compute sigmoid elementwise
    scalar* valueResult = result->getValueAddr();
    scalar* valueA = a->getValueAddr();
    
    unsigned int n = a->getSize();
    for(unsigned int i = 0;i < n; ++i)
        *valueResult = f(*(valueA++));
}

scalar Sigmoid::f(scalar x) {
    return 1.0 / (1.0 + exp(-x));
}
