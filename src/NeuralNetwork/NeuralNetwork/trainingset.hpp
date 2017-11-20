#ifndef trainer_hpp
#define trainer_hpp

#include "network.hpp"
#include <vector>
#include <string>

class TrainingSet {
    
public:
    
    const uint8_t bytesPerInputValue;
    const uint8_t bytesPerOutputValue;
    const double inputLowerBound, inputUpperBound;
    const double outputLowerBound, outputUpperBound;
    const uint32_t sampleInputSize;
    const uint32_t sampleOutputSize;

private:

    std::vector<uint8_t*> samples;
    
    scalar* currentSampleInput;
    scalar* currentSampleOutput;
    
    inline size_t sampleSize() { return bytesPerInputValue * sampleInputSize + bytesPerOutputValue * sampleOutputSize; }
    
public:
    
    TrainingSet(uint8_t, uint8_t, double, double, double, double, uint32_t, uint32_t);
    ~TrainingSet();
    
    inline size_t getAmountOfSamples() { return samples.size(); }
    
    void addSample(scalar*, scalar*);
    void setCurrentSample(uint8_t*);
    inline void setCurrentSample(size_t i) { setCurrentSample(samples.at(i)); }
    
    void shuffle();
    
    bool store(std::string);
    static TrainingSet* load(std::string);
    
    bool train(Network&);
    bool evaluate(Network&);
    
    // Getters
    inline scalar* getCurrentSampleInput() { return currentSampleInput; }
    inline scalar* getCurrentSampleOutput() { return currentSampleOutput; }
    
    // Conversion functions
    scalar toInputScalar1(uint8_t*); scalar toInputScalar2(uint16_t*); scalar toInputScalar4(uint32_t*);
    scalar toOutputScalar1(uint8_t*); scalar toOutputScalar2(uint16_t*); scalar toOutputScalar4(uint32_t*);
    uint8_t toInputValue1(scalar); uint16_t toInputValue2(scalar); uint32_t toInputValue4(scalar);
    uint8_t toOutputValue1(scalar); uint16_t toOutputValue2(scalar); uint32_t toOutputValue4(scalar);
};

#endif
