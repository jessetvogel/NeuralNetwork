#ifndef sample_hpp
#define sample_hpp

#include "math.hpp"
#include <cstring>

class Sample {

    const dim inputSize;
    const dim outputSize;
    
public:
    
    Sample(dim, dim);
    ~Sample();
    
    inline dim getInputSize() { return inputSize; }
    inline dim getOutputSize() { return outputSize; }
    
    scalar* input;
    scalar* output;
    
    bool save(std::string);
    static Sample* load(std::string);

    Sample* duplicate();
    
};

#endif
