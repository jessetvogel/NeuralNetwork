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

void Printer::print(TrainingSet* set) {
    size_t S = set->getAmountOfSamples();
    OUTPUT_STREAM << "Amount of samples:      " << S << std::endl;
    OUTPUT_STREAM << "Bytes per input value:  " << (unsigned int) set->bytesPerInputValue << std::endl;
    OUTPUT_STREAM << "Bytes per output value: " << (unsigned int) set->bytesPerOutputValue << std::endl;
    OUTPUT_STREAM << "Input lower bound:      " << set->inputLowerBound << std::endl;
    OUTPUT_STREAM << "Input upper bound:      " << set->inputUpperBound << std::endl;
    OUTPUT_STREAM << "Output lower bound:     " << set->outputLowerBound << std::endl;
    OUTPUT_STREAM << "Output upper bound:     " << set->outputUpperBound << std::endl;
    OUTPUT_STREAM << "Sample input size:      " << set->sampleInputSize << std::endl;
    OUTPUT_STREAM << "Sample output size:     " << set->sampleOutputSize << std::endl << std::endl;
    
    if(S > 20) { S = 20; OUTPUT_STREAM << "(only printing 20 samples)" << std::endl; }
    
    for(int i = 0;i < S; ++i) {
        set->setCurrentSample(i);
        OUTPUT_STREAM << "input  #" << i << ": [ ";
        scalar* value = set->getCurrentSampleInput();
        for(dim i = 0;i < set->sampleInputSize; ++i) {
            OUTPUT_STREAM << *(value++); if(i < set->sampleInputSize - 1) OUTPUT_STREAM << ", ";
        }
        OUTPUT_STREAM << " ]" << std::endl;
    
        OUTPUT_STREAM << "output #" << i << ": [ ";
        value = set->getCurrentSampleOutput();
        for(dim i = 0;i < set->sampleOutputSize; ++i) {
            OUTPUT_STREAM << *(value++); if(i < set->sampleOutputSize - 1) OUTPUT_STREAM << ", ";
        }
        OUTPUT_STREAM << " ]" << std::endl << std::endl;
    }
}

//void Printer::print(Sample& sample) {
//    dim inputSize = sample.getInputSize();
//    dim outputSize = sample.getOutputSize();
//    scalar* input = sample.input;
//    scalar* output = sample.output;
//    OUTPUT_STREAM << "input size  = " << inputSize << std::endl;
//    OUTPUT_STREAM << "output size = " << outputSize << std::endl;
//    OUTPUT_STREAM << "input  = [ ";
//    for(dim i = 0;i < inputSize; ++i) {
//        OUTPUT_STREAM << (*(input++));
//        if(i < inputSize - 1) OUTPUT_STREAM << ", ";
//        
//    }
//    OUTPUT_STREAM << " ]" << std::endl;
//    OUTPUT_STREAM << "output = [ ";
//    for(dim i = 0;i < outputSize; ++i) {
//        OUTPUT_STREAM << (*(output++));
//        if(i < outputSize - 1) OUTPUT_STREAM << ", ";
//        
//    }
//    OUTPUT_STREAM << " ]" << std::endl << std::endl;
//}
