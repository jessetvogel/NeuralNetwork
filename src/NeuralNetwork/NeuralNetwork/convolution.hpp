#ifndef convolution_hpp
#define convolution_hpp

#include "tensor.hpp"

class Convolution : Function {
    
    Volume* const a;
    FilterSet* const b;
    
    Convolution(Volume* a, FilterSet* b) : a(a), b(b) {};
    
public:
    
    static Volume* create(Volume*, FilterSet*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
