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

bool Sample::load(std::string path) {
    std::ifstream in(path);
    if(in.fail()) {
        Log::print("Failed to open file");
        return false;
    }
    
    // Read 4 bytes
    char code[4];
    in.read(code, 4);
    
    if(std::string(code, 4).compare("NNTS") != 0) {
        Log::print("Invalid file");
        return false;
    }
    
    // Read dimension of input and output
    in.read((char*) &inputSize, sizeof(inputSize));
    in.read((char*) &outputSize, sizeof(outputSize));
    
    // Read data
    if(inputSize > 0) in.read((char*) input, sizeof(scalar) * inputSize);
    if(outputSize > 0) in.read((char*) output, sizeof(scalar) * outputSize);
    
    in.close();
    return true;
}
