#include "vector.hpp"

Vector::Vector(unsigned int size, Function* function) : size(size), function(function) {
    value = new scalar[size];
    gradient = new scalar[size];
}

Vector::~Vector() {
    delete function;
    delete[] value;
    delete[] gradient;
}
