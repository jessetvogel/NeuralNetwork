#include "printer.hpp"
#include <iostream>

#define OUTPUT_STREAM std::cerr

void Printer::printScalar(Scalar* s) {
    scalar* value = s->getValueAddr();
    OUTPUT_STREAM << "[" << *value << "]" << std::endl;
}

void Printer::printVector(Vector* v) {
    scalar* value = v->getValueAddr();
    unsigned int n = v->getSize();
    OUTPUT_STREAM << "[ ";
    for(unsigned int i = 0;i < n; ++i) {
        OUTPUT_STREAM << (*(value++));
        if(i < n - 1) OUTPUT_STREAM << ", ";
    }
    OUTPUT_STREAM << " ]" << std::endl;
}

void Printer::printMatrix(Matrix* m) {
    scalar* value = m->getValueAddr();
    unsigned int rows = m->getRowSize();
    unsigned int columns = m->getColumnSize();
    for(unsigned int i = 0;i < rows; ++i) {
        OUTPUT_STREAM << "[ ";
        for(unsigned int j = 0;j < columns; ++j) {
            OUTPUT_STREAM << (*(value++));
            if(j < columns - 1) OUTPUT_STREAM << ", ";
        }
        OUTPUT_STREAM << " ]" << std::endl;
    }
}
