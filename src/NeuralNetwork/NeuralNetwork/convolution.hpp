#ifndef convolution_hpp
#define convolution_hpp

#include "tensor.hpp"

class Convolution : Function {
    
    Volume* const volume;
    FilterSet* const filters;
    
    Convolution(Volume* volume, FilterSet* filters) : volume(volume), filters(filters) {};
    
public:
    
    static Volume* create(Volume*, FilterSet*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
