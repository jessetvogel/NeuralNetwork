#include "printer.hpp"
#include <iostream>

template <>
void Printer::print(Tensor<0>* tensor) {
    scalar* value = tensor->getValueAddr();
    OUTPUT_STREAM << "[" << *value << "]" << std::endl << std::endl;
}

template <>
void Printer::print(Tensor<1>* tensor) {
    scalar* value = tensor->getValueAddr();
    dim n = tensor->getDimension(MATRIX_ROWS);
    OUTPUT_STREAM << "[ ";
    for(dim i = 0;i < n; ++i) {
        OUTPUT_STREAM << (*(value++));
        if(i < n - 1) OUTPUT_STREAM << ", ";
    }
    OUTPUT_STREAM << " ]" << std::endl << std::endl;
}

template <>
void Printer::print(Tensor<2>* tensor) {
    scalar* value = tensor->getValueAddr();
    dim rows = tensor->getDimension(MATRIX_ROWS);
    dim columns = tensor->getDimension(MATRIX_COLUMNS);
    for(dim i = 0;i < rows; ++i) {
        OUTPUT_STREAM << "[ ";
        for(dim j = 0;j < columns; ++j) {
            OUTPUT_STREAM << (*(value++));
            if(j < columns - 1) OUTPUT_STREAM << ", ";
        }
        OUTPUT_STREAM << " ]" << std::endl;
    }
    OUTPUT_STREAM << std::endl;
}

void Printer::printSample(Sample& sample) {
    dim inputSize = sample.getInputSize();
    dim outputSize = sample.getOutputSize();
    scalar* input = sample.input;
    scalar* output = sample.output;
    OUTPUT_STREAM << "input size  = " << inputSize << std::endl;
    OUTPUT_STREAM << "output size = " << outputSize << std::endl;
    OUTPUT_STREAM << "input  = [ ";
    for(dim i = 0;i < inputSize; ++i) {
        OUTPUT_STREAM << (*(input++));
        if(i < inputSize - 1) OUTPUT_STREAM << ", ";
        
    }
    OUTPUT_STREAM << " ]" << std::endl;
    OUTPUT_STREAM << "output = [ ";
    for(dim i = 0;i < outputSize; ++i) {
        OUTPUT_STREAM << (*(output++));
        if(i < outputSize - 1) OUTPUT_STREAM << ", ";
        
    }
    OUTPUT_STREAM << " ]" << std::endl << std::endl;
}