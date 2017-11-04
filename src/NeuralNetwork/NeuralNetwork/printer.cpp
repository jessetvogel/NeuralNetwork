#include "printer.hpp"

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