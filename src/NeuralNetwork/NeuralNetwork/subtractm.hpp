#ifndef addm_hpp
#define addm_hpp

#include "math.hpp"
#include "matrix.hpp"

class SubtractM : Function {
    
    Matrix* result;
    
    Matrix* a;
    Matrix* b;
    
    SubtractM(Matrix*, Matrix*);
    inline ~SubtractM() {};
    
public:
    
    static Matrix* create(Matrix*, Matrix*);
    
    void evaluate();
    void backpropagate();
    
};

#endif


