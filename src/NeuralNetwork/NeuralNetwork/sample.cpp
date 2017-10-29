#include "sample.hpp"

Sample::Sample(unsigned int inputSize, unsigned int outputSize) : inputSize(inputSize), outputSize(outputSize) {
    input = new scalar[inputSize];
    output = new scalar[outputSize];
}

Sample::~Sample() {
    delete[] input;
    delete[] output;
}
