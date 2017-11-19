#include "trainingset.hpp"
#include <dirent.h>
#include <fstream>

TrainingSet::TrainingSet(uint8_t bpiv, uint8_t bpov,
            double ilb, double iub, double olb, double oub,
            uint32_t sis, uint32_t sos) :
                                            bytesPerInputValue(bpiv), bytesPerOutputValue(bpov),
                                            inputLowerBound(ilb), inputUpperBound(iub), outputLowerBound(olb), outputUpperBound(oub),
                                            sampleInputSize(sis), sampleOutputSize(sos) {
    currentSampleInput = new scalar[sampleInputSize];
    currentSampleOutput = new scalar[sampleOutputSize];
};

TrainingSet::~TrainingSet() {
    // Delete all samples
    for(auto it = samples.begin();it != samples.end(); ++it)
        delete[] *it;
    
    // Delete arrays
    delete[] currentSampleInput;
    delete[] currentSampleOutput;
}

bool TrainingSet::train(Network& network) {
    // Go through all samples
    for(auto it = samples.begin();it != samples.end(); ++it) {
        // Train the network in it
        setCurrentSample(*it);
        if(!network.train(currentSampleInput, currentSampleOutput)) return false;
    }
    return true;
}

bool TrainingSet::store(std::string path) {
    // Try to open file for output
    std::ofstream out(path);
    if(out.fail()) {
        Log::print("Failed to open file");
        return false;
    }
    
    // Write signature (Neural Network Training Set)
    out.write("NNTS", 4);
    
    // Write the amount of samples
    uint32_t S = (uint32_t) getAmountOfSamples();
    out.write((const char*) &S, 4);
    
    // Write amount of bytes per input / output value
    out.write((const char*) &bytesPerInputValue, 1);
    out.write((const char*) &bytesPerOutputValue, 1);
    
    // Write input / output lower / upper bounds
    out.write((const char*) &inputLowerBound, 8);
    out.write((const char*) &inputUpperBound, 8);
    out.write((const char*) &outputLowerBound, 8);
    out.write((const char*) &outputUpperBound, 8);
    
    // Write sample input / output size
    out.write((const char*) &sampleInputSize, 4);
    out.write((const char*) &sampleOutputSize, 4);
    
    // Write samples
    size_t ss = sampleSize();
    for(auto it = samples.begin();it != samples.end(); ++it)
        out.write((const char*) *it, ss);
    
    out.close();
    return true;
}

TrainingSet* TrainingSet::load(std::string path) {
    // Try to open file for reading
    std::ifstream in(path);
    if(in.fail()) {
        Log::print("Failed to open file");
        return nullptr;
    }
    
    // Read signature
    char signature[4];
    in.read(signature, 4);
    if(std::string(signature, 4).compare("NNTS") != 0) {
        Log::print("Invalid file");
        return nullptr;
    }
    
    // Read amount of samples
    uint32_t amountOfSamples;
    in.read((char*) &amountOfSamples, 4);
    
    // Read amount of bytes per input / output value
    unsigned char bytesPerInputValue, bytesPerOutputValue;
    in.read((char*) &bytesPerInputValue, 1);
    in.read((char*) &bytesPerOutputValue, 1);
    
    if((bytesPerInputValue != 1 && bytesPerInputValue != 2 && bytesPerInputValue != 4) ||
        (bytesPerOutputValue != 1 && bytesPerOutputValue != 2 && bytesPerOutputValue != 4)) {
        Log::print("Bytes per value can only be 1, 2, or 4");
        return nullptr;
    }
    
    // Read input / output lower / upper bounds
    double inputLowerBound, inputUpperBound;
    double outputLowerBound, outputUpperBound;
    in.read((char*) &inputLowerBound, 8);
    in.read((char*) &inputUpperBound, 8);
    in.read((char*) &outputLowerBound, 8);
    in.read((char*) &outputUpperBound, 8);
    
    // Read sample input / output size
    uint32_t sampleInputSize, sampleOutputSize;
    in.read((char*) &sampleInputSize, 4);
    in.read((char*) &sampleOutputSize, 4);
    
    // TODO: check if values are valid?
    
    // Create instance of training set
    TrainingSet* trainingSet = new TrainingSet(
        bytesPerInputValue, bytesPerOutputValue,
        inputLowerBound, inputUpperBound, outputLowerBound, outputUpperBound,
        sampleInputSize, sampleOutputSize
    );
    
    // Read samples
    size_t ss = trainingSet->sampleSize();
    for(size_t i = 0;i < amountOfSamples; ++i) {
        uint8_t* sample = new uint8_t[ss];
        in.read((char*) sample, ss);
        trainingSet->samples.push_back(sample);
    }
    
    // Close and return
    in.close();
    return trainingSet;
}

