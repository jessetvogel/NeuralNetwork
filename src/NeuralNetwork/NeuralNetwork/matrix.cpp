#include "matrix.hpp"

Matrix::Matrix(unsigned int rowSize, unsigned int columnSize, Function* function) : rowSize(rowSize), columnSize(columnSize), Variable(rowSize * columnSize, function) {
    if(function != nullptr)
        function->setResult(this);
}
