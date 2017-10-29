#ifndef sample_hpp
#define sample_hpp

#include "math.hpp"

class Sample {

    const unsigned int inputSize;
    const unsigned int outputSize;
    
public:
    
    Sample(unsigned int, unsigned int);
    ~Sample();
    
    inline unsigned int getInputSize() { return inputSize; }
    inline unsigned int getOutputSize() { return outputSize; }
    
    scalar* input;
    scalar* output;

};

#endif
