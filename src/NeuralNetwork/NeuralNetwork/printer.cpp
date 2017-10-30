#include "printer.hpp"
#include <iostream>

#define OUTPUT_STREAM std::cerr

void Printer::printScalar(Scalar* s) {
    scalar* value = s->getValueAddr();
    OUTPUT_STREAM << "[" << *value << "]" << std::endl << std::endl;
}

void Printer::printVector(Vector* v) {
    scalar* value = v->getValueAddr();
    dimension n = v->getSize();
    OUTPUT_STREAM << "[ ";
    for(dimension i = 0;i < n; ++i) {
        OUTPUT_STREAM << (*(value++));
        if(i < n - 1) OUTPUT_STREAM << ", ";
    }
    OUTPUT_STREAM << " ]" << std::endl << std::endl;
}

void Printer::printMatrix(Matrix* m) {
    scalar* value = m->getValueAddr();
    dimension rows = m->getRowSize();
    dimension columns = m->getColumnSize();
    for(dimension i = 0;i < rows; ++i) {
        OUTPUT_STREAM << "[ ";
        for(dimension j = 0;j < columns; ++j) {
            OUTPUT_STREAM << (*(value++));
            if(j < columns - 1) OUTPUT_STREAM << ", ";
        }
        OUTPUT_STREAM << " ]" << std::endl;
    }
    OUTPUT_STREAM << std::endl;
}

void Printer::printScalarGradient(Scalar* s) {
    scalar* gradient = s->getGradientAddr();
    OUTPUT_STREAM << "[" << *gradient << "]" << std::endl << std::endl;
}

void Printer::printVectorGradient(Vector* v) {
    scalar* gradient = v->getGradientAddr();
    dimension n = v->getSize();
    OUTPUT_STREAM << "[ ";
    for(dimension i = 0;i < n; ++i) {
        OUTPUT_STREAM << (*(gradient++));
        if(i < n - 1) OUTPUT_STREAM << ", ";
    }
    OUTPUT_STREAM << " ]" << std::endl << std::endl;
}

void Printer::printMatrixGradient(Matrix* m) {
    scalar* gradient = m->getGradientAddr();
    dimension rows = m->getRowSize();
    dimension columns = m->getColumnSize();
    for(dimension i = 0;i < rows; ++i) {
        OUTPUT_STREAM << "[ ";
        for(dimension j = 0;j < columns; ++j) {
            OUTPUT_STREAM << (*(gradient++));
            if(j < columns - 1) OUTPUT_STREAM << ", ";
        }
        OUTPUT_STREAM << " ]" << std::endl;
    }
    OUTPUT_STREAM << std::endl;
}

void Printer::printSample(Sample& sample) {
    dimension inputSize = sample.getInputSize();
    dimension outputSize = sample.getOutputSize();
    scalar* input = sample.input;
    scalar* output = sample.output;
    OUTPUT_STREAM << "input size  = " << inputSize << std::endl;
    OUTPUT_STREAM << "output size = " << outputSize << std::endl;
    OUTPUT_STREAM << "input  = [ ";
    for(dimension i = 0;i < inputSize; ++i) {
        OUTPUT_STREAM << (*(input++));
        if(i < inputSize - 1) OUTPUT_STREAM << ", ";
        
    }
    OUTPUT_STREAM << " ]" << std::endl;
    OUTPUT_STREAM << "output = [ ";
    for(dimension i = 0;i < outputSize; ++i) {
        OUTPUT_STREAM << (*(output++));
        if(i < outputSize - 1) OUTPUT_STREAM << ", ";
        
    }
    OUTPUT_STREAM << " ]" << std::endl << std::endl;
}