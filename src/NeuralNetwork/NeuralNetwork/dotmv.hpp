#ifndef dotmv_hpp
#define dotmv_hpp

#include "tensor.hpp"

class DotMV : Function {
    
    Matrix* const a;
    Variable* const b;
    
    DotMV(Matrix* a, Variable* b) : a(a), b(b) {};
    
public:
    
    static Vector* create(Matrix*, Variable*);
    
    void setResult(Variable*);
    void evaluate();
    void backpropagate();
    
};

#endif
