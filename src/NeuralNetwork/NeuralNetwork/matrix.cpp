#include "matrix.hpp"

Matrix::Matrix(dimension rowSize, dimension columnSize, Function* function) : rowSize(rowSize), columnSize(columnSize), Variable(rowSize * columnSize, function) {
    if(function != nullptr)
        function->setResult(this);
}
