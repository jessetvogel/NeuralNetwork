#include "vector.hpp"

Vector::Vector(unsigned int size, Function* function) : size(size), Variable(size, function) {
    function->setResult(this);
}