void TrainingSet::addSample(scalar* inputValues, scalar* outputValues) {
    uint8_t* sample = new uint8_t[sampleSize()];
    samples.push_back(sample);
    
    switch(bytesPerInputValue) {
        case 1: for(uint32_t i = 0;i < sampleInputSize; ++i) *(sample++) = toInputValue1(*(inputValues++)); break;
        case 2: for(uint32_t i = 0;i < sampleInputSize; ++i) { *((uint16_t*) sample) = toInputValue2(*(inputValues++)); sample += 2; } break;
        case 4: for(uint32_t i = 0;i < sampleInputSize; ++i) { *((uint16_t*) sample) = toInputValue4(*(inputValues++)); sample += 4; } break;
    }
    
    switch(bytesPerOutputValue) {
        case 1: for(uint32_t i = 0;i < sampleOutputSize; ++i) *(sample++) = toOutputValue1(*(outputValues++)); break;
        case 2: for(uint32_t i = 0;i < sampleOutputSize; ++i) { *((uint16_t*) sample) = toOutputValue2(*(outputValues++)); sample += 2; } break;
        case 4: for(uint32_t i = 0;i < sampleOutputSize; ++i) { *((uint16_t*) sample) = toOutputValue4(*(outputValues++)); sample += 4; } break;
    }
}

void TrainingSet::setCurrentSample(uint8_t* sample) {
    // Set input
    switch(bytesPerInputValue) {
        case 1: for(uint32_t i = 0;i < sampleInputSize; ++i) currentSampleInput[i] = toInputScalar1(sample++); break;
        case 2: for(uint32_t i = 0;i < sampleInputSize; ++i) { currentSampleInput[i] = toInputScalar2((uint16_t*) sample); sample += 2; } break;
        case 4: for(uint32_t i = 0;i < sampleInputSize; ++i) { currentSampleInput[i] = toInputScalar4((uint32_t*) sample); sample += 4; } break;
    }
    
    // Set output
    switch(bytesPerOutputValue) {
        case 1: for(uint32_t i = 0;i < sampleOutputSize; ++i) currentSampleOutput[i] = toOutputScalar1(sample++); break;
        case 2: for(uint32_t i = 0;i < sampleOutputSize; ++i) { currentSampleOutput[i] = toOutputScalar2((uint16_t*) sample); sample += 2; } break;
        case 4: for(uint32_t i = 0;i < sampleOutputSize; ++i) { currentSampleOutput[i] = toOutputScalar4((uint32_t*) sample); sample += 4; } break;
    }
}

// Conversion functions
scalar TrainingSet::toInputScalar1(uint8_t* ptr) { return inputLowerBound + ((double) *ptr) * (inputUpperBound - inputLowerBound) / UINT8_MAX; }
scalar TrainingSet::toInputScalar2(uint16_t* ptr) { return inputLowerBound + ((double) *ptr) * (inputUpperBound - inputLowerBound) / UINT16_MAX; }
scalar TrainingSet::toInputScalar4(uint32_t* ptr) { return inputLowerBound + ((double) *ptr) * (inputUpperBound - inputLowerBound) / UINT32_MAX; }

uint8_t TrainingSet::toInputValue1(scalar s) { return UINT8_MAX * (s - inputLowerBound) / (inputUpperBound - inputLowerBound); }
uint16_t TrainingSet::toInputValue2(scalar s) { return UINT16_MAX * (s - inputLowerBound) / (inputUpperBound - inputLowerBound); }
uint32_t TrainingSet::toInputValue4(scalar s) { return UINT32_MAX * (s - inputLowerBound) / (inputUpperBound - inputLowerBound); }

scalar TrainingSet::toOutputScalar1(uint8_t* ptr) { return outputLowerBound + ((double) *ptr) * (outputUpperBound - outputLowerBound) / UINT8_MAX; }
scalar TrainingSet::toOutputScalar2(uint16_t* ptr) { return outputLowerBound + ((double) *ptr) * (outputUpperBound - outputLowerBound) / UINT16_MAX; }
scalar TrainingSet::toOutputScalar4(uint32_t* ptr) { return outputLowerBound + ((double) *ptr) * (outputUpperBound - outputLowerBound) / UINT32_MAX; }

uint8_t TrainingSet::toOutputValue1(scalar s) { return UINT8_MAX * (s - outputLowerBound) / (outputUpperBound - outputLowerBound); }
uint16_t TrainingSet::toOutputValue2(scalar s) { return UINT16_MAX * (s - outputLowerBound) / (outputUpperBound - outputLowerBound); }
uint32_t TrainingSet::toOutputValue4(scalar s) { return UINT32_MAX * (s - outputLowerBound) / (outputUpperBound - outputLowerBound); }
