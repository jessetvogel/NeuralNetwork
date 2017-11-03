#include "sample.hpp"
#include <fstream>

Sample::Sample(dimension inputSize, dimension outputSize) : inputSize(inputSize), outputSize(outputSize) {
    input = new scalar[inputSize];
    output = new scalar[outputSize];
}

Sample::~Sample() {
    delete[] input;
    delete[] output;
}

bool Sample::save(std::string path) {
    std::ofstream out(path);
    if(out.fail()) {
        Log::print("Failed to open file");
        return false;
    }
    
    // Write 4 bytes to indicate the right file type
    out.write("NNTS", 4); // Neural Network Training Sample
    
    // Write dimension of input and output
    out.write((const char*) &inputSize, sizeof(inputSize));
    out.write((const char*) &outputSize, sizeof(outputSize));
    
    // Write data
    if(inputSize > 0) out.write((const char*) input, sizeof(scalar) * inputSize);
    if(outputSize > 0) out.write((const char*) output, sizeof(scalar) * outputSize);
    
    out.close();
    return true;
}

Sample* Sample::load(std::string path) {
    std::ifstream in(path);
    if(in.fail()) {
        Log::print("Failed to open file");
        return nullptr;
    }
    
    // Read 4 bytes
    char code[4];
    in.read(code, 4);
    
    if(std::string(code, 4).compare("NNTS") != 0) {
        Log::print("Invalid file");
        return nullptr;
    }
    
    // Read dimension of input and output
    dimension inputSize, outputSize;
    in.read((char*) &inputSize, sizeof(inputSize));
    in.read((char*) &outputSize, sizeof(outputSize));
    
    // Create new sample of given dimensions
    Sample* sample = new Sample(inputSize, outputSize);
    
    // Read data
    if(inputSize > 0) in.read((char*) sample->input, sizeof(scalar) * inputSize);
    if(outputSize > 0) in.read((char*) sample->output, sizeof(scalar) * outputSize);
    
    in.close();
    return sample;
}

Sample* Sample::duplicate() {
    // Create new sample, and copy input and output
    Sample* sample = new Sample(inputSize, outputSize);
    memcpy(sample->input, input, sizeof(scalar) * inputSize);
    memcpy(sample->output, output, sizeof(scalar) * outputSize);
    return sample;
}
