#ifndef maxpool_hpp
#define maxpool_hpp

#include "tensor.hpp"

class MaxPool : Function {
    
    Volume* const a;
    const int width;
    const int height;
    
    MaxPool(Volume* a, int w, int h) : a(a), width(w), height(h) {};
    
public:
    
    static Volume* create(Volume*, int, int);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
