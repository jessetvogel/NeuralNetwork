#include "vector.hpp"

Vector::Vector(dimension size, Function* function) : Variable(size, function) {
    if(function != nullptr)
        function->setResult(this);
}
