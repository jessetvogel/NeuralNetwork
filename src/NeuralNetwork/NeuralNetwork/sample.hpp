#ifndef sample_hpp
#define sample_hpp

#include "math.hpp"
#include <cstring>

class Sample {

    const dimension inputSize;
    const dimension outputSize;
    
public:
    
    Sample(dimension, dimension);
    ~Sample();
    
    inline dimension getInputSize() { return inputSize; }
    inline dimension getOutputSize() { return outputSize; }
    
    scalar* input;
    scalar* output;
    
    bool save(std::string);
    static Sample* load(std::string);

    Sample* duplicate();
    
};

#endif
