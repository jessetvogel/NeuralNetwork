#include "printer.hpp"
#include <iostream>

void Printer::print(std::string message) {
    OUTPUT_STREAM << message << std::endl;
}

template <>
void Printer::print(Tensor<0>* tensor, scalar* value) {
    OUTPUT_STREAM << "[" << *value << "]" << std::endl << std::endl;
}

template <>
void Printer::print(Tensor<1>* tensor, scalar* value) {
    dim n = tensor->getDimension(MATRIX_ROWS);
    OUTPUT_STREAM << "[ ";
    for(dim i = 0;i < n; ++i) {
        OUTPUT_STREAM << (*(value++));
        if(i < n - 1) OUTPUT_STREAM << ", ";
    }
    OUTPUT_STREAM << " ]" << std::endl << std::endl;
}

template <>
void Printer::print(Tensor<2>* tensor, scalar* value) {
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

template <>
void Printer::print(Tensor<3>* tensor, scalar* value) {
    dim width = tensor->getDimension(VOLUME_WIDTH);
    dim height = tensor->getDimension(VOLUME_HEIGHT);
    dim depth = tensor->getDimension(VOLUME_DEPTH);
    
    for(dim h = 0;h < height; ++h) {
        for(dim d = 0;d < depth; ++d) {
            OUTPUT_STREAM << "[ ";
            for(dim w = 0;w < width; ++w) {
                OUTPUT_STREAM << value[d + depth * (h + height * w)];
                if(w < width - 1) OUTPUT_STREAM << ", ";
            }
            OUTPUT_STREAM << " ] ";
        }
        OUTPUT_STREAM << std::endl;
    }
    OUTPUT_STREAM << std::endl;
}

template <>
void Printer::print(Tensor<4>* tensor, scalar* value) {
    dim width = tensor->getDimension(FILTERSET_WIDTH);
    dim height = tensor->getDimension(FILTERSET_HEIGHT);
    dim depth = tensor->getDimension(FILTERSET_DEPTH);
    dim amount = tensor->getDimension(FILTERSET_AMOUNT);
    for(dim a = 0;a < amount; ++ a) {
        for(dim h = 0;h < height; ++h) {
            for(dim d = 0;d < depth; ++d) {
                OUTPUT_STREAM << "[ ";
                for(dim w = 0;w < width; ++w) {
                    OUTPUT_STREAM << value[a + amount * (d + depth * (h + height * w))];
                    if(w < width - 1) OUTPUT_STREAM << ", ";
                }
                OUTPUT_STREAM << " ] ";
            }
            OUTPUT_STREAM << std::endl;
        }
        OUTPUT_STREAM << std::endl;
    }
}

void Printer::print(Sample& sample) {
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
