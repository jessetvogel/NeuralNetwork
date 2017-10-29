#include "scalar.hpp"

Scalar::Scalar(Function* function) : Variable(1, function) {
    if(function != nullptr)
        function->setResult(this);
}
