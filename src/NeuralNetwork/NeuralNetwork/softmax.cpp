#include "softmax.hpp"
#include <cmath>

Vector* Softmax::create(Vector* a) {
    // Create function object and vector, and return
    Softmax* softmax = new Softmax(a);
    return new Vector(a->getSize(), softmax);
}

void Softmax::setResult(Variable* variable) {
    result = variable;
    result->addChild(a);
}

void Softmax::evaluate() {
    // TODO
}

void Softmax::backpropagate() {
    // TODO
}
