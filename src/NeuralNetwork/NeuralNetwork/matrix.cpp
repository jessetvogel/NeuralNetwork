#include "matrix.hpp"

Matrix::Matrix(unsigned int rowSize, unsigned int columnSize, Function* function) : rowSize(rowSize), columnSize(columnSize), function(function) {
    value = new scalar[rowSize * columnSize];
    gradient = new scalar[rowSize * columnSize];
}

Matrix::~Matrix() {
    delete function;
    delete[] value;
    delete[] gradient;
}
