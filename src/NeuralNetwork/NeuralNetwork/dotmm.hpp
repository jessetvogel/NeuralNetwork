#ifndef dotmm_hpp
#define dotmm_hpp

#include "matrix.hpp"

class DotMM : Function {
    
    Matrix* const a;
    Matrix* const b;
    
    DotMM(Matrix* a, Matrix* b) : a(a), b(b) {};
    
public:
    
    static Matrix* create(Matrix*, Matrix*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
