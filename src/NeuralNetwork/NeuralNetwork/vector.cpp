#include "vector.hpp"

Vector::Vector(unsigned int size, Function* function) : Variable(size, function) {
    if(function != nullptr)
        function->setResult(this);
}
